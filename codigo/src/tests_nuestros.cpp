#include <vector>
#include <iostream>
#include "lib/littletest.hpp"
#include <chrono>
#include <cstdint>
#include <future>
#include <cassert>
#include <thread>

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

using namespace std::chrono;
int main(){
    //TIEMPOS
    std::vector<std::string> filePaths = {"./data/corpus",
    "./data/test-1","./data/test-2","./data/test-3"};

    HashMapConcurrente hashMap_cuatro_threads{};

    auto inicio = steady_clock::now();

    cargarMultiplesArchivos(hashMap_cuatro_threads,4,filePaths);

    auto fin = steady_clock::now();

    std::cout << "Cantidad de threads: 4 \n" << " tiempo: " << duration_cast<milliseconds>(fin-inicio).count() << " millisecs\n" ;
    
    HashMapConcurrente hashMap_un_thread{};

    auto start = steady_clock::now();

    cargarMultiplesArchivos(hashMap_un_thread,1,filePaths);

    auto end = steady_clock::now();

    std::cout << "Cantidad de threads: 1 \n" << " tiempo: " << duration_cast<milliseconds>(end-start).count() << " millisecs\n" ;

    return 0;
}