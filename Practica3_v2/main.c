/*
ESCOM-IPN
Practica 3: Codificacion voraz de huffman
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
18-06-18
*/
#include "tiempo.c"
#include "huffman.c"

int main(int argc, char const *argv[]) {

    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    int i; //auxiliar para ciclos
    if (argc < 4) {
        printf("Faltan argumentos: Ej. e|d [e - codificar|d- decodificar] nombre_original nombre_codificado\n");
        exit(1);
    }
    init();
    if (strcmp(argv[1], "e") == 0)
        encode(argv[2], argv[3]);
    else if (strcmp(argv[1], "d") == 0)
        decode(argv[2], argv[3]);

    destruir();
    return 0;
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
