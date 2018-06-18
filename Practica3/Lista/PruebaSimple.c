#include<stdio.h>
#include "TADListaSL.h"
#define TAM_ALPHABET 26

//Función para imprimir el elemento de la lista con base en mi estructura elemento
void ImprimeLista(lista *l);

//PROGRAMA PRINCIPAL
int main (void)
{
	lista mi_lista; //Mi lista 
	posicion aux;	//Posición auxiliar para manejar la lista
	elemento e;		//Elemento e
	
	int i;			//Para manejar los ciclos
	//int a,b;		//Variables enteras auxiliares
	
	Initialize(&mi_lista); //Inicializar la lista
	
	//Insertar TAM_ALPHABET elementos al frente o atras de la lista "Caracteres 'A' 'B'"
	for(i=0;i<TAM_ALPHABET;i++)
	{
		//Llenar el elemento
		e.c='A'+i;
		
		//Insertar al frente de la lista
		//aux=First(&mi_lista);
		//Insert(&mi_lista,e,aux,ADELANTE);		
		
		//Insertar al final de la lista
		Add(&mi_lista,e);		
	}
	
	//Ver la lista**********
	printf("\nLista Inicial");
	ImprimeLista(&mi_lista);
	
	//Eliminar el primero de la lista y el ultimo
	aux=First(&mi_lista);
	Remove(&mi_lista,aux);		

	aux=Final(&mi_lista);
	Remove(&mi_lista,aux);		
	
	//Ver la lista**********
	printf("\nLista despues de remover el primero y el ultimo");
	ImprimeLista(&mi_lista);


	//Remover al elemento 10 de la lista si existe
	
	//Forma 1 (Recorrer del inicio al final la posicion)
	aux=First(&mi_lista);
	for(i=1;i<10;i++)
	{
		aux=Following(&mi_lista,aux);
	}
	
	//Remover al elemento de posición aux si aux es valida
	if(ValidatePosition(&mi_lista,aux))
		Remove(&mi_lista,aux);
	
	//Forma 2 (Obtener directamente la posicion del elemento 10)
	aux=ElementPosition(&mi_lista,5);
	
	//Remover al elemento de posición aux si aux es valida
	if(ValidatePosition(&mi_lista,aux))
		Remove(&mi_lista,aux);
	
	//Ver la lista**********
	printf("\nLista despues de remover al elemento 10 y al 5 de la lista si existe");
	ImprimeLista(&mi_lista);
abort	
	//Remplazar a un elemento con el caracter 'T' si existe
	printf("\nLista despues buscar a T y remplazar por t");
	elemento a;
	a.c='T';
	aux=Search(&mi_lista,a);
	if(ValidatePosition(&mi_lista,aux))
	{
		e.c='t';
		Replace(&mi_lista,aux,e);	
	}
	
	
	//Ver la lista**********
	//Lista despues de remplazar al elemento con un char 'T' de la lista si existe
	ImprimeLista(&mi_lista);

	return 0;
}


//Función para imprimir el elemento de la lista con base en mi estructura elemento
void ImprimeLista(lista *l)
{
	posicion p;
	elemento e;
	int i;
	
	//Recorrer e imprimir los elementos mientras se tenga una posición valida
	p=First(l);		//Iniciamos por el primero de la lista
	
	//Mientras la posición sea valida
	for(i=1;ValidatePosition(l,p);i++)
	{
		e=Position(l,p);		
		printf("\nElemento %d\t%c",i,e.c);
		p=Following(l,p);
	}
	return;	
}
