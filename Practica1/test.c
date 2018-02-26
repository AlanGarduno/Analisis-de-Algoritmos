/*
ESCOM-IPN
Practica 1: Pruebas a posterior (Algortimos de ordenamiento)
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
24-02-18
*/
#include <stdio.h>
#include <stdlib.h>
#include "prac1.c"
#include "ABB/sbt.c"

void elegir_algoritmo(long A[], long n, int op);

int main(int argc, char *argv[]){
  if(argc != 3){
    printf("Faltan argumentos ej: n(100000) con 1<=n<=10,000,000 y el path del archivo fuente (Desktop/numeros.txt) \n");
  }
  else{
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
    printf("Leyendo datos...\n");
    for(i = 0; i<n;i++){
      fgets(buffer,20,archivo);
      aux =  atol(buffer);
      A[i] = aux;
      printf("%d\n",A[i]);
    }
  }

}

void elegir_algoritmo(long A[], long n, int op){
  int i;
  printf("Elije el algortimo de tu preferencia\n1.Burbuja\n2.Burbuja Optimizada\n3.Selection Sort\n4.Insertion sort\n5.Shell sort\n6.ABB\n");
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
      Nodo *arbol = NULL;
      for(i = 0; i<n; i++){
        insertar(&arbol,A[i]);
      }
      inOrden(arbol);
    break;

  }
}

void print(long A[], long n){
  int i = 0;
  for(int i = 0; i<n; i++){
    printf("%d\n",A[i]);
  }
}
