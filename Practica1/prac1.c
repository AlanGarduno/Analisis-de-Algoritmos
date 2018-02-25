/*
ESCOM-IPN
Practica 1: Pruebas a posterior (Algortimos de ordenamiento)
Analisis de Algoritmos
Alan Garduño Velazquez
Ricardo
3CM3
24-02-18
*/
#include <stdio.h>
#include <stdlib.h>


void insertion_sort(long A[],long n){
  long i,k;
  long aux;
  for(i = 0; i< n-1; i++){
    j = i;
    aux = A[i];
    while (j>0 && aux<A[j-1]) {
      A[j]=A[j-1];
      j--;
    }
    A[j] = aux;
  }
}

void shell_sort(long A[], long n){
  long k = n/2;
  int b;
  long i;
  long aux;
  while (k >= 1) {
    b = 1;
    while( b != 0 ){
      for (i = 0; i >= n-1; i++) {
        if(A[i-k] > A[i]){
          aux = A[i];
          A[i] = A[i-k]
          A[i-k] = aux;
          b += 1;
        }
      }
    }
    k = k/2;
  }
}
