#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*Variables globales*/
int num_active = 0;
int num_alphabets = 256;
int *frecuencia = NULL;
unsigned int tam_orginal = 0;

Nodo *nodes = NULL;
int num_nodos = 0;
int *hoja_index = NULL;
int *padre_index = NULL;

int free_index = 1;

int *stack;
int stack_top;

unsigned char buffer[TAM_MAX];
int bits_in_buffer = 0;
int current_bit = 0;

int eof_input = 0;
/*Funcion: determinar_frecuencia
Recibe: puntero a descriptor de archivo
Devuelve:
Determina la frecuencia de un carcater c dentro de un archivo
Solo conseidera cractres con valor ASCII*/
void determinar_frecuencia(FILE *f){
  int c;
  while((c = fgetc(f) != EOF)){
    ++frecuencia[c];
    ++original_size;
  }
  for(c = 0; c < num_alphabets; c++)
    if(frecuencia[c] > 0)
      num_active++;
}
/*Funcion init
Recibe:
Devuelve:
Inicializa los valores del arreglo deonde se guardan las frecuencias
y el indecide de las hojas del arbol codificador
*/
void init(){
  frecuencia = (int*)calloc(2*num_alphabets,sizeof(int));
  hoja_index = frecuencia + num_alphabets -1;
}

/*Funcion init_arbol
Recibe:
Devuelve:
Reserva memoria para los nodos del arbol codificador
y calcula el nuemro de nodos padre
*/
void init_arbol(){
  nodes = (Nodo*)calloc(2*num_active,sizeof(Node));
  padre_index = (int*)calloc(num_active,sizeof(int));
}

/*Funcion destruir
Recibe:
Devuelve:
Libera la memoria reservada
*/
void destruir(){
  free(padre_index);
  free(frecuencia);
  free(nodes);
}

/*
Funcion add_nodo
Recibe: int index que es el indice donde se va a agregar
int weight el dato que se va a guardar en este caso es la frecuencia
Devuelve: El indice del nodo agregado
Agrega in nodo al arbol
*/
int add_nodo(int index, int weight){
  int i = num_nodos++;
  while (i > 0 && nodes[i].weight > weight) {
    memcpy(&nodes[i+1], &nodes[i], sizeof(Node));
    if(nodes[i].index < 0)
      ++hoja_index[-nodes[i].index];
    else
      ++padre_index[nodes[i].index];

    --i;
  }

  i++;
  nodes[i].index = index;
  nodes[i].weight = weight;
  if(index < 0)
    hoja_index[-index] = i;
  else
    padre_index[index] = i;

  return i;
}

/*Funcion add_hoja
Recibe:
Devuelve:
Funcion complementaria a add_node*/
void add_hoja(){
  int i, freq;
  for(i = 0; i < num_alphabets; i++ ){
    freq = frecuencia[i];
    if(freq > 0)
      add_nodo(-(i+1), freq);
  }
}
/*Funcion build_tree
Recibe:
Devuelve:
Contruye el arbol con base al numero de nodos caluclado previamente*/
void build_tree(){
  int a,b,index;
  while (free_index < num_nodos) {
    a = free_index++;
    b = free_index++;
    index = add_nodo(b/2, nodes[a].weight + nodes[b].weight);
    padre_index[b/2] = index;
  }
}

/*Funcion: encode
Recibe: nombre del archivo a encodear y nombre del archivo de salida
Retorna: -1 si no se tuvo exito 0 si se tuvo exito*/
int encode(const char* ifile, const char *ofile){
  FILE *fin, *fout;
  if ((fin = fopen(ifile, "rb")) == NULL) {
      perror("Error: ");
      return -1;
  }
  if ((fout = fopen(ofile, "wb")) == NULL) {
      perror("Error: ");
      fclose(fin);
      return -1;
  }

  determinar_frecuencia(fin);
  stack = (int*)calloc(num_active- 1,sizeof(int));
  init_arbol();
  add_hoja();
  write_header(fout);
  build_tree();
  fseek(fin,0,SEEK_SET);
  int c;
  while ((c = fgetc(fin) != EOF))
    encode_alphabet(fout,c);
  flush_buffer(fout);
  free(stack);
  fclose(fin);
  fclose(fout);

  return 0;

}
/*Funcion encode_alphabet
Recibe: Puntero a descriptor y caracter c
Devuelve: */
void encode_alphabet(FILE *fout, int c){
  int node_index;
  stack_top = 0;
  node_index = hoja_index[c + 1];
  while(node_index < num_nodos){
    stack[stack_top++] = node_index % 2;
    node_index = padre_index[(node_index+1)/2];
  }
  while(--stack_top > -1 )
    write_bit(fout,stack[stack_top]);
}
/*Funcion: decode
Recibe: nombre del archivo a encodear y nombre del archivo de salida
Retorna: -1 si no se tuvo exito 0 si se tuvo exito*/

int decode(const char* ifile, const char *ofile) {
    FILE *fin, *fout;
    if ((fin = fopen(ifile, "rb")) == NULL) {
        perror("Error: ");
        return -1;
    }
    if ((fout = fopen(ofile, "wb")) == NULL) {
        perror("Error: ");
        fclose(fin);
        return -1;
    }

    if (read_header(fin) == 0) {
        build_tree();
        decode_bit_stream(fin, fout);
    }
    fclose(fin);
    fclose(fout);

    return 0;
}


