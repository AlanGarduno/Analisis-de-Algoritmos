/*
ESCOM-IPN
Practica 1: Pruebas a posteriori (Algortimos de ordenamiento)
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
24-02-18
*/
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(long A[],long n){
	long aux;
	for (long i = 0; i <= n-2; i++)
		for (long j = 0; j <= (n-2)-i; j++)
			if (A[j]>A[j+1])
			{
				aux=A[j];
				A[j]=A[j+1];
				A[j+1]=aux;
			}
}

void Obubble_sort(long A[], long n){
	char cambios=1;
	long i=0,aux;
	while(i < n-1 && cambios != 0){
		cambios=0;
		for (int j  = 0; j <= (n-2)-i; j++)
			if (A[j]>A[j+1])
			{
				aux=A[j];
				A[j]=A[j+1];
				A[j+1]=aux;
				cambios=1;
			}
		i++;
	}
}

void insertion_sort(long A[], long n){
	long int i,j,temp;
	for(i = 0; i <= n-1; i++){
		j = i;
		while (j >0 && A[j] < A[j-1]) {
			temp = A[j];
			A[j] = A[j-1];
			A[j-1] = temp;
			j--;
		}
	}
}

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
