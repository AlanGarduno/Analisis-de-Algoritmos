#include<stdio.h>
#include "TADListaSL.h"

//Compilar gcc main.c TADLista/TADListaSL.c -o main

int main (void)
{
	lista A,B,C;
	posicion p1,p2,p3;
	elemento e1,e2;
	char c;
	int i,j;
	
	Initialize(&A);
	Initialize(&B);
	Initialize(&C);
	
	c=getchar();
	
	//Llenar la primera de caracteres A	
	while(c!='\n')
	{
		e1.c=c;
		Add(&A,e1);						
		c=getchar();
	}
	

	c=getchar();
	//Llenar la primera de caracteres B
	while(c!='\n')
	{
		e1.c=c;
		Add(&B,e1);						
		c=getchar();
	}
	
	//Buscar elementos de A en B
	p1=First(&A);	
	while(ValidatePosition(&A,p1))
	{
		e1=Position(&A,p1);
		printf("\n%c",e1.c);
		p2=Search(&B,e1);
		if(p2!=NULL)//Como encontro e entonces eliminar de A y de B e insertar en C
		{
			//Eliminar de A
			p3=Following(&A,p1);	
			Remove(&A,p1);
			//Eliminar de B
			Remove(&B,p2);
			//Inserta en C
			Add(&C,e1);
			p1=p3;
		}
		else
		{
			p1=Following(&A,p1);		
		}
	}

		
	//Imprimir la lista A
	printf("\nLISTA A\n");
	p1=First(&A);	
	for(;ValidatePosition(&A,p1);)
	{
		e1=Position(&A,p1);
		printf("\t%c",e1.c);
		p1=Following(&A,p1);		
	}

	//Imprimir la lista B
	p1=First(&B);	
	printf("\nLISTA B\n");
	while(ValidatePosition(&B,p1))
	{
		e1=Position(&B,p1);
		printf("\t%c",e1.c);
		p1=Following(&B,p1);		
	}

	//Imprimir la lista C
	p1=Final(&C);
	printf("\nLISTA C\n");	
	for(i=0;i<Size(&C);i++)
	{
		e1=Position(&C,p1);
		printf("\t%c",e1.c);
		p1=Previous(&C,p1);		
	}
	
	//Ver las ligas de las listas (DEPURAR)
	printf("\nLista A (Nodos y Siguientes)");
	VerLigasLista(&A);

	printf("\nLista B (Nodos y Siguientes)");
	VerLigasLista(&B);

	printf("\nLista C (Nodos y Siguientes)");
	VerLigasLista(&C);
	

	//Destruir la lista A
	Destroy(&A);
	
	//Destruir la lista B
	Destroy(&B);
	
	//Destruir la lista C
	Destroy(&C);
	
	return 0;
}
