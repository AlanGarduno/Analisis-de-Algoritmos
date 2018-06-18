/*
ESCOM-IPN
Practica 3: Codificacion voraz de huffman
Analisis de Algoritmos
Alan Garduño Velazquez
Luis Ricardo Tellez Giron Garcia
3CM3
18-06-18
*/
#define TAM_MAX 256 //tamaño maximo de los buffer
#define INVALID_BIT_WRITE  -1
#define INVALID_BIT_READ -1 //Valor para los bit invalidos

#define FALLO 1
#define EXITO 0
#define ERROR_APERTURA_ARCHIVO -1
#define FIN_ARCHIVO -1
#define NO_MEMORY -1

typedef struct Nodo{
    int index;
    unsigned int weight;
}Nodo;

void determinar_frecuencia(FILE *f);
void init();
void init_arbol();
void destruir();
int add_nodo(int index, int weight);
void add_hoja();
void build_tree();
int encode(const char* ifile, const char *ofile);
void encode_alphabet(FILE *fout, int c);
int decode(const char* ifile, const char *ofile);
void decode_bit_stream(FILE *fin, FILE *fout);
int write_bit(FILE *f, int bit);
int flush_buffer(FILE *f);
int read_bit(FILE *f);
int write_header(FILE *f);
int read_header(FILE *f)
