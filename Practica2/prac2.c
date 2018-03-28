#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "prac2.h"

typedef struct Param
{
	long n;
	long dato;
	long A[];
	
}PARAM;




int busquedaLineal(long A[], long n, long dato){
	long i;
	for ( i = 0; i < n;i++)
	{
		if(dato == A[i]){
			return 1;
		}
	}
	return 0;
}
int busquedaBinaria(long A[], long n, long dato){
	long centro, inf=0, sup= n-1;
	while(inf <= sup){
		centro = ((sup-inf)/2)+inf;
		if(A[centro] == dato){
			return 1;
		}
		else if(dato < A[centro]){
			sup= centro-1;
		}
		else{
			inf = centro+1;
		}
	}
	return 0;
}

void *bLineal(void* param){
	PARAM *p = (PARAM*)param;
	long i;
		for ( i = 0; i < p->n;i++)
	{
		if(p->dato == p->A[i]){
			printf("El dato %ld se encuenta en la coleccion",p->dato);
			return;
		}
	}
	printf("El dato %ld no se encuenta en la coleccion",p->dato);


}
void *bBinaria(void* param){
	PARAM *p = (PARAM*)param;
	long centro, inf=0, sup= p->n-1;
	while(inf <= sup){
		centro = ((sup-inf)/2)+inf;
		if(p->A[centro] == p->dato){
			printf("El dato %ld se encuenta en la coleccion",p->dato);
			return;
		}
		else if(p->dato < p->A[centro]){
			sup= centro-1;
		}
		else{
			inf = centro+1;
		}
	}
	printf("El dato %ld no se encuenta en la coleccion",p->dato);
}