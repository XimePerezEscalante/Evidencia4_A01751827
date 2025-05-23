//
//  main.cpp
//  procesadorImagenes
//
//  Created by Ximena Perez Escalante on 18/05/25.
//

#include <iostream>
#include <thread>
#include <algorithm>
#include <fstream>
#include <chrono>

// declaracion de constantes

// altura en pixeles
#define H 2048
// ancho en pixeles
#define W 3072
// valores rgb
#define Z 3

using namespace std::chrono;

/*
 funcion que pasa el valor a gris, utiliza el valor mas
 alto para igualar los demas a ese mismo.
 input:
 arr: apuntador a un apuntador a un apuntador
 para el arreglo de enteros de tres dimensiones
 start: int,
 end: int
 */
void setDesaturatedValues(int*** arr, int start, int end) {
    int r = 0;
    int g = 0;
    int b = 0;
    
    for (int i = start; i < end; i++) {
        for (int j = 0; j < W;j++) {
            r = arr[i][j][0];
            g = arr[i][j][1];
            b = arr[i][j][2];
            // si r tiene el valor maximo
            if (r > g && r > b) {
                arr[i][j][0] = r;
                arr[i][j][1] = r;
                arr[i][j][2] = r;
            }
            // si g tiene el valor maximo
            else if (g > r && g > b) {
                arr[i][j][0] = g;
                arr[i][j][1] = g;
                arr[i][j][2] = g;
            }
            // si b tiene el valor maximo
            else if (b > r && b > g) {
                arr[i][j][0] = b;
                arr[i][j][1] = b;
                arr[i][j][2] = b;
            }
        }
    }
}

/*
 funcion que lee el archivo con los valores RGB
 de la imagen original y las pasa al arreglo,
 que es un triple apuntador.
 input:
 arr: triple apuntador de ints
 */
void readPixels(int*** arr) {
    // archivo del que se va a leer
    std::ifstream inputFile;
    // input para los valores rgb
    int r, g, b;
    // abrir el archivo
    inputFile.open("pixelespy.txt");
    
    // si esta abierto el archivo
    if (inputFile.is_open()) {
        // recorre por fila
        for (int i = 0; i < H; i++) {
            // apunta a un nuevo arreglo del ancho
            arr[i] = new int*[W];
            // recorre cada columna
            for (int j = 0; j < W;j++) {
                // ultimo apuntador para los valores RGB
                arr[i][j] = new int[Z];
                // input de tres valores
                inputFile >> r >> g >> b;
                // asigna cada valor al arreglo
                arr[i][j][0] = r;
                arr[i][j][1] = g;
                arr[i][j][2] = b;
            }
        }
    }
    else {
        std::cout << "Error al abrir el archivo" << std::endl;
    }
}

/*
 funcion que escribe los valores de la matriz en el archivo.
 input:
 arr: triple apuntador de ints
 start: posicion inicial del arreglo (fila)
 end: posicion final del arreglo (fila)
 Archivo: referencia del archivo donde se escriben los valores
 */
void writePixels(int*** arr, int start, int end, std::ofstream& Archivo) {
    for (int i = start;i < end; i++) {
        for (int j = 0;j < W; j++) {
            for (int k = 0;k < Z; k++) {
                Archivo << arr[i][j][k] << " ";
            }
        }
        // cada linea del archivo corresponde a una fila
        Archivo << "\n";
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "¡Bienvenid@!\nEste programa pasa tus imágenes a blanco y negro.";
    
    // Crear y abrir el archivo
    std::ofstream MyFile("pixeles.txt");
    
    // triple apuntador para el arreglo de tres dimensiones
    int*** res = new int**[H];
    
    //Leer los valores del archivo de la imagen original
    readPixels(res);
    
    // contar tiempo a partir de la parte paralela
    auto start = high_resolution_clock::now();
    
    /* mandar llamar la función setDesaturatedValues
     donde se hace todo de manera secuencial
    */
    setDesaturatedValues(res, 0, H);
    
    // dejar de contar el tiempo
    auto stop = high_resolution_clock::now();
    
    // calcular duracion
    auto duration = duration_cast<microseconds>(stop - start);
    
    std::cout << "\nTiempo: " <<  duration.count()  << std::endl;
    
    // Escribir los valores en el archivo
    writePixels(res, 0, H, MyFile);
    
    // Cerrar el archivo
    MyFile.close();
    
    return 0;
}
