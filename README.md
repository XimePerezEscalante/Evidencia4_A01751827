# Evidencia4_A01751827: Edición de la saturación de una imagen usando el Paradigma Paralelo

Este proyecto consiste en editar la saturación de distintas imágenes utilizando programación paralela en C++ y las librerías **NumPy** y **Pillow** de Python para poder visualizar las imágenes desde la matriz que las representa.

## Descripción del Paradigma

La **programación paralela** consiste en usar dos o más procesadores para resolver una tarea (Ortiz, 2020). En este proyecto, esa tarea es el procesamiento de una matriz tridimensional que representa una imagen a través de sus píxeles RGB.

Existen tres tipos de paralelismo:

* A nivel de bit
* A nivel de instrucción
* A nivel de tarea (**utilizado aquí**) mediante **threads** (hilos)

Un **hilo** es una unidad de ejecución independiente dentro de un programa. Usar hilos permite realizar tareas simultáneamente, mejorando la eficiencia, especialmente en tareas que pueden dividirse en subtareas.

## Diagrama de Ejecución Paralela

<img src="https://github.com/XimePerezEscalante/Evidencia4_A01751827/blob/main/diagrama.jpg">

Cada imagen se procesa dividiendo las filas entre 8 hilos:

* Cada hilo procesa `H / 8` filas.
* Cada fila tiene `W = 3072` columnas.
* Cada columna representa un píxel, compuesto por 3 valores: R, G, B.

## Dependencias y Compilación

### Python

* **Librerías**: `Pillow`, `NumPy`
* **Ejecución**:

```bash
python3 paint_image.py
```
_Nota: puede que el programa tarde en ejecutarse por el tiempo que le toma escribir los valores RGB de cada píxel en el archivo pixelespy.txt_
### C++

* **Librerías**: `chrono`, `algorithm`, `thread`, `fstream`
* **Compilar modo paralelo**:

```bash
g++ -std=c++11 -pthread paralelismo.cpp
```

* **Compilar modo secuencial**:

```bash
g++ -std=c++11 -pthread secuencial.cpp
```

* **Ejecutar**:

```bash
./a.out
```

## Complejidad Temporal y Espacial

La función central `setDesaturatedValues` tiene esta complejidad:

* **Tiempo secuencial**: `O(H × W)`
* **Tiempo paralelo ideal (8 hilos)**: `O((H × W)/8)`
* **Espacio**: `O(H × W × 3)` (cada píxel tiene 3 valores)

### Ejemplo:

* Si `H = 2048` y `W = 3072`, entonces `H × W = 6291456` iteraciones
* Tiempo en secuencial: `O(6291456)`
* Tiempo en paralelo ideal: `O(786432)`

## Resultados de Pruebas

Los siguientes tiempos se midieron usando `std::chrono` en C++.

| Imagen | Paralelismo (ms) | Secuencial (ms) |
| ------ | ---------------- | --------------- |
| 1      | 16885            | 70250           |
| 2      | 27329            | 84292           |
| 3      | 22311            | 86541           |

**Conclusión**: el uso de hilos mejora notablemente el rendimiento.

## Referencias

* Ortiz, 2020. Computación paralela: [https://www.teldat.com/es/blog/computacion-paralela-capacidad-procesamiento/](https://www.teldat.com/es/blog/computacion-paralela-capacidad-procesamiento/)
* GeeksforGeeks, 2025. Threads en sistemas operativos: [https://www-geeksforgeeks-org.translate.goog/threads-and-its-types-in-operating-system](https://www-geeksforgeeks-org.translate.goog/threads-and-its-types-in-operating-system)
* Imágenes utilizadas:

  * [https://i.natgeofe.com/n/f2199174-f2d1-4ac8-9e53-cb484073868a/athabasca-river-jasper-national-park.jpg](https://i.natgeofe.com/n/f2199174-f2d1-4ac8-9e53-cb484073868a/athabasca-river-jasper-national-park.jpg)
  * [https://i.natgeofe.com/n/f7facfef-285c-4171-b58a-3c4653d11872/2019-travel-photo-contest-epic-landscapes035.jpg](https://i.natgeofe.com/n/f7facfef-285c-4171-b58a-3c4653d11872/2019-travel-photo-contest-epic-landscapes035.jpg)
  * [https://i.natgeofe.com/n/375cf222-3c35-439d-82c4-acc392297812/05-best\_pod\_landscapes.jpg](https://i.natgeofe.com/n/375cf222-3c35-439d-82c4-acc392297812/05-best_pod_landscapes.jpg)

