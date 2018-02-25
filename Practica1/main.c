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

void main(){
 long A [] = {231231,353453,67865,2312312,534534,567567856,123123};
 long n = 7;
 long i;
 printf("Arreglo sin ordenar\n");
 for(i = 0; i<7; i++){
   printf("%d\n",A[i]);
 }
  shell_sort(A,n);
  printf("\nArreglo ordenado\n");
  for(i = 0; i<7; i++){
    printf("%d\n",A[i]);
  }
}
