#include <vector>
#include <iostream>
#include "lib/littletest.hpp"

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

// Tests Ejercicio 1

LT_BEGIN_SUITE(TestsEjercicio1)
ListaAtomica<int> l;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio1)

LT_BEGIN_TEST(TestsEjercicio1, ListaComienzaVacia)
    LT_CHECK_EQ(l.longitud(), 0);
LT_END_TEST(ListaComienzaVacia)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaElemento)
    l.insertar(42);
    LT_CHECK_EQ(l.longitud(), 1);
LT_END_TEST(InsertarAgregaElemento)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaElementoCorrecto)
    l.insertar(42);
    LT_CHECK_EQ(l[0], 42);
LT_END_TEST(InsertarAgregaElementoCorrecto)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaEnOrden)
    l.insertar(4);
    l.insertar(3);
    l.insertar(2);
    l.insertar(1);
    LT_CHECK_EQ(l.longitud(), 4);
    LT_CHECK_EQ(l[0], 1);
    LT_CHECK_EQ(l[1], 2);
    LT_CHECK_EQ(l[2], 3);
    LT_CHECK_EQ(l[3], 4);
LT_END_TEST(InsertarAgregaEnOrden)

// Tests Ejercicio 2

LT_BEGIN_SUITE(TestsEjercicio2)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio2)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoEnHashMapVacio)
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 0);
LT_END_TEST(ValorEsCorrectoEnHashMapVacio)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoEnHashMapVacio)
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoEnHashMapVacio)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasUnaInsercion)
    hM.incrementar("tiranosaurio");
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 1);
LT_END_TEST(ValorEsCorrectoTrasUnaInsercion)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasUnaInsercion)
    hM.incrementar("tiranosaurio");
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {"tiranosaurio"};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoTrasUnaInsercion)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasDosInsercionesMismaPalabra)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
LT_END_TEST(ValorEsCorrectoTrasDosInsercionesMismaPalabra)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasDosInsercionesMismaPalabra)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {"tiranosaurio"};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoTrasDosInsercionesMismaPalabra)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasVariasInsercionesMismoBucket)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("triceratops");
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
    LT_CHECK_EQ(hM.valor("triceratops"), 1);
LT_END_TEST(ValorEsCorrectoTrasVariasInsercionesMismoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasVariasInsercionesMismoBucket)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("triceratops");
    std::vector<std::string> actual = hM.claves();
    LT_CHECK_EQ(actual.size(), 2);
    LT_CHECK(std::find(actual.begin(), actual.end(), "tiranosaurio") != actual.end());
    LT_CHECK(std::find(actual.begin(), actual.end(), "triceratops") != actual.end());
LT_END_TEST(ClavesEsCorrectoTrasVariasInsercionesMismoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasVariasInsercionesDistintoBucket)
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("tiranosaurio");
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
    LT_CHECK_EQ(hM.valor("estegosaurio"), 1);
LT_END_TEST(ValorEsCorrectoTrasVariasInsercionesDistintoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasVariasInsercionesDistintoBucket)
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("tiranosaurio");
    std::vector<std::string> actual = hM.claves();
    LT_CHECK_EQ(actual.size(), 2);
    LT_CHECK(std::find(actual.begin(), actual.end(), "tiranosaurio") != actual.end());
    LT_CHECK(std::find(actual.begin(), actual.end(), "estegosaurio") != actual.end());
LT_END_TEST(ClavesEsCorrectoTrasVariasInsercionesDistintoBucket)

// Tests Ejercicio 3

LT_BEGIN_SUITE(TestsEjercicio3)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio3)

LT_BEGIN_TEST(TestsEjercicio3, MaximoEsCorrecto)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("estegosaurio");

    hashMapPair actual = hM.maximo();
    LT_CHECK_EQ(actual.first, "tiranosaurio");
    LT_CHECK_EQ(actual.second, 4);
LT_END_TEST(MaximoEsCorrecto)

LT_BEGIN_TEST(TestsEjercicio3, MaximoParaleloEsCorrectoUnThread)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("estegosaurio");

    hashMapPair actual = hM.maximoParalelo(1);
    LT_CHECK_EQ(actual.first, "tiranosaurio");
    LT_CHECK_EQ(actual.second, 4);
LT_END_TEST(MaximoParaleloEsCorrectoUnThread)

LT_BEGIN_TEST(TestsEjercicio3, MaximoParaleloEsCorrectoDosThreads)
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("tiranosaurio");
    hM.incrementar("estegosaurio");
    hM.incrementar("estegosaurio");

    hashMapPair actual = hM.maximoParalelo(2);
    LT_CHECK_EQ(actual.first, "tiranosaurio");
    LT_CHECK_EQ(actual.second, 4);
LT_END_TEST(MaximoParaleloEsCorrectoDosThreads)

// Tests Ejercicio 4

LT_BEGIN_SUITE(TestsEjercicio4)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio4)

LT_BEGIN_TEST(TestsEjercicio4, CargarArchivoFunciona)
    cargarArchivo(hM, "data/test-1");
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 1);
    LT_CHECK_EQ(hM.claves().size(), 5);
