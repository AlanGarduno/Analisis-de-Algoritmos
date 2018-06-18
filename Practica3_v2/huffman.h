/*Cabecera de la estructura del algortimo de huffman*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
* Tam. maximo de bytes que se van a leer y escribir
*/
int bits_buffer;
unsigned char buffer_salida[256];
const unsigned char *VALORES[257];


/*Estrctura que nos funcionara como nodo tanto de un TAD arbol binario como de un TAD lista SE*/
typedef struct Nodo {
    int numero;
    unsigned long long frecuencia;
    struct Nodo *izq;
    struct Nodo *der;
    struct Nodo *siguiente;
}Nodo;

/*
* Funcion que inserta un nodo de forma ordenada en una lista,
* recibe una lista, el valor a insertar
* y devuelve una nueva lista ordenada
*/
 Nodo *Add(Nodo *, unsigned long long, int);
 
void construir_tabla(struct Nodo *, char *);

void llenar_tabla(struct Nodo *, char *, int, FILE *);

void agregar_simbolo_tabla(int, char *, int, FILE *);

ssize_t obtener_tam_archivo(char *archivo);

Nodo *crear_arbol(struct Nodo *);

void escribir_bit(int, int);

int comprimir_archivo(char *);

void crear_comprimido(char *);
