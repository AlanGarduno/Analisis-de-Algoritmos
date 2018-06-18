#include "huffman.h"

FILE * abrir_archivo(char * nombre_archivo){
  FILE * arch = fopen(nombre_archivo,"rb");
  if(arch == NULL){
    printf("No es posible abrir el archivo %s\n",nombre_archivo);
    exit(1);
  }
  return arch;
}
void codificar(char* nombreArchivoOriginal, char* nombreArchivoNuevo){
  lista TablaFrecuencias;
  lista frecuenciasOrdenadas;
  elemento e;
  unsigned char elem;
  posicion pos;
  Initialize(&TablaFrecuencias);
  FILE * archivo = abrir_archivo(nombreArchivoOriginal);
  while (!feof(archivo)) {
    fread(&elem,sizeof(char),1,archivo);
    e.c = elem;
    pos = busca_elemento(&TablaFrecuencias,e);

    if( pos != NULL){
      (pos->e).frecuencia++;
    }
    else{
      e.frecuencia = 1;
      Add(&TablaFrecuencias,e);
    }
  }
  imprimir_lista(&TablaFrecuencias);

  frecuenciasOrdenadas = ordenar_lista(&TablaFrecuencias);

}
