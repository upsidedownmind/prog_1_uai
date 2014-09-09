#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicion
#define true  1
#define false 0

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

//codigo
int main(int argc, char *argv[])
{
  Cola cola;
  int size = 10;
  Tarea *tarea;
  
  // pedir tamaño por consola
  crear(&cola, size);
  
  //tomr datos de menu
  agregar(&cola, 123, "test");
  
  //test:
  if(estaVacia(&cola) == false) {
    tarea = ver(&cola); //no9 l saca
  
    tarea = tomar(&cola); //l saca
  }
  
  liberar(&cola);
  
  system("PAUSE");	
   
  return 0;
}

//funciones
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
