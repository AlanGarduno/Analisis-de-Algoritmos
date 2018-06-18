#include "huffman.h"

void inicializar_variables() {
    bits_buffer = 0;
    memset(buffer_salida, 0, 256);
}

ssize_t obtener_tam_archivo(char *archivo) {
    struct stat datos_archivo;
    stat(archivo, &datos_archivo);
    return datos_archivo.st_size;
}

int comprimir_archivo(char *nombre_archivo){
    int archivo = open(nombre_archivo, O_RDONLY);
    unsigned char buffer_entrada[256];
    /*
    * Arreglo donde contaremos las frecuencias de nuestros 256
    * simbolos mas un simbolo para identificar el final de
    * archivo en el archivo comprimido
    */
    unsigned long long frecuencias[257] = {0};

    // El ultimo elemento es el de final de archivo
    frecuencias[256] = 1;

    int leidos = 0;
    ssize_t total = 0;

    //Leemos el archivo por bloques
    while ((leidos = read(archivo, buffer_entrada, 256)) > 0){
        // Contamos las frecuencias de los bytes leidos en el bloque
        for (unsigned long long i = 0; i<leidos; i++)
            frecuencias[buffer_entrada[i]]++;
        total += leidos;
    }
    close(archivo);


    // LLenamos nuestra lista
    Nodo *lista = NULL;
    for (int i = 0; i < 257; i++)
        if(frecuencias[i] != 0)
            lista = Add(lista, frecuencias[i], i);

    lista = crear_arbol(lista);
    construir_tabla(lista, nombre_archivo);
    crear_comprimido(nombre_archivo);
    return 0;
}

void construir_tabla(Nodo *lista, char *archivo) {
    char camino[2000];
    FILE *f;
    f = fopen("tabla_codificacion.txt", "w");
    memset(camino, '\0', sizeof(camino));
    llenar_tabla(lista, camino, 0, f);
    fclose(f);
}


void crear_comprimido(char *nombre_archivo) {
    int archivo = open(nombre_archivo, O_RDONLY);
    int f_comprimido = open("comprimido.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    int leidos = 0;
    unsigned char buffer[256];
    while ((leidos = read(archivo, buffer, 256)) > 0){
        for (unsigned long long i = 0; i < leidos; i++)
            for (int j = 0; j< strlen(VALORES[buffer[i]]); j++)
                escribir_bit(f_comprimido, VALORES[buffer[i]][j]-'0');
    }
    /*
    * Metemos la secuencia de bits que terminan el archivo
    * al buffer antes de escribirlo en el archivo
    */
    for (int j = 0; j< strlen(VALORES[256]); j++)
        escribir_bit(f_comprimido, VALORES[256][j]-'0');

    // Metemos los bits que no llenaron un buffer
    if (bits_buffer < 256 << 3)
        write(f_comprimido, buffer_salida, (bits_buffer / 8)+1);

    close(f_comprimido);
    close(archivo);
}


void llenar_tabla(Nodo *arbol, char *camino, int longitud, FILE *f) {
    if(arbol->izq== NULL && arbol->der == NULL) {
        return;
    }
    char camino_izq[2000];
    char camino_der[2000];
    memset(camino_izq, '\0', sizeof(camino_izq));
    memset(camino_der, '\0', sizeof(camino_der));
    strcpy(camino_izq, camino);
    strcpy(camino_der, camino);
    camino_izq[longitud] = '0';
    camino_der[longitud++] = '1';

    llenar_tabla(arbol->izq, camino_izq, longitud, f);
    if (arbol->izq->izq == NULL && arbol->izq->der == NULL)
        agregar_simbolo_tabla(arbol->izq->numero, camino_izq, longitud, f);

    llenar_tabla(arbol->der, camino_der, longitud, f);
    if (arbol->der->izq == NULL && arbol->der->der == NULL)
        agregar_simbolo_tabla(arbol->der->numero, camino_der, longitud, f);
}

void agregar_simbolo_tabla(int numero, char *secuencia, int longitud, FILE *f) {
    char *string = malloc(sizeof(char) * longitud);
    strcpy(string, secuencia);
    VALORES[numero] = string;
    fprintf(f, "%d %s\n", numero, secuencia);
}

Nodo *Add(Nodo *inicio, unsigned long long frecuencia, int numero) {
    Nodo *temp = (struct Nodo*)malloc(sizeof(struct Nodo));
    temp->numero = numero;
    temp->frecuencia = frecuencia;

    if (inicio == NULL){
        temp->siguiente = NULL;
        return temp;
    }
    if (frecuencia < inicio->frecuencia) {
        temp->siguiente = inicio;
        return temp;
    }

     Nodo *prev = inicio;
     Nodo *aux = inicio->siguiente;
    while(aux != NULL && (aux->frecuencia < frecuencia)) {
        prev = aux;
        aux = aux->siguiente;
    }

    temp->siguiente = aux;
    prev->siguiente = temp;
    return inicio;
}

void escribir_bit(int f, int bit) {
    /*Si recibimos un uno lo ponemos y aumentamos nuestro
    * contador de bits, de lo contrario solo se aumenta
    * el numero de bits
    */
    if (bit){
        /*
        * Corrimiento hacia la derecha para ubicarnos en el byte
        * correcto, compuerta or para que se pueda agregar el bit sin
        * modificar los bits que ya estaban
        */
        buffer_salida[bits_buffer >> 3] |= (0x1 << (7 - bits_buffer % 8));
    }
    bits_buffer++;
    /*
    * Si ya llenamos el buffer lo escribimos, corrimiento a la izq
    * para comparar bits y no bytes, limpiamos el buffer y
    * reiniciamos el contador de bits
    */
    if (bits_buffer == 256 << 3) {
        write(f, buffer_salida, 256);
        inicializar_variables();
    }
}

Nodo *crear_arbol(Nodo *lista) {
    // Nodos mas pequeños dentro de la lista
     Nodo *auxiliar2;
     Nodo *auxiliar;

    // Nodo auxiliar para iterar la lista
    Nodo *indice = lista;
    int tomar = 1;

    // Nodo auxiliar para crear nodos internos
    struct Nodo *nuevo;

    // Clave para identificar un nodo interno
    int clave = -1;

    while (indice != NULL) {
        if (tomar) {
            auxiliar = lista;
            auxiliar2 = lista->siguiente;
            nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
            nuevo->frecuencia = auxiliar->frecuencia + auxiliar2->frecuencia;
            nuevo->numero = clave--;
            nuevo->izq = auxiliar;
            nuevo->der = auxiliar2;
            nuevo->siguiente = NULL;
            if (auxiliar2->siguiente == NULL) {
                lista = nuevo;
                break;
            }
            lista = auxiliar2->siguiente;
            if (nuevo->frecuencia < lista->frecuencia) {
                nuevo->siguiente = lista;
                lista = nuevo;
                tomar = 1;
            } else {
                tomar = 0;
            }
            indice = lista;
        } else {
            if (indice->siguiente == NULL) {
                indice->siguiente = nuevo;
                indice = lista;
                tomar = 1;
            }else if (nuevo->frecuencia < indice->siguiente->frecuencia) {
                nuevo->siguiente = indice->siguiente;
                indice->siguiente = nuevo;
                tomar = 1;
            } else {
                indice = indice->siguiente;
                if (indice->siguiente == NULL) {
                    indice->siguiente = nuevo;
                    indice = lista;
                    tomar = 1;
                }
            }
        }
    }
    return lista;
}
