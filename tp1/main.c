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

int estaVacia(Cola *cola);

void crear(Cola* cola, int size);
void liberar(Cola *cola);

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
    return 10;//tomar del usuario
}
int preguntarAccion() {
    //poner menu
    return SALIR;
}
void mostrarMensajeDeOpctionInvalida(){
     //hacer
}
 
void obtenerTareaDesdeUsuario(Cola *cola){
  //tomr datos de menu
  agregar(cola, 123, "test");
  
}

void mostrarActual(Cola *cola) {
     
  Tarea *tarea;
  //test:
  if(estaVacia(cola) == false) {
    tarea = ver(cola); //no9 l saca
  
  } else {
         //mostrar error
  }
  
}

void mostrarYDescargar(Cola *cola){
     
  Tarea *tarea;
  //test:
  if(estaVacia(cola) == false) {  
    tarea = tomar(cola); //l saca
  } else {
         //mostrar error
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
     
     if(cola->actual >= cola->max) {
       return;
     } 
     
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
