#include <stdlib.h>
#include <stdio.h>
#include "abb.h"

typedef struct PA
{
  Nodo *arbol;
  long n;
}PA;

/*Funcion que crea un nodo a partir de un entero n
Recibe: un long int n
Devuelve: Un puntero al nodo creado
*/
Nodo* crearNodo(long int n){
  Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); //Se reserva memoria para el nodo
  nuevoNodo->valor = n; //Se asigna al atributo valor del TAD a n 
  nuevoNodo->izq = NULL; //Atributo izq a null
  nuevoNodo->der = NULL; //Atributo der a null
  return nuevoNodo; // Se devuelve el nodo 
}

/*Fucnion que destruye un nodo
Recibe: Un puntero a el nodo que se desea eliminar
Devuelve: Nada
*/
void destruirNodo(Nodo *nodo){
  nodo->der = NULL; //Atributo izq a null
  nodo->izq = NULL; //Atributo izq a null
  free(nodo); //Se libera la memoria que ocupaba el nodo
}

/*Funcion que inserta un nodo
Recibe: La direccion de memoria de un puntero a un arbol y un long int n
Devuelve: Nada
*/

/*Funcion que inserta un nodo
Recibe: La direccion de memoria de un puntero a un arbol y un long int n
Devuelve: Nada
*/
void insertar(Nodo **arbol, long int valor){
  if(*arbol == NULL){ //Condicion para revisar si el arbol es nulo
    Nodo* nuevoNodo = crearNodo(valor); //Si es asi se crea el nodo a partir del dato n (valor)
    *arbol = nuevoNodo; //Y se hace al nodo recien creado al raiz del arbol
  }else{ //Si no es asi entonces el arbol no esta vacio, se hace lp siguiente
    int valorRaiz = (*arbol)->valor; //Se guada el valor de la raiz
    if(valor < valorRaiz){ //Si el valor es menor que la raiz
      insertar(&(*arbol)->izq,valor); //Se recorre el arbol hacia la izquierda hasta insertarlo
    }
    else{
      insertar(&(*arbol)->der,valor); //Si es mayor se recorre el arbol hacia la derecha hasta insertarlo 
    }
  }
}

/*Fucncion de recorido inorden
Recibe: Un punetro a la raiz del arbol, un arreglo A*/
void inOrden(Nodo *arbol, long A[]){
  static int i=0; //Variable auxiliar
  if(arbol == NULL); //Si el arbol es nulo no hace nada
  else{
    inOrden(arbol->izq,A);//Recoore el arbol por su lado izquierdo hasta llegar a un nodo hoja
    A[i++]=arbol->valor; //Se va ordenando el arreglo 
    inOrden(arbol->der,A);// Recorre el arbol por su lado derecho hasta llegar a un nodo hoja
  }
}

int buscar(Nodo* a, long n){
	Nodo *arbol = a;
	while(arbol != NULL){
		if(n == arbol->valor)
			return 1;
		if(n > arbol->valor)
			arbol = arbol->der;
		else
			arbol = arbol->izq;
	}
	return 0;
}

void* buscarArbol(void *p){
  PA *pa = (PA*)p;
  Nodo *a = pa->arbol;
    while(a != NULL){
    if(pa->n == a->valor)
      return (int*)1;
    if(pa->n > a->valor)
      a = a->der;
    else
      a = a->izq;
  }
  return (int*)0;
}