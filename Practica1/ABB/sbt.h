
typedef struct Nodo{
  long int valor;
  struct Nodo *izq,*der;
}Nodo;


typedef Nodo Arbol;

Nodo *crearNodo(long int n);
void destruitNodo(Nodo *nodo);
void insertar(Nodo **arbol, long int valor);
void inOrden(Nodo *arbol, long A[]);
