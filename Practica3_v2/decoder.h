#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_BUFFER 8000
#define TAM_BUFFER_ARBOL 3000

struct arbol_decodificador{
    unsigned int valor_real;
    struct arbol_decodificador * hijo_izq;
    struct arbol_decodificador * hijo_der;
};

struct info_archivo{
    char * nombre;
    long tam;
    char * extension;
};

int decodificar_archivo(char *);
struct info_archivo * construir_arbol(FILE *, struct arbol_decodificador **);
int insertar_nodo_arbol(struct arbol_decodificador **, int, char *, int);
int construir_archivo(struct arbol_decodificador *, char *, char *);
unsigned int obtener_valor(int, unsigned char *, int *, struct arbol_decodificador *);
int obtener_bit(unsigned char *, int);
int llenar_info_archivo(struct info_archivo *, char *);
int iniciar_arbol(struct arbol_decodificador **);
