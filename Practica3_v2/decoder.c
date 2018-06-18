#include "decoder.h"


int decodificar_archivo(char * nombre_archivo){
    if(nombre_archivo == NULL){return -1;}

    FILE * tabla_codificacion = fopen("tabla_codificacion.txt", "r");
    struct arbol_decodificador * arbol = NULL;
    char * nombre_original = (char *)malloc(TAM_BUFFER_ARBOL*sizeof(char));

    iniciar_arbol(&arbol);
    struct info_archivo * info = construir_arbol(tabla_codificacion, &arbol);

    strcat(nombre_original, info -> nombre);
    strcat(nombre_original, "-decodificado");
    strcat(nombre_original, ".");
    strcat(nombre_original, info -> extension);


    construir_archivo(arbol, nombre_archivo, nombre_original);

    return 0;
}

int construir_archivo(struct arbol_decodificador * arbol, char * nombre_archivo, char * nombre_archivo_original){
    if(arbol == NULL){return -1;}
    if(nombre_archivo == NULL){return -1;}

    unsigned char * buffer = (unsigned char *)malloc(TAM_BUFFER * sizeof(unsigned char));
    unsigned int valor = 0;
    unsigned char valor_escritura;
    int i = TAM_BUFFER * 8;
    int continuar = 1;

    int f_archivo = open(nombre_archivo, O_RDONLY);
    int f_nuevo = open(nombre_archivo_original, O_WRONLY | O_CREAT, 0644);

    while(continuar){
        valor = obtener_valor(f_archivo, buffer, &i, arbol);
        //printf("VALOR: %d\n", valor);
        if(valor != 256){
            valor_escritura = valor;
            write(f_nuevo, &valor_escritura, sizeof(char));
        }
        else{
            continuar = 0;
            close(f_archivo);
        }
    }

    return 0;
}

unsigned int obtener_valor(int f_archivo, unsigned char * buffer, int * contador, struct arbol_decodificador * arbol){
    if(arbol == NULL){
        printf("%s\n", "MMTA");
    }
    if((*contador) == TAM_BUFFER * 8){
        read(f_archivo, buffer, TAM_BUFFER);
        *contador = 0;
    }

    if(arbol -> hijo_izq == NULL && arbol -> hijo_der == NULL){
        return arbol -> valor_real;
    }

    int bit = obtener_bit(buffer, *contador);
    //printf("BIT: %d\n", bit);
    if(bit){
        *contador += 1;
        return obtener_valor(f_archivo, buffer, contador, arbol -> hijo_izq);
    }
    else{
        *contador += 1;
        return obtener_valor(f_archivo, buffer, contador, arbol -> hijo_der);
    }
}

int obtener_bit(unsigned char * buffer, int contador){
    //printf("Contador: %d\n", contador);
    int pos = contador / 8;
    int pos_bit = contador % 8;
    char aux = buffer[pos] >> (7 - pos_bit);

    return !(aux & 0x1);
}

/**
    Construimos nuevamente el arbol que en las hojas contiene los verdaderos
    valores del archivo a descomprimir, todo con base en el archivo tabla_codificacion.txt que contiene
*/
struct info_archivo * construir_arbol(FILE * tabla, struct arbol_decodificador ** arbol){
    if((*arbol) == NULL){
        printf("%s\n", "EL ARBOL FUE NULO.");
        exit(3);
    }

    char buffer[TAM_BUFFER_ARBOL];
    char buffer_valor[5];
    char buffer_camino[2990];
    struct info_archivo * info = (struct info_archivo *)malloc(sizeof(struct info_archivo));
    int i = 0, j = 0;
    unsigned int valor = 0;

    if(fgets(buffer, TAM_BUFFER_ARBOL, tabla) != NULL){
        llenar_info_archivo(info, buffer);
    }
    else{
        printf("%s\n", "No puedo leer la tabla");
        exit(3);
    }

    while(fgets(buffer, TAM_BUFFER_ARBOL, tabla) != NULL){
        i = 0;
        j = 0;
        while(buffer[i] != ' '){
            buffer_valor[j++] = buffer[i];
            i++;
        }
        i++;
        buffer_valor[j] = '\0';
        valor = atoi(buffer_valor);
        j = 0;
        while(buffer[i] != '\n' && buffer[i] != '\0'){
            buffer_camino[j++] = buffer[i];
            i++;
        }
        buffer_camino[j] = '\0';
        //printf("%d, %s\n", valor, buffer_camino);
        insertar_nodo_arbol(arbol, valor, buffer_camino, 0);
    }

    return info;
}

int iniciar_arbol(struct arbol_decodificador ** arbol){
    if((*arbol) == NULL){
        (*arbol) = (struct arbol_decodificador *)malloc(sizeof(struct arbol_decodificador));
        if((*arbol) == NULL){printf("%s\n", "Memoria insuficiente");exit(1);}
        (*arbol) -> hijo_izq = NULL;
        (*arbol) -> hijo_der = NULL;
    }
    return 0;
}


int llenar_info_archivo(struct info_archivo * info, char * cadena){
        if(info == NULL){return -1;}
        //printf("CADENA: %s\n", cadena);
        info -> nombre = (char *)malloc(TAM_BUFFER_ARBOL * sizeof(char));
        info -> extension = (char *)malloc(10 * sizeof(char));
        info -> tam = 0;

        int i = 0, j = 0, k = 0;
        while(1){
            if(cadena[i] == '.')
                break;
            info -> nombre[k++] = cadena[i];
            i++;
        }
        i++;

        while(1){
            if(cadena[i] == ' ')
                break;
            info -> extension[j++] = cadena[i];
            i++;
        }
        i++;

        info -> tam = atoi(cadena + i);
        //printf("nombre: %s, extension: %s, tam: %ld\n", info -> nombre, info -> extension, info -> tam);

        return 0;
}


int insertar_nodo_arbol(struct arbol_decodificador ** arbol, int valor, char * camino, int contador_camino){
    if((*arbol) == NULL){printf("%s\n", "Árbol nulo"); return -1;}
    //printf("%c\n", camino[contador_camino]);
    if(camino[contador_camino] == '0'){
        if((*arbol) -> hijo_izq == NULL){
            (*arbol) -> hijo_izq = (struct arbol_decodificador *)malloc(sizeof(struct arbol_decodificador));
            (*arbol) -> hijo_izq -> hijo_izq = NULL;
            (*arbol) -> hijo_izq -> hijo_der = NULL;
        }
        return insertar_nodo_arbol(&((*arbol) -> hijo_izq), valor, camino, ++contador_camino);
    }
    else if(camino[contador_camino] == '1'){
        if((*arbol) -> hijo_der == NULL){
            (*arbol) -> hijo_der = (struct arbol_decodificador *)malloc(sizeof(struct arbol_decodificador));
            (*arbol) -> hijo_der -> hijo_izq = NULL;
            (*arbol) -> hijo_der -> hijo_der = NULL;
        }
        return insertar_nodo_arbol(&((*arbol) -> hijo_der), valor, camino, ++contador_camino);
    }
    else{
        (*arbol) -> valor_real = valor;
    }

    return 0;
}
