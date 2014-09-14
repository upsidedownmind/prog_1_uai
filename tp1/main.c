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

void crear(Pila* cola, int size);
void liberar(Pila *cola);

int estaVacia(Pila *cola);
int estaLlena(Pila *cola);
int limpiar(Pila *cola);

void insertar(Pila *cola, int numero, char *titulo); //push
Tarea* tomar(Pila *cola);//pull
Tarea* ver(Pila *cola);//peek 

//funciones de menu:
int preguntarCantidadDeTareas();
int preguntarAccion();
void mostrarMensajeDeOpctionInvalida();
void obtenerTareaDesdeUsuario(Pila *cola);
void mostrarActual(Pila *cola);
void mostrarYDescargar(Pila *cola);
void limpiarPila(Pila *cola);

//codigo
int main(int argc, char *argv[])
{
  Pila cola;
  int size;
  int opcion;
  Tarea *tarea;
  
  size = preguntarCantidadDeTareas();
  
  // pedir tamaño por consola
  crear(&cola, size);
  
  while( (opcion = preguntarAccion()) != SALIR ){
         switch(opcion) {
             case AGREGAR:
                 obtenerTareaDesdeUsuario(&cola);
                 break; 
             case VER:
                 mostrarActual(&cola);
                 break; 
             case DESCARTAR:
                 mostrarYDescargar(&cola);
                 break; 
             case LIMPIAR:
                 limpiarPila(&cola);
                 break;                  
             default : /* Optional */
               mostrarMensajeDeOpctionInvalida();             
         };
  }
  
  
  liberar(&cola);
  
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
 
void obtenerTareaDesdeUsuario(Pila *cola){
     
  int numero;
  char titulo[100];
  
   if(pilaLlena(cola) == false) {
      
    printf( "\n\nIngrese tarea\n nr texto\n");
    scanf("%d %s", &numero, titulo);
    
    insertar(cola, numero, titulo);
      
  } else {
    printf( "\n\nYa no se pueden cargar mas tareas\n");
  }
  
}

void mostrarActual(Pila *cola) {
     
  Tarea *tarea;
  //test:
  if(pilaVacia(cola) == false) {
    printf( "\n\nTarea Actual:\n");
    tarea = ver(cola); //no la saca
    printf( "- %d %s\n", tarea->numero, tarea->titulo);
    
  } else {
    printf( "\n\nSin tareas\n");
  }
  
}

void mostrarYDescargar(Pila *cola){
     
  Tarea *tarea;
  //test:
  if(pilaVacia(cola) == false) {  
                     
    printf( "\n\nDescartando:\n");
    mostrarActual(cola);
    tarea = tomar(cola); //l saca
  } else {
      printf( "\n\nSin tareas\n");
  }
}

//////////
// functiones de cola
void crear(Pila* cola, int size){
     cola->actual = 0;
     cola->cima = size;
     
     cola->tareas = malloc(sizeof(Pila) * size);
}

void limpiarPila(Pila *cola) {
    cola->actual = 0;
}

void liberar(Pila *cola) {
     free( cola->tareas );
}

void insertar(Pila *cola, int numero, char *titulo) {
     
     cola->actual++;
     
     //por q es 0-based
     Tarea* tarea = &cola->tareas[cola->actual-1];
     
     tarea->numero = numero;
     
     strcpy( tarea->titulo, titulo);
     
}

Tarea* tomar(Pila *cola){
       //ver si esta bien esto
       Tarea *tarea = &cola->tareas[cola->actual-1];
       
       cola->actual--;
       
       return tarea;
}

Tarea* ver(Pila *cola) {
        return &cola->tareas[cola->actual-1];
}

int pilaVacia(Pila *cola) {
    if(cola->actual > 0) {
       return false;
     } 
     
     return true;
}
int pilaLlena(Pila *cola) {
    if(cola->actual >= cola->cima) {
       return true;
     } 
     
     return false;
}
