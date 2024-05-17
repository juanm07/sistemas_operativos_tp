#ifndef CHM_CPP
#define CHM_CPP

#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include "HashMapConcurrente.hpp"

using namespace std;

atomic<int> i = 0;                                  //no se donde crear estas variables 
hashMapPair *maximo = new hashMapPair();           //no se donde crear estas variables 
maximo->second = -1;
maximo->first = "";    
HashMapConcurrente::HashMapConcurrente() {                                  
    sem_init(&semIncYMax, 0 , 1);
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int indice = hashIndex(clave);
    mutex[indice].lock();
    sem_wait(&semIncYMax);
    bool existe = false;
    for(auto& palabra: *tabla[indice]){
        if(palabra.first == clave){
            palabra.second++;
            existe = true;
            break;
        }
    }

    if(!existe){
        tabla[indice]->insertar(make_pair(clave, 1));
    }

    sem_post(&semIncYMax);
    mutex[indice].unlock();    
}

std::vector<std::string> HashMapConcurrente::claves() {
    vector<string> res;
    for (int j = 0; j < cantLetras; j++){
        mutex[j].lock();
    }
    for (int i = 0; i < cantLetras; i++){
        for(auto& clave_actual: *tabla[i]){
            res.push_back(clave_actual.first);
        }
        mutex[i].unlock();
    }
    return res;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int indice = hashIndex(clave);
    int valor = 0;
    for(auto& palabra: *tabla[indice]){
        if(palabra.first == clave){
            valor = palabra.second;
            break;
        }    
    }

    return valor;

}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    sem_wait(&semIncYMax);
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
    }

    sem_post(&semIncYMax);
    return *max;
}

void HashMapConcurrente::maximoParaleloAux() {
    int indice;
    while((indice = i++) <= 26){                //cuando i == 26 quiere decir que estoy en tabla[25]. Lo tengo q hacer asi para q no pueda pasar que mas de un thread use el mismo tabla[indice]

         for (auto &palabra : *tabla[indice--]) {
            mutexMax.lock();
            if(palabra.second > maximo.second){
                maximo.second = palabra.second;
                maximo.first = palabra.first;
            }
            mutexMax.unlock();
        }

        mutex[indice--].unlock();
        
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
   
    for (int j = 0; j < cantLetras; j++){
        mutex[j].lock();
    }
     vector<thread> threads;
    for(int i = 0; i < cant_threads; i++){
        //buscar max
        threads.emplace_back(maximoParaleloAux);
    }
    
    for(auto &t: threads){
        t.join();
    }
    return maximo;
}



#endif
