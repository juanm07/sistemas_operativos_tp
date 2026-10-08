# TP1 Sistemas Operativos - Threading

Trabajo práctico de la materia Sistemas Operativos (primer cuatrimestre de 2024).
El enunciado completo está en `tp1-enunciado.pdf`.

## De qué trata

El objetivo del TP es practicar programación concurrente con threads en C++
(`std::thread`, que por debajo usa pthreads) y evitar condiciones de carrera y
deadlocks.

Para eso se implementa un `HashMapConcurrente`: una tabla de hash cuyas claves
son palabras y cuyos valores son la cantidad de veces que aparece cada palabra.
Con esa estructura, el programa `ContarPalabras` lee uno o más archivos de texto
usando varios threads y después calcula, también en paralelo, cuál es la palabra
que más se repite.

### Cómo está armada la solución

- **`ListaAtomica`** (`src/ListaAtomica.hpp`): lista enlazada que se usa como
  bucket de la tabla. La inserción al principio de la lista es atómica (está
  protegida con un mutex).
- **`HashMapConcurrente`** (`src/HashMapConcurrente.hpp` y `.cpp`): tabla de
  26 buckets, uno por cada letra de la `a` a la `z`. La función de hash es
  simplemente la primera letra de la palabra.
  - `incrementar(clave)`: suma 1 a la clave o la agrega con valor 1. Hay un
    mutex por bucket, así que dos threads solo compiten si las palabras
    empiezan con la misma letra.
  - `claves()`: devuelve todas las palabras cargadas.
  - `valor(clave)`: devuelve cuántas veces aparece una palabra (0 si no está).
  - `maximo()`: devuelve el par (palabra, apariciones) con más apariciones,
    sin pisarse con `incrementar`.
  - `maximoParalelo(cantThreads)`: igual que `maximo`, pero reparte el trabajo
    entre varios threads. Cada thread toma la siguiente fila libre de la tabla
    usando un contador atómico, y termina cuando ya no quedan filas.
- **`CargarArchivos`** (`src/CargarArchivos.hpp` y `.cpp`):
  - `cargarArchivo(hashMap, archivo)`: lee un archivo palabra por palabra y lo
    carga en la tabla.
  - `cargarMultiplesArchivos(hashMap, cantThreads, archivos)`: carga varios
    archivos usando `cantThreads` threads. Cada thread toma el siguiente
    archivo pendiente (también con un contador atómico) hasta que no quedan más.
- **`ContarPalabras`** (`src/ContarPalabras.cpp`): programa principal que une
  todo lo anterior.

## Estructura del repositorio

```
.
├── README.md
├── tp1-enunciado.pdf          Enunciado del TP
└── codigo/
    ├── Makefile
    ├── README.md              README original de la cátedra
    ├── src/
    │   ├── ContarPalabras.cpp     Programa principal
    │   ├── HashMapConcurrente.*   Tabla de hash concurrente
    │   ├── ListaAtomica.hpp       Lista enlazada usada en cada bucket
    │   ├── CargarArchivos.*       Lectura de archivos con threads
    │   ├── UnitTests.cpp          Tests de la cátedra y tests propios
    │   └── lib/littletest.hpp     Biblioteca de tests
    ├── data/                  Archivos de texto de prueba
    └── scripts/
        └── contar-palabras.awk    Script para verificar resultados
```

## Requisitos

- Linux, o WSL si estás en Windows. El código usa `semaphore.h` (semáforos
  POSIX), así que no compila con MinGW/MSVC en Windows nativo y en macOS los
  semáforos sin nombre no funcionan.
- `g++` con soporte para C++11.
- `make`.

En Ubuntu/Debian se instala todo con:

```
sudo apt install build-essential
```

## Cómo compilar

Todos los comandos se corren desde la carpeta `codigo`:

```
cd codigo
make
```

El ejecutable queda en `build/ContarPalabras`.

Para borrar lo compilado:

```
make clean
```

## Cómo ejecutar

```
./build/ContarPalabras <threads_lectura> <threads_maximo> <archivo1> [<archivo2> ...]
```

- `threads_lectura`: cantidad de threads que se usan para leer los archivos.
- `threads_maximo`: cantidad de threads que se usan para buscar la palabra con
  más apariciones.
- `archivo1`, `archivo2`, ...: archivos de texto a procesar.

Ejemplo:

```
./build/ContarPalabras 4 4 data/concurrencia-1 data/concurrencia-2 data/concurrencia-3 data/concurrencia-4
```

La salida muestra cuántos threads de lectura se usaron, cuánto tardó la carga
de los archivos y, en la última línea, la palabra más repetida junto con su
cantidad de apariciones:

```
Cantidad de threads: 4
 tiempo: 0 millisecs
arbol 50
```

### Formato de los archivos de entrada

Los archivos tienen que contener palabras separadas por espacios o saltos de
línea, escritas solo con letras minúsculas de la `a` a la `z` (sin mayúsculas,
números, tildes, `ñ` ni signos de puntuación). Esto es porque la función de
hash usa la primera letra de cada palabra para elegir el bucket.

En `data/` hay algunos archivos de ejemplo:

| Archivo | Contenido |
|---|---|
| `test-1`, `test-2`, `test-3` | Archivos chicos con nombres de dinosaurios, usados por los tests de la cátedra |
| `concurrencia-1` a `concurrencia-4` | Archivos con nombres de animales, usados por nuestros tests |
| `corpus` | Archivo más grande (unas 2500 palabras) para probar con más carga |

## Cómo correr los tests

Desde la carpeta `codigo`:

```
make test
```

Esto compila y ejecuta `build/UnitTests`, que incluye:

- Los tests provistos por la cátedra, separados por ejercicio (`TestsEjercicio1`
  a `TestsEjercicio4`).
- Tests propios (`TestsNuestros`), que cargan los archivos `concurrencia-*` con
  varios threads y verifican los conteos y el resultado de `maximo` y
  `maximoParalelo` después de varias operaciones.

Los tests abren archivos con rutas relativas (`data/...`), así que tienen que
correrse desde `codigo`.

Como aclara el enunciado, estos tests no prueban la concurrencia a fondo: que
pasen no garantiza que no haya condiciones de carrera.

Nota: el `Makefile` tiene un objetivo `make nuestros` que busca un archivo
`src/tests_nuestros.cpp` que no existe, por lo que ese comando falla. Los tests
propios están dentro de `UnitTests.cpp` y se corren con `make test`.

## Verificar resultados con awk

El script `scripts/contar-palabras.awk` cuenta las apariciones de cada palabra
sin usar threads, y sirve para comparar con lo que devuelve el programa:

```
awk -f scripts/contar-palabras.awk data/corpus | sort -nk 2
```

Las palabras más repetidas aparecen al final. Si hay varias empatadas en el
máximo, `ContarPalabras` puede devolver cualquiera de ellas.

## Modo debug

```
make debug
```

Compila con la macro `DEBUG` definida y con símbolos de depuración, para usar
con `gdb` o con el debugger de VS Code.
