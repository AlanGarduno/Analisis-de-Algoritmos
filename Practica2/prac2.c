#include <stdlib.h>
#include <stdio.h>
#include "prac2.h"


/*Estructura para pasar parametros a los hilos (procesos ligeros)*/
typedef struct Param
{
	long n;
	long dato;
	long *A;
	
}PARAM;



/*Implementacion del algoritmo de busqueda lineal
recibe: Arreglo A, n que es el tamaño de a y dato que es el dato a buscar en A
retorna: 1 si dato se encuentra en A, 0 si no es asi.
*/
int busquedaLineal(long A[], long n, long dato){
	long i; //variable auxiliar para el ciclo 
	for ( i = 0; i < n;i++) 
	{
		if(dato == A[i]){ //Condicional que compara el valor que se esta buscando y el valor
						 //Actual de A
			return 1; // Se retorna 1 si la condicion se cumple
		}
	}
	return 0; //se retorna 0 si no es asi.
}


/*Implementacion del algortimo de busqueda binaria
recibe: Arreglo A, n que es el tamaño de a y dato que es el dato a buscar en A
retorna:  1 si dato se encuentra en A, 0 si no es asi.
*/
int busquedaBinaria(long A[], long n, long dato){
	long centro, inf=0, sup= n-1; //Variables auxiliares para el uso
	while(inf <= sup){ //Cilco que se repite mientras se cumpla la condicion inf <= sup
		centro = ((sup-inf)/2)+inf;
		if(A[centro] == dato){
			return 1;  //Si la condicion se cumple se retorna 1
		}
		else if(dato < A[centro]){
			sup= centro-1; // Si la condicion se cumple se actualiza el valor de sup
		}
		else{
			inf = centro+1; // Si la condicion se cumple se actualiza el valor de inf
		}
	}
	return 0; //Se retorna 0 si el ciclo termina 
}



/*Adaptaciones de las funciones anteriores para trabajar con procesos ligeros
Al ser una adaptacion su funcionamiento es identico, solo varian en el tipo 
de retorno y la manera en la que se reciben los parametros
*/

void *bLineal(void* param){
	PARAM *p = (PARAM*)param;
	long i;
		for ( i = 0; i < p->n;i++)
	{
		if(p->dato == p->A[i]){
			printf("El dato %ld se encuenta en la coleccion\n",p->dato);
			return (void*)1;
		}
	}
	printf("El dato %ld no se encuenta en la coleccion\n",p->dato);


}
void *bBinaria(void* param){
	PARAM *p = (PARAM*)param;
	long centro, inf=0, sup= p->n-1;
	while(inf <= sup){
		centro = ((sup-inf)/2)+inf;
		if(p->A[centro] == p->dato){
			printf("El dato %ld se encuenta en la coleccion\n",p->dato);
			return (void*)1;
		}
		else if(p->dato < p->A[centro]){
			sup= centro-1;
		}
		else{
			inf = centro+1;
		}
	}
	printf("El dato %ld no se encuenta en la coleccion\n",p->dato);
}