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
#include "tiempo/tiempo.h"
#include "prac1.c"
#include "ABB/sbt.c"
#include "tiempo/tiempo.c"


void elegir_algoritmo(long A[], long n, int op);
void print(long A[], long n);

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Faltan argumentos ej: n(100000) con 1<=n<=10,000,000 y el path del archivo fuente (Desktop/numeros.txt)  op: Que algoritmo se ejecutara\n");
  }
  else{
    int op = atoi(argv[3]);
    long i = 0;
    char buffer[20];
    FILE *archivo;
    long n = atol(argv[1]); //Se convierte el primer argumento n a long con la funcion atol
    long *A = (long*)calloc(n,sizeof(long)); //Se crea el arreglo dinamico de n elementos
    archivo = fopen(argv[2],"r");
    if(archivo == NULL){
      printf("No fue posible abrir el archivo\n");
      exit(1);
    }
    long r = n;
    long aux;
    for(i = 0; i<n;i++){
      fgets(buffer,20,archivo);
      aux =  atol(buffer);
      A[i] = aux;
      //printf("%d\n",A[i]);
    }
    elegir_algoritmo(A,n,op);
    printf("%d.-\t%ld\t",op,n);
    printf("%.10f\t%.10f\t%.10f\t%.10f\n", wtime1-wtime0, utime1-utime0, stime1-stime0, 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    if(op == 6)
      printf("\n");
  }

}

void elegir_algoritmo(long A[], long n, int op){
  int i;
  Nodo *arbol = NULL;
  switch (op) {
    case 1:
      bubble_sort(A,n);
      print(A,n);
    break;
    case 2:
      Obubble_sort(A,n);
      print(A,n);
    break;
    case 3:
      selection_sort(A,n);
      print(A,n);
    break;
    case 4:
      insertion_sort(A,n);
      print(A,n);
    break;
    case 5:
      shell_sort(A,n);
      print(A,n);
    break;
    case 6:
      for(i = 0; i<n; i++){ //insertando los datos en el arreglo 
        insertar(&arbol,A[i]);
      }
      //******************************************************************  
      //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
      //******************************************************************  
      uswtime(&utime0, &stime0, &wtime0);
      inOrden(arbol,A);
      //******************************************************************  
      //Evaluar los tiempos de ejecución 
      //******************************************************************
      uswtime(&utime1, &stime1, &wtime1);
      //print(A,n);
    break;

  }
}


/*Funcion que imprime un arrgelo
Recibe: A un puntero a un arreglo y n la longitud del mismo*/
void print(long A[], long n){
  int i = 0;
  for(int i = 0; i<n; i++){
    printf("%ld\n",A[i]);
  }
}
