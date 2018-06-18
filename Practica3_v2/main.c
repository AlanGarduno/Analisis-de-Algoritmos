/*
ESCOM-IPN
Practica 3: Codificacion voraz de huffman
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
18-06-18
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.c"
#include "huffman.c"
#include "decoder.c"

int main(int argc, char const *argv[]) {

    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    int i; //auxiliar para ciclos

    if (argc < 3){
        printf("Faltan argumentos Ej. archivo 1/2 comprimir/descomprimir\n");
        exit(1);
    }

    //******************************************************************
    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    //******************************************************************
    uswtime(&utime0, &stime0, &wtime0);

    int opcion = atoi(argv[2]);
    if(opcion == 1){
        comprimir_archivo(argv[1]);
    }
    else if(opcion == 2){
        decodificar_archivo(argv[1]);
    }
    //******************************************************************

    //******************************************************************
    //Evaluar los tiempos de ejecución
    //******************************************************************
    uswtime(&utime1, &stime1, &wtime1);

    //Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");
    //******************************************************************

    exit (0);
}
