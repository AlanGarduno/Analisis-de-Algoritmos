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


void selection_sort(long A[],long n){
  long k,p,i,aux;
  for(k = 0; k <= n-2; k++){
    p = k;
    for(i = k+1; i<= n-1; i++){
      if(A[i] < A[p] ){
        p = i;
      }
    }
    aux = A[p];
    A[p] = A[k];
    A[k] = aux;
  }
}

void shell_sort(long A[], long n){
  long int gap = n/2;
  long int inner, outer, swap;
  while (gap > 0) {
    for(outer = gap; outer < n; outer++){

      inner = outer;
      swap = A[inner];
      while (inner > gap - 1 && A[inner - gap] > swap ) {
        A[inner] = A[inner - gap];
        inner -= gap;
      }
      A[inner] = swap;
    }
    gap /=2;
  }
}