LT_END_TEST(CargarArchivoFunciona)

LT_BEGIN_TEST(TestsEjercicio4, CargarMultiplesArchivosFuncionaUnThread)
    cargarMultiplesArchivos(hM, 1, {"data/test-1", "data/test-2", "data/test-3"});
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
    LT_CHECK_EQ(hM.valor("linux"), 3);
    LT_CHECK_EQ(hM.valor("estegosaurio"), 4);
    LT_CHECK_EQ(hM.claves().size(), 12);
LT_END_TEST(CargarMultiplesArchivosFuncionaUnThread)

LT_BEGIN_TEST(TestsEjercicio4, CargarMultiplesArchivosFuncionaDosThreads)
    cargarMultiplesArchivos(hM, 2, {"data/test-1", "data/test-2", "data/test-3"});
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
    LT_CHECK_EQ(hM.valor("linux"), 3);
    LT_CHECK_EQ(hM.valor("estegosaurio"), 4);
    LT_CHECK_EQ(hM.claves().size(), 12);
LT_END_TEST(CargarMultiplesArchivosFuncionaDosThreads)

// Tests nuestros
LT_BEGIN_SUITE(TestsNuestros)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsNuestros)

LT_BEGIN_TEST(TestsNuestros, MaximoNoDevuelvaValorIncorrecto)
    cargarMultiplesArchivos(hM, 2, {"data/concurrencia-1", "data/concurrencia-2", "data/concurrencia-3", "data/concurrencia-4"});
    LT_CHECK_EQ(hM.valor("arbol"), 50);
    LT_CHECK_EQ(hM.valor("zoo"), 50);
    LT_CHECK_EQ(hM.valor("mono"), 9);
    LT_CHECK_EQ(hM.valor("comida"), 17);
    LT_CHECK_EQ(hM.valor("bufalo"), 2);
    LT_CHECK_EQ(hM.valor("yacare"), 21);
    LT_CHECK_EQ(hM.valor("vivora"), 1);
    LT_CHECK_EQ(hM.valor("tigre"), 4);
    LT_CHECK_EQ(hM.valor("flamenco"), 31);
    LT_CHECK_EQ(hM.valor("hipopotamo"), 10);
    LT_CHECK_EQ(hM.valor("jirafa"), 4);
    LT_CHECK_EQ(hM.valor("leon"), 5);
    LT_CHECK_EQ(hM.valor("liebre"), 2);
    LT_CHECK_EQ(hM.valor("aguila"), 9);
    LT_CHECK_EQ(hM.valor("caballo"), 3);
    LT_CHECK_EQ(hM.claves().size(), 15);

    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hashMapPair actual = hM.maximo();
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");

    LT_CHECK_EQ(actual.first, "arbol");
    LT_CHECK_EQ(actual.second, 65);

    LT_CHECK_EQ(hM.valor("arbol"), 65);
    LT_CHECK_EQ(hM.valor("zoo"), 58);
    LT_CHECK_EQ(hM.claves().size(), 15);
LT_END_TEST(MaximoNoDevuelvaValorIncorrecto)

LT_BEGIN_TEST(TestsNuestros, MaximoParaleloNoDevuelvaValorIncorrecto)
    cargarMultiplesArchivos(hM, 3, {"data/concurrencia-1", "data/concurrencia-2", "data/concurrencia-3", "data/concurrencia-4"});
    LT_CHECK_EQ(hM.valor("arbol"), 50);
    LT_CHECK_EQ(hM.valor("zoo"), 50);
    LT_CHECK_EQ(hM.valor("mono"), 9);
    LT_CHECK_EQ(hM.valor("comida"), 17);
    LT_CHECK_EQ(hM.valor("bufalo"), 2);
    LT_CHECK_EQ(hM.valor("yacare"), 21);
    LT_CHECK_EQ(hM.valor("vivora"), 1);
    LT_CHECK_EQ(hM.valor("tigre"), 4);
    LT_CHECK_EQ(hM.valor("flamenco"), 31);
    LT_CHECK_EQ(hM.valor("hipopotamo"), 10);
    LT_CHECK_EQ(hM.valor("jirafa"), 4);
    LT_CHECK_EQ(hM.valor("leon"), 5);
    LT_CHECK_EQ(hM.valor("liebre"), 2);
    LT_CHECK_EQ(hM.valor("aguila"), 9);
    LT_CHECK_EQ(hM.valor("caballo"), 3);
    LT_CHECK_EQ(hM.claves().size(), 15);

    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hashMapPair actual = hM.maximoParalelo(4);
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");
    hM.incrementar("zoo");


    LT_CHECK_EQ(actual.first, "arbol");
    LT_CHECK_EQ(actual.second, 65);

    LT_CHECK_EQ(hM.valor("arbol"), 65);
    LT_CHECK_EQ(hM.valor("zoo"), 64);
    LT_CHECK_EQ(hM.claves().size(), 15);
LT_END_TEST(MaximoParaleloNoDevuelvaValorIncorrecto)

