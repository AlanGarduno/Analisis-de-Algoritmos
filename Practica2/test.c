#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.c"
#include "prac2.c"

int main(int argc, char const *argv[])
{
	long A[] = {1213,3412421,54546,324233,55555,131313,453546,665788,2311231};
	long dato = 55555;

	long i;
	Nodo *arbol;
	for (i = 0; i < 9; i++)
		insertar(&arbol,A[i]);

	if(buscar(arbol,dato) == 1)
		printf("El dato %d pertenece a la coleccion\n",dato);
	else
		printf("El dato %d  no pertenece a la coleccion\n",dato);
	return 0;
}