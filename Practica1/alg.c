/*
ESCOM-IPN
Practica 1: Pruebas a posterior (Algortimos de ordenamiento)
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
24-02-18
Compilacion: gcc test.c
Ejecucion:
Windows:a  1000 nums.txt 2, donde 1000 es n nums.txt es el archivo de donde se obtienen los datos y 2 es el algortomo a usar en este caso Obs
OSX/Linux:./a 1000 nums.txt 2, idem
Opciones de algortimos a seleccionar a traves de parametro:
1.Bubble sort
2.Optimized bubble sort
3.Selection soort
4.Insertion sort
5.Shell sort
6.ABB
*/
#include <stdio.h>
#include <stdlib.h>
#include "prac1.c"
#include "ABB/sbt.c"
#include "tiempo/tiempo.c"


//Variables globales para la medicion del tiempo de ejecucion
double utime0, stime0, wtime0,utime1, stime1, wtime1;

/*Funcion para eleegir el algortimo de ordenamiento
Recibe: A el arrgelo de numeros de tipo long, n que es el tamaño del arreglo A, y op que es una varible para determina que
algoritmo ejecutar*/
void elegir_algoritmo(long A[], long n, int op);

/*Funcion que imprime un arrgelo
Recibe: A un puntero a un arreglo y n la longitud del mismo*/
void print(long A[], long n);

int main(int argc, char *argv[]){
  if(argc != 4){ //Se validan si se ingresaron los argumentos suficientes
    printf("Faltan argumentos ej: n(100000) con 1<=n<=10,000,000 y el path del archivo fuente (Desktop/numeros.txt)  op: Que algoritmo se ejecutara\n");
  }
  else{
    int op = atoi(argv[3]); //Se convierte a entero el argument0 4
    long i = 0;// variable auxiliar
    char buffer[20];//Buffer 
    FILE *archivo; //Puntero a archivo
    long n = atol(argv[1]); //Se convierte el primer argumento n a long con la funcion atol
    long *A = (long*)calloc(n,sizeof(long)); //Se crea el arreglo dinamico de n elementos
    archivo = fopen(argv[2],"r"); // Se abre el archivo en modo lectura
    if(archivo == NULL){ //Se valida si fue posible abrir el archivo
      printf("No fue posible abrir el archivo\n"); 
      exit(1);
    }
    long r = n;
    long aux;
    printf("Leyendo datos...\n");
    for(i = 0; i<n;i++){ //Se lleen los datos del archivo linea por liena
      fgets(buffer,20,archivo);
      aux =  atol(buffer);
      A[i] = aux;
      //printf("%d\n",A[i]);
    }
    elegir_algoritmo(A,n,op); // Se ejecuta la fucnion elejir_algoritmo
  }

}

void elegir_algoritmo(long A[], long n, int op){
  int i;
  Nodo *arbol = NULL;
  switch (op) {
    case 1:
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      bubble_sort(A,n); //Ejecucion del algoritmo burbuja
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
      	//Cálculo del tiempo de ejecución del programa
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
	//******************************************************************
      //print(A,n); //Se imprime el arreglo ordenado

    break;
    case 2:
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      Obubble_sort(A,n); //Ejecucion del algortimo burbuja mejorado
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
      //Cálculo del tiempo de ejecución del programa
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
      //print(A,n); // impresion Arreglo ordenado
    break;
    case 3:
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      selection_sort(A,n); //ejecucion del selection sort
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
      //print(A,n); //impresion de arreglo ordenado
    break;
    case 4:
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      insertion_sort(A,n); //ejecucion del insertion sort
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
      //print(A,n); //impresion de arreglo oerdenado
    break;
    case 5:
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      shell_sort(A,n); //ejecucion del shell sort
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
      //print(A,n);//impresion de arreglo oerdenado
    break;
    case 6:
      for(i = 0; i<n; i++){ //insertando los datos en el arreglo 
        insertar(&arbol,A[i]);
      }
      uswtime(&utime0, &stime0, &wtime0); //Se comienza a medir el tiempo
      inOrden(arbol); //Recorrido en inOrden del arbol binario
      uswtime(&utime1, &stime1, &wtime1); // Se Evaluan los tiempos
	    printf("\n");
	    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    printf("\n");
  	//Mostrar los tiempos en formato exponecial
	    printf("\n");
	    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	    printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	    //printf("\n");
    break;

  }
}



void print(long A[], long n){
  int i = 0;
  for(int i = 0; i<n; i++){
    printf("%d\n",A[i]);
  }
}