/*Funcion: decode_bit_stream
Recibe: nombre del archivo a encodear y nombre del archivo de salida
Algortmo de huffman para decodificar bits*/

void decode_bit_stream(FILE *fin, FILE *fout) {
    int i = 0, bit, node_index = nodes[num_nodes].index;
    while (1) {
        bit = read_bit(fin);
        if (bit == -1)
            break;
        node_index = nodes[node_index * 2 - bit].index;
        if (node_index < 0) {
            char c = -node_index - 1;
            fwrite(&c, 1, 1, fout);
            if (++i == tam_orginal)
                break;
            node_index = nodes[num_nodes].index;
        }
    }
}

/*Funcion write_bit
Recibe: puntero a descriptor de archivo, un bit
Devuelve: 0 si tuvo exto -1 si no fue asi
Escribe bit a bit en el archivo de salida*/
int write_bit(FILE *f, int bit) {
    if (bits_in_buffer == TAM_MAX << 3) {
        size_t bytes_written =
            fwrite(buffer, 1, TAM_MAX, f);
        if (bytes_written < TAM_MAX && ferror(f))
            return INVALID_BIT_WRITE;
        bits_in_buffer = 0;
        memset(buffer, 0, TAM_MAX);
    }
    if (bit)
        buffer[bits_in_buffer >> 3] |=
            (0x1 << (7 - bits_in_buffer % 8));
    ++bits_in_buffer;
    return 0;
}
/*Funcion: flush_buffer
Recibe: Puntero a descriptor de archivo
Devuelve: 0 si tuvo exito
Limpia el buffer de escritura en archivos*/
int flush_buffer(FILE *f) {
    if (bits_in_buffer) {
        size_t bytes_written =
            fwrite(buffer, 1,
                (bits_in_buffer + 7) >> 3, f);
        if (bytes_written < TAM_MAX && ferror(f))
            return -1;
        bits_in_buffer = 0;
    }
    return 0;
}
/*Funcion read_bit
Recibe: puntero a descriptor de archivo
Devuelve: el bit leido si tuvo exto -1 si no fue asi
lee bit a bit en el archivo de salida*/
int read_bit(FILE *f) {
    if (current_bit == bits_in_buffer) {
        if (eof_input)
            return -1;
        else {
            size_t bytes_read =
                fread(buffer, 1, TAM_MAX, f);
            if (bytes_read < TAM_MAX) {
                if (feof(f))
                    eof_input = 1;
            }
            bits_in_buffer = bytes_read << 3;
            current_bit = 0;
        }
    }

    if (bits_in_buffer == 0)
        return -2;
    int bit = (buffer[current_bit >> 3] >>
        (7 - current_bit % 8)) & 0x1;
    ++current_bit;
    return bit;
}
/*Funcion: write_header
Recibe: puntero al descriptor del archivo
Devuelve: 0 si tuvo exito -1 si no fue asi*/
int write_header(FILE *f) {
     int i, j, byte = 0,
         size = sizeof(unsigned int) + 1 +
              num_active * (1 + sizeof(int));
     unsigned int weight;
     char *buffer = (char *) calloc(size, 1);
     if (buffer == NULL)
         return -1;

     j = sizeof(int);
     while (j--)
         buffer[byte++] =
             (original_size >> (j << 3)) & 0xff;
     buffer[byte++] = (char) num_active;
     for (i = 1; i <= num_active; ++i) {
         weight = nodes[i].weight;
         buffer[byte++] =
             (char) (-nodes[i].index - 1);
         j = sizeof(int);
         while (j--)
             buffer[byte++] =
                 (weight >> (j << 3)) & 0xff;
     }
     fwrite(buffer, 1, size, f);
     free(buffer);
     return 0;
}
/*Funcion: read_header
Recibe: puntero al descriptor del archivo
Devuelve: 0 si tuvo exito -1 si no fue asi*/

int read_header(FILE *f) {
     int i, j, byte = 0, size;
     size_t bytes_read;
     unsigned char buff[4];

     bytes_read = fread(&buff, 1, sizeof(int), f);
     if (bytes_read < 1)
         return -1;
     byte = 0;
     original_size = buff[byte++];
     while (byte < sizeof(int))
         original_size =
             (original_size << (1 << 3)) | buff[byte++];

     bytes_read = fread(&num_active, 1, 1, f);
     if (bytes_read < 1)
         return -1;

     init_arbol();

     size = num_active * (1 + sizeof(int));
     unsigned int weight;
     char *buffer = (char *) calloc(size, 1);
     if (buffer == NULL)
         return -1;
     fread(buffer, 1, size, f);
     byte = 0;
     for (i = 1; i <= num_active; ++i) {
         nodes[i].index = -(buffer[byte++] + 1);
         j = 0;
         weight = (unsigned char) buffer[byte++];
         while (++j < sizeof(int)) {
             weight = (weight << (1 << 3)) |
                 (unsigned char) buffer[byte++];
         }
         nodes[i].weight = weight;
     }
     num_nodes = (int) num_active;
     free(buffer);
     return 0;
}
