#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicion
#define true  1
#define false 0

#define AGREGAR 1
#define VER 2
#define DESCARTAR 3
#define LIMPIAR 4
#define SALIR 5

//tipos de datos
typedef struct STarea
{
  int numero;
  char titulo[100];
} Tarea;

typedef struct SCola
{ 
  int actual;  
  int cima;
  
  Tarea *tareas;
  
} Pila;


//firmas

void crear(Pila* pila, int size);
void liberar(Pila *pila);

int estaVacia(Pila *pila);
int estaLlena(Pila *pila);
int limpiar(Pila *pila);

void insertar(Pila *pila, int numero, char *titulo); //push
Tarea* tomar(Pila *pila);//pull
Tarea* ver(Pila *pila);//peek 

//funciones de menu:
int preguntarCantidadDeTareas();
int preguntarAccion();
void mostrarMensajeDeOpctionInvalida();
void obtenerTareaDesdeUsuario(Pila *pila);
void mostrarActual(Pila *pila);
void mostrarYDescargar(Pila *pila);
void limpiarPila(Pila *pila);

//codigo
int main(int argc, char *argv[])
{
  Pila pila;
  int size;
  int opcion;
  Tarea *tarea;
  
  size = preguntarCantidadDeTareas();
  
  // pedir tamaño por consola
  crear(&pila, size);
  
  while( (opcion = preguntarAccion()) != SALIR ){
         switch(opcion) {
             case AGREGAR:
                 obtenerTareaDesdeUsuario(&pila);
                 break; 
             case VER:
                 mostrarActual(&pila);
                 break; 
             case DESCARTAR:
                 mostrarYDescargar(&pila);
                 break; 
             case LIMPIAR:
                 limpiarPila(&pila);
                 break;                  
             default : /* Optional */
               mostrarMensajeDeOpctionInvalida();             
         };
  }
  
  
  liberar(&pila);
  
  system("PAUSE");	
   
  return 0;
}

//funciones
//////////
// menus
int preguntarCantidadDeTareas() {
    int size;
    
    printf( "Cuntas tareas (cima)?\n-");
    scanf("%d", &size);
    
    return size;
}
int preguntarAccion() {
    int accion;
     
    printf( "\n\nSeleccione un accion?\n");
    printf( "- %d AGREGAR\n", AGREGAR);
    printf( "- %d VER\n", VER);
    printf( "- %d DESCARTAR\n", DESCARTAR);
    printf( "- %d LIMPIAR\n\n", LIMPIAR); 
    printf( "- %d SALIR\n", SALIR); 
    
    scanf("%d", &accion);
    
    return accion;
}
void mostrarMensajeDeOpctionInvalida(){
    printf( "Opcion Invalida\n");
}
 
void obtenerTareaDesdeUsuario(Pila *pila){
     
  int numero;
  char titulo[100];
  
   if(pilaLlena(pila) == false) {
      
    printf( "\n\nIngrese tarea\n nr texto\n");
    scanf("%d %s", &numero, titulo);
    
    insertar(pila, numero, titulo);
      
  } else {
    printf( "\n\nYa no se pueden cargar mas tareas\n");
  }
  
}

void mostrarActual(Pila *pila) {
     
  Tarea *tarea;
  //test:
  if(pilaVacia(pila) == false) {
    printf( "\n\nTarea Actual:\n");
    tarea = ver(pila); //no la saca
    printf( "- %d %s\n", tarea->numero, tarea->titulo);
    
  } else {
    printf( "\n\nSin tareas\n");
  }
  
}

void mostrarYDescargar(Pila *pila){
     
  Tarea *tarea;
  //test:
  if(pilaVacia(pila) == false) {  
                     
    printf( "\n\nDescartando:\n");
    mostrarActual(pila);
    tarea = tomar(pila); //l saca
  } else {
      printf( "\n\nSin tareas\n");
  }
}

//////////
// functiones de pila
void crear(Pila* pila, int size){
     pila->actual = 0;
     pila->cima = size;
     
     pila->tareas = malloc(sizeof(Pila) * size);
}

void limpiarPila(Pila *pila) {
    pila->actual = 0;
}

void liberar(Pila *pila) {
     free( pila->tareas );
}

void insertar(Pila *pila, int numero, char *titulo) {
     
     pila->actual++;
     
     //por q es 0-based
     Tarea* tarea = &pila->tareas[pila->actual-1];
     
     tarea->numero = numero;
     
     strcpy( tarea->titulo, titulo);
     
}

Tarea* tomar(Pila *pila){
       //ver si esta bien esto
       Tarea *tarea = &pila->tareas[pila->actual-1];
       
       pila->actual--;
       
       return tarea;
}

Tarea* ver(Pila *pila) {
        return &pila->tareas[pila->actual-1];
}

int pilaVacia(Pila *pila) {
    if(pila->actual > 0) {
       return false;
     } 
     
     return true;
}
int pilaLlena(Pila *pila) {
    if(pila->actual >= pila->cima) {
       return true;
     } 
     
     return false;
}
