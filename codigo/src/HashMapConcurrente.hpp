#ifndef HMC_HPP
#define HMC_HPP

#include <mutex>
#include <array>
#include <atomic>
#include <string>
#include <vector>
#include <semaphore.h>
#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static constexpr int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);
    hashMapPair maximoParaleloAux();

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];
    static unsigned int hashIndex(std::string clave);
    mutex mutex[cantLetras];
    mutex mutexMax;
    sem_t semIncYMax;
    
};

#endif  /* HMC_HPP */
