/*
ESCOM-IPN
Analisis de Algortimos Grupo: 3CM3
Practica 2: Analisis temporal y notacion de orden
Autores:
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia

Fecha de elaboracion: 17.03.18
Version: 1

*/
#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.c"
#include "prac2.c"

void selc_algortimo(long* A,long n, long dato, int h, int op);

int main(int argc, char const *argv[])
{
	if(argv < 5)
	{
		printf("Faltan argumentos: 
				1 -> path del data set
				2 -> Numero a buscar 
				3 -> Tamaño de n 
				4 -> Algortmo a utilizar 
				5 -> Con/sin hilos. 
				Ej nums.txt 1000 10000 2 0 
				Donde: 
				nums.txt es el path del data set
				1000 es el numero a buscar
				10000 es el tamaño de n
				2 es el algortimo a usar
				y 0 es que no se usaran hilos\n");
				exit(0);
	}
	long i = 0;
    char buffer[20];
	FILE* archivo;
	long dato = atol(argv[2]);
	long n = atol(argv[3]);
	int op = atoi(argv[4]);
	int hilo = atoi(argv[5]);

	long *A = (long*)calloc(n,sizeof(long));
	archivo = fopen(argv[1],"r");
    if(archivo == NULL){
      printf("No fue posible abrir el archivo\n");
      exit(1);
    }

    long aux;
    for(i = 0; i<n;i++){
      fgets(buffer,20,archivo);
      aux =  atol(buffer);
      A[i] = aux;
    }

    selc_algortimo(A,n,dato,hilo,op);

	return 0;
}

void selc_algortimo(long* A,long n, long dato, int h, int op){
	Nodo *arbol = NULL;
	long i;
	switch(op){
		case 1:
			if(h == 0){
				if(busquedaLineal(A,n,dato))
					printf("El dato %d se encuentra en la coleccion\n",dato);
				else
					printf("El dato %d no se encuentra en la coleccion\n",dato);
			}
			else{
				//Ejecucion con hilos
			}
		break;
		case 2:
			if(h == 0){
				if(busquedaBinaria(A,n,dato))
					printf("El dato %d se encuentra en la coleccion\n",dato);
				else
					printf("El dato %d no se encuentra en la coleccion\n",dato);
			}
			else{
				//Ejecucion con hilos
			}
		break;
		case 3:
			for (i = 0; i < n; i++) //Insertando los datos en el arbol
				insertar(&arbol,A[i]);

			if(h == 0){
				if(buscar(arbol,dato))
					printf("El dato %d se encuentra en la coleccion\n",dato);
				else
					printf("El dato %d no se encuentra en la coleccion\n",dato);
			}
			else{
				//Ejecucion con hilos
			}
		break; 
	}

}