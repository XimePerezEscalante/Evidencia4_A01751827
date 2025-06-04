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

## Instrucciones de Uso

Es importante seguir el siguiente orden para ejecutar correctamente el proyecto:

1. Ejecutar el archivo **`crear_imagen.py`** y seleccionar la **primera opción**.

   * Esto utilizará NumPy para obtener los valores de cada píxel y los guardará en el archivo `pixelespy.txt`.

2. Compilar y ejecutar uno de los programas en C++ (`paralelismo.cpp` o `secuencial.cpp`).

   * Aquí se realiza la conversión a blanco y negro modificando el archivo `pixeles.txt` con los nuevos valores.

3. (Opcional) Ejecutar nuevamente `crear_imagen.py`, esta vez eligiendo la **segunda opción**.

   * Esto permitirá visualizar la imagen modificada en una ventana emergente.

### Imágenes Disponibles

En total hay 3 imágenes predeterminadas entre las que puedes elegir:

1. **imagen1.png**
   ![imagen1](https://github.com/XimePerezEscalante/Evidencia4_A01751827/blob/main/imagen1.png)
   **Referencia**: https://i.natgeofe.com/n/f2199174-f2d1-4ac8-9e53-cb484073868a/athabasca-river-jasper-national-park.jpg

2. **imagen2.png**
   ![imagen2](https://github.com/XimePerezEscalante/Evidencia4_A01751827/blob/main/imagen2.png)
   **Referencia**: https://i.natgeofe.com/n/f7facfef-285c-4171-b58a-3c4653d11872/2019-travel-photo-contest-epic-landscapes035.jpg

3. **imagen3.png**
   ![imagen3](https://github.com/XimePerezEscalante/Evidencia4_A01751827/blob/main/imagen3.png)
   **Referencia**: https://i.natgeofe.com/n/375cf222-3c35-439d-82c4-acc392297812/05-best_pod_landscapes.jpg

> También puedes usar una imagen propia.
>
> * Sólo debes añadirla a la carpeta y renombrarla como `imagen1`, `imagen2` o `imagen3` (borra la original del nombre que escojas).
> * **Asegúrate de que tenga resolución de 2048 × 3072 px**.
> * Si no es así, puedes cambiar su tamaño con esta herramienta: [https://imageresizer.com](https://imageresizer.com)


## Dependencias y Compilación

### Python

* **Librerías**: `Pillow`, `NumPy`
* **Ejecución**:

```bash
python3 crear_imagen.py
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

### Es decir:

* Si `H = 2048` y `W = 3072`, entonces `H × W = 6291456` iteraciones
* Tiempo en secuencial: `O(6291456)`
* Tiempo en paralelo ideal: `O(786432)`

**¿Por qué?**

Porque la función usa un ciclo for para revisar cada píxel y esto sólo lo hace una única vez, así que por eso únicamente se multiplican las dimensiones del problema (matriz de 2048 x 3072 x 3)

## Resultados de Pruebas

Los siguientes tiempos se midieron usando `std::chrono` en C++:

| Imagen | Paralelismo (ms) | Secuencial (ms) |
| ------ | ---------------- | --------------- |
| 1      | 16885            | 70250           |
| 2      | 27329            | 84292           |
| 3      | 22311            | 86541           |

_Las fotos de los resultados están en la carpeta tests._

## ¿Esta fue una buena solución?

Para comprobar que mi solución fue efectiva, especialmente por el número de threads que escogí (8), decidí volver a realizar pruebas pero únicamente con 4 threads, es decir, la mitad de los que se usaron originalmente. Los cuales trabajarían así:

![Diagrama 4 threads](https://github.com/XimePerezEscalante/Evidencia4_A01751827/blob/main/Diagrama4Threads.png?raw=true)

El código quedó de la siguiente manera:
```C++
std::thread s1(setDesaturatedValues, std::ref(res), 0, H/4);
std::thread s2(setDesaturatedValues, std::ref(res), H/4, H/2);
std::thread s3(setDesaturatedValues, std::ref(res), H/2, (H/4) * 3);
std::thread s4(setDesaturatedValues, std::ref(res), (H/4) * 3, H);
    
s1.join();
s2.join();
s3.join();
s4.join();
```

### Resultado de las pruebas

| Imagen | Paralelismo 4 threads (ms) | 
| ------ | ---------------- |
| 1      | 21317            | 
| 2      | 26430            | 
| 3      | 27533            |

**Conclusión**

A partir de las pruebas se comprobó que usar paralelismo redujo el tiempo de ejecución de la función que desaturaba cada pixel. En cuanto al uso de 8 vs 4 threads, se notó un menor tiempo para 2 de las 3 pruebas con aproximadamente 5000 milisegundos. La comparación de tiempo y espacio es la siguiente:

* Tiempo en paralelo ideal (8 threads): `O((H × W)/8)` = **O(786432)**
* Tiempo en paralelo ideal (4 threads): `O((H × W)/4)` = **O(1572864)**

8 threads lo reduce a la mitad, pero de igual manera debe tomarse en cuenta el tiempo necesario para la creación de cada thread, así que es más tardado crear 8 threads, que 4.

## Referencias

* Ortiz, 2020. Computación paralela: [https://www.teldat.com/es/blog/computacion-paralela-capacidad-procesamiento/](https://www.teldat.com/es/blog/computacion-paralela-capacidad-procesamiento/)
* GeeksforGeeks, 2025. Threads en sistemas operativos: [https://www-geeksforgeeks-org.translate.goog/threads-and-its-types-in-operating-system](https://www-geeksforgeeks-org.translate.goog/threads-and-its-types-in-operating-system)

