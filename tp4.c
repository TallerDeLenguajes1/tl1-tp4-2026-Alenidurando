#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

    typedef struct Tarea{
        int TareaID;//Numérico autoincremental comenzando en 1000
        char *Descripcion; //
        int Duracion; // entre 10 – 100
    } Tarea;

    typedef struct Nodo{
        Tarea T;
        struct Nodo *Siguiente;
    } Nodo;

Nodo* ListaVacia();
Nodo* CrearNodoTarea(int id,char* pdescripcion,int duracion);
void InsertarNodo(Nodo **Start , Nodo *Nodo);
void RecorrerLista(Nodo *Start);

int main(){
    srand(time(NULL));

    Nodo* StartListaPendiente=ListaVacia();

    char *Buff,*pdescripcion;
    Buff=(char *) malloc(100*sizeof(char));

    int opcion,id=999,longNombre,duracion;
    
    do{
        printf("--Carga de Datos. \n\tOPCIONES:--");
        printf("\n 1. Ingresar nueva tarea pendiente.");
        printf("\n 2. Finalizar carga de tareas pendientes.\n Ingresaro Opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);
       
        if(opcion==1){
                    
                    id++; //id autoincremental. 
                    getchar(); //para scar el \n del scanf de opcion.  
                    printf("\nIngresar descripcion de la tarea pendiente: ");
                    
                    gets(Buff); //con scanf no puedo usar espacios...
                    //scanf("%s",Buff);
                    longNombre=strlen(Buff);
                    pdescripcion= (char *) malloc((longNombre+1)*sizeof(char));
                    strcpy(pdescripcion,Buff); //reserva dinamica para la cadena de texto de despcion.

                    duracion=rand() % 91 + 10; //rand (max 100 - min 10 + 1 luego + min)
        
                    Nodo * nuevo=CrearNodoTarea(id,pdescripcion,duracion); //recibe el nodo creado con los parametros anteriores. 
                    InsertarNodo(&StartListaPendiente ,nuevo); //funcion para agregar el nuevo nodo a la lista.
            }
        
    }while(opcion!=2);

    RecorrerLista(StartListaPendiente);

    getchar();






    return 0;
}


Nodo* ListaVacia(){
    return NULL;
}


Nodo* CrearNodoTarea(int id,char* pdescripcion,int duracion){

        Nodo* NNodo=(Nodo*)malloc(sizeof(Nodo)); //reserva para el nuevo nodo
        NNodo->T.TareaID=id; //id de la tarea pendiente.
        NNodo->T.Descripcion=pdescripcion;//string descripcion
        NNodo->T.Duracion=duracion; //duracion de la tarea.
        NNodo->Siguiente=NULL;

return NNodo;
}

void InsertarNodo(Nodo **Start , Nodo *Nodo)
{
    Nodo -> Siguiente = *Start;
    *Start = Nodo ;
}

void RecorrerLista(Nodo *Start){
    Nodo *aux=Start;
    while(aux!=NULL){
        printf("\nid del nodo: %d",aux->T.TareaID);
        printf("\ndescripcion:");
        puts(aux->T.Descripcion);
        printf("duracion: %d",aux->T.Duracion);
        aux=aux->Siguiente;
    }
}