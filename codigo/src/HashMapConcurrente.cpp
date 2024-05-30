#ifndef CHM_CPP
#define CHM_CPP

#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include "HashMapConcurrente.hpp"

using namespace std;

//atomic<int> index(0);                                  //no se donde crear estas variables
//hashMapPair maximoHMP = make_pair("", -1);           //no se donde crear estas variables

HashMapConcurrente::HashMapConcurrente() {                                  
    sem_init(&_semIncYMax, 0 , 1);
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
    _index = 0;
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int indice = hashIndex(clave);
    _mutex[indice].lock();
    sem_wait(&_semIncYMax);
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

    sem_post(&_semIncYMax);
    _mutex[indice].unlock();    
}

std::vector<std::string> HashMapConcurrente::claves() {
    vector<string> res;
    for (int j = 0; j < cantLetras; j++){
        _mutex[j].lock();
    }
    for (int i = 0; i < cantLetras; i++){
        for(auto& clave_actual: *tabla[i]){
            res.push_back(clave_actual.first);
        }
        _mutex[i].unlock();
    }
    return res;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int indice = hashIndex(clave);
    unsigned int valor = 0;
    for(auto& palabra: *tabla[indice]){
        if(palabra.first == clave){
            valor = palabra.second;
            break;
        }    
    }

    return valor;

}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair res = make_pair("", 0);
    res.second = 0;

    sem_wait(&_semIncYMax);
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        for (auto &p : *tabla[i]) {
            if (p.second > res.second) {
                res.first = p.first;
                res.second = p.second;
            }
        }
    }

    sem_post(&_semIncYMax);
    return res;
}

void HashMapConcurrente::maximoParaleloAux() {
    int indice;
    while((indice = _index++) < 26){                //index++ devuelve el valor anterior de index

         for (auto &palabra : *tabla[indice]) {
            _mutexMax.lock();
            if(palabra.second > _maximoHMP.second){
                _maximoHMP.second = palabra.second;
                _maximoHMP.first = palabra.first;
            }
            _mutexMax.unlock();
        }

        _mutex[indice].unlock();
        
    }
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
   
    for (int j = 0; j < cantLetras; j++){
        _mutex[j].lock();
    }
    vector<thread> threads;
    for(unsigned int i = 0; i < cant_threads; i++){
        //buscar max
        threads.emplace_back(&HashMapConcurrente::maximoParaleloAux, this);
    }
    
    for(auto &t: threads){
        t.join();
    }
    return _maximoHMP;
}



#endif
