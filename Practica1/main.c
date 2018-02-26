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

void main(){
 long A [] = {231231,353453,67865,2312312,534534,567567856,123123};
 long n = 7;
 long i;
 Nodo *arbol = NULL;
 printf("Arreglo sin ordenar\n");
 for(i = 0; i<7; i++){
   printf("%d\n",A[i]);
 }

  /*printf("\nInsertando datos en el arbol\n");
  for(i = 0; i<7; i++){
    insertar(&arbol,A[i]);
  }

  printf("\nArbol en inorden\n");
  inOrden(arbol);*/
  insertion_sort(A,n);
  printf("Arreglo ordenado\n");
  for(i = 0; i<7; i++){
    printf("%d\n",A[i]);
  }

}
