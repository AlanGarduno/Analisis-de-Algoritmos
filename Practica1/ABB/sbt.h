/*Cabecera de la estructura de datos arbol binario*/

/*TAD Nodo que contiene un valor de tipo long int
y dos punteros iz y der, que definen la estructura de
manera recursiva 
*/
typedef struct Nodo{
  long int valor;
  struct Nodo *izq,*der;
}Nodo;


typedef Nodo Arbol;
/*Prototipo de funciion de crearNodo que retorna un puntero de tipo Nodo, recibe un long n*/
Nodo *crearNodo(long int n);
/*Prototipo de funcion destruirNodo no retorna nada y recibe el nodo a ser destruido */
void destruirNodo(Nodo *nodo);
/*Prototipo de funcion inserar que recibe la direccion de menoria del puntero a un arbol, un long int que es el valor a insertar*/
void insertar(Nodo **arbol, long int valor);
/*Prototipo de funcion inOrden,no retorna nada y recibe un puntero a arbol y un long A que es un puntero a un arrgelo tipo long*/
void inOrden(Nodo *arbol, long A[]);
