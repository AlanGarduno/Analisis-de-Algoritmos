#include <stdio.h>
#include <stdlib.h>
#include "huffman.c"


int main(int argc, char const *argv[]) {
  if(argc < 4){
    printf("Faltan parametros.\n");
    printf("Codificacion:\n");
    printf("nombre_archivo nombre_archivo_codificado 1\n");
    printf("Decodificacion\n");
    printf("nombre_archivo_codificado nombre_archivo 2 \n");
    exit(1);
  }
  char *nombreArchivoOriginal = (char*)argv[1];
  char *nombreArchivoNuevo = (char*)argv[2];
  int op = atoi(argv[3]);
  if( op == 1 )
    codificar(nombreArchivoOriginal, nombreArchivoNuevo);
  else
    //Funcion decodificar
  return 0;
}
