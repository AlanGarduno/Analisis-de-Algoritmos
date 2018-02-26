#include <stdlib.h>
#include <stdio.h>
#include "sbt.h"


Nodo* crearNodo(long int n){
  Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
  nuevoNodo->valor = n;
  nuevoNodo->izq = NULL;
  nuevoNodo->der = NULL;
  return nuevoNodo;
}

void destruitNodo(Nodo *nodo){
  nodo->der = NULL;
  nodo->izq = NULL;
  free(nodo);
}

void insertar(Nodo **arbol, long int valor){
  if(*arbol == NULL){
    Nodo* nuevoNodo = crearNodo(valor);
    *arbol = nuevoNodo;
  }else{
    int valorRaiz = (*arbol)->valor;
    if(valor < valorRaiz){
      insertar(&(*arbol)->izq,valor);
    }
    else{
      insertar(&(*arbol)->der,valor);
    }
  }
}

void inOrden(Nodo *arbol){
  if(arbol == NULL)
      printf(" - ");
  else{
    inOrden(arbol->izq);
    printf("%d\n",arbol->valor);
    inOrden(arbol->der);
  }
}