LT_BEGIN_TEST(TestsNuestros, IncrementarDespuesNoAfectaClaves)
    cargarMultiplesArchivos(hM, 1, {"data/test-1", "data/test-2", "data/test-3"});
    LT_CHECK_EQ(hM.valor("arbol"), 0);
    LT_CHECK_EQ(hM.valor("zoo"), 0);
    LT_CHECK_EQ(hM.claves().size(), 12);

    vector<std::string> v = hM.claves();
    hM.incrementar("arbol");
    hM.incrementar("zoo");

    LT_CHECK_EQ(v.size(), 12);
    LT_CHECK_EQ(hM.claves().size(), 14);
    LT_CHECK_EQ(hM.valor("arbol"), 1);
    LT_CHECK_EQ(hM.valor("zoo"), 1);
    LT_CHECK_EQ(hM.valor("tiranosaurio"), 2);
    LT_CHECK_EQ(hM.valor("linux"), 3);
    LT_CHECK_EQ(hM.valor("estegosaurio"), 4);
LT_END_TEST(IncrementarDespuesNoAfectaClaves)

LT_BEGIN_TEST(TestsNuestros, testCompleto)
    cargarMultiplesArchivos(hM, 4, {"data/concurrencia-1", "data/concurrencia-2", "data/concurrencia-3", "data/concurrencia-4"});
    LT_CHECK_EQ(hM.valor("arbol"), 50);
    LT_CHECK_EQ(hM.valor("zoo"), 50);
    LT_CHECK_EQ(hM.valor("mono"), 9);
    LT_CHECK_EQ(hM.valor("comida"), 17);
    LT_CHECK_EQ(hM.valor("bufalo"), 2);
    LT_CHECK_EQ(hM.valor("yacare"), 21);
    LT_CHECK_EQ(hM.valor("vivora"), 1);
    LT_CHECK_EQ(hM.valor("tigre"), 4);
    LT_CHECK_EQ(hM.valor("flamenco"), 31);
    LT_CHECK_EQ(hM.valor("hipopotamo"), 10);
    LT_CHECK_EQ(hM.valor("jirafa"), 4);
    LT_CHECK_EQ(hM.valor("leon"), 5);
    LT_CHECK_EQ(hM.valor("liebre"), 2);
    LT_CHECK_EQ(hM.valor("aguila"), 9);
    LT_CHECK_EQ(hM.valor("caballo"), 3);
    LT_CHECK_EQ(hM.claves().size(), 15);

    hM.incrementar("zoo");
    hM.incrementar("mono");
    hashMapPair primerMax = hM.maximoParalelo(4);
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hashMapPair segundoMax = hM.maximoParalelo(3);
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    hM.incrementar("arbol");
    unsigned int ar = hM.valor("arbol");
    unsigned int ag = hM.valor("aguila");
    hM.incrementar("aguila");
    hM.incrementar("hipopotamo");
    hM.incrementar("pez");
    hM.incrementar("pez");
    hM.incrementar("pez");
    hM.incrementar("pez");
    hM.incrementar("leon");
    hM.incrementar("liebre");
    hM.incrementar("caballo");
    hM.incrementar("caballo");
    hM.incrementar("caballo");
    hM.incrementar("leon");
    hM.incrementar("liebre");
    hM.incrementar("zoo");
    vector<std::string> v = hM.claves();
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hM.incrementar("perro");
    hashMapPair tercerMax = hM.maximoParalelo(2);


    LT_CHECK_EQ(primerMax.first, "zoo");
    LT_CHECK_EQ(primerMax.second, 51);
    LT_CHECK_EQ(segundoMax.first, "arbol");
    LT_CHECK_EQ(segundoMax.second, 52);
    LT_CHECK_EQ(tercerMax.first, "arbol");
    LT_CHECK_EQ(tercerMax.second, 57);
    LT_CHECK_EQ(ar, 57);
    LT_CHECK_EQ(ag, 9);
    LT_CHECK_EQ(v.size(), 16);
    LT_CHECK_EQ(hM.claves().size(), 17);
    LT_CHECK_EQ(hM.valor("pez"), 4);
    LT_CHECK_EQ(hM.valor("perro"), 11);
    LT_CHECK_EQ(hM.valor("arbol"), 57);
    LT_CHECK_EQ(hM.valor("zoo"), 52);
    LT_CHECK_EQ(hM.valor("mono"), 10);
    LT_CHECK_EQ(hM.valor("comida"), 17);
    LT_CHECK_EQ(hM.valor("bufalo"), 2);
    LT_CHECK_EQ(hM.valor("yacare"), 21);
    LT_CHECK_EQ(hM.valor("vivora"), 1);
    LT_CHECK_EQ(hM.valor("tigre"), 4);
    LT_CHECK_EQ(hM.valor("flamenco"), 31);
    LT_CHECK_EQ(hM.valor("hipopotamo"), 11);
    LT_CHECK_EQ(hM.valor("jirafa"), 4);
    LT_CHECK_EQ(hM.valor("leon"), 7);
    LT_CHECK_EQ(hM.valor("liebre"), 4);
    LT_CHECK_EQ(hM.valor("aguila"), 10);
    LT_CHECK_EQ(hM.valor("caballo"), 6);
LT_END_TEST(testCompleto)

// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()

