#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicion
#define true  1
#define false 0

#define AGREGAR 1
#define VER 2
#define DESCARTAR 3
#define SALIR 4

//tipos de datos
typedef struct STarea
{
  int numero;
  char titulo[100];
} Tarea;

typedef struct SCola
{ 
  int actual;  
  int max;
  
  Tarea *tareas;
  
} Cola;


//firmas

void crear(Cola* cola, int size);
void liberar(Cola *cola);

int estaVacia(Cola *cola);
int estaLlena(Cola *cola);

void agregar(Cola *cola, int numero, char *titulo); //push
Tarea* tomar(Cola *cola);//pull
Tarea* ver(Cola *cola);//peek

//funciones de menu:
int preguntarCantidadDeTareas();
int preguntarAccion();
void mostrarMensajeDeOpctionInvalida();
void obtenerTareaDesdeUsuario(Cola *cola);
void mostrarActual(Cola *cola);
void mostrarYDescargar(Cola *cola);

//codigo
int main(int argc, char *argv[])
{
  Cola cola;
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
    
    printf( "Cuntas tareas (max)?\n-");
    scanf("%d", &size);
    
    return size;
}
int preguntarAccion() {
    int accion;
     
    printf( "Seleccione un accion?\n");
    printf( "- %d AGREGAR\n", AGREGAR);
    printf( "- %d VER\n", VER);
    printf( "- %d DESCARTAR\n", DESCARTAR);
    printf( "- %d SALIR\n", SALIR); 
    
    scanf("%d", &accion);
    
    return accion;
}
void mostrarMensajeDeOpctionInvalida(){
    printf( "Opcion Invalida\n");
}
 
void obtenerTareaDesdeUsuario(Cola *cola){
     
  int numero;
  char titulo[100];
  
   if(estaLlena(cola) == false) {
      
    printf( "Ingrese tarea\n nr texto\n");
    scanf("%d %s", &numero, titulo);
    
    agregar(cola, numero, titulo);
      
  } else {
    printf( "Ya no se pueden cargar mas tareas\n");
  }
  
}

void mostrarActual(Cola *cola) {
     
  Tarea *tarea;
  //test:
  if(estaVacia(cola) == false) {
    tarea = ver(cola); //no la saca
    printf( "- %d %s\n", tarea->numero, tarea->titulo);
    
  } else {
    printf( "Sin tareas\n");
  }
  
}

void mostrarYDescargar(Cola *cola){
     
  Tarea *tarea;
  //test:
  if(estaVacia(cola) == false) {  
                     
    printf( "Descartando:\n");
    mostrarActual(cola);
    tarea = tomar(cola); //l saca
  } else {
      printf( "Sin tareas\n");
  }
}

//////////
// functiones de cola
void crear(Cola* cola, int size){
     cola->actual = 0;
     cola->max = size;
     
     cola->tareas = malloc(sizeof(Cola) * size);
}

void liberar(Cola *cola) {
     free( cola->tareas );
}

void agregar(Cola *cola, int numero, char *titulo) {
     
     cola->actual++;
     
     //por q es 0-based
     Tarea* tarea = &cola->tareas[cola->actual-1];
     
     tarea->numero = numero;
     
     strcpy( tarea->titulo, titulo);
     
}

Tarea* tomar(Cola *cola){
       //ver si esta bien esto
       Tarea *tarea = &cola->tareas[cola->actual-1];
       
       cola->actual--;
       
       return tarea;
}

Tarea* ver(Cola *cola) {
        return &cola->tareas[cola->actual-1];
}

int estaVacia(Cola *cola) {
    if(cola->actual > 0) {
       return false;
     } 
     
     return true;
}
int estaLlena(Cola *cola) {
    if(cola->actual >= cola->max) {
       return true;
     } 
     
     return false;
}
