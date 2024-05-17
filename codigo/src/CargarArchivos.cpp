#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "CargarArchivos.hpp"


atomic<int> archivo(0); 

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

//esta funcion aux no estaba en el archivo original
void cargarMultiplesArchivosAux(
    HashMapConcurrente &hashMap,
   
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)
    int indice;
    int n = sizeof(filePaths);
    while((indice = archivo++) < n){  
        string filePath = filePaths[indice];          
        cargarArchivo(hashMap, filePath);  
    }
    
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)
    vector<thread> threads;
    for(unsigned int i = 0; i < cantThreads; i++){
        //buscar max
        threads.emplace_back(cargarMultiplesArchivosAux,ref(hashMap), ref(filePaths));
    }
    
    for(auto &t: threads){
        t.join();
    }
}

#endif
