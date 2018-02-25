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

void bubble_sort(int A[],long n){
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

void Obubble_sort(int A[], long n){
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


void selection_sort(int A[], long n){
	long p, 
  long temp;
	for (long k = 0; k < n-1; k++)
	{
		p=k;
		for (long i = k+1; i < n; i++)
			if (A[i] < A[p])
				p=i;
		temp=A[p];
		A[p]=A[k];
		A[k]=temp;
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


