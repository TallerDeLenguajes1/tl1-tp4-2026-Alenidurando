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
Nodo* BuscarNodo(Nodo ** Start,int id);
Nodo* QuitarNodo(Nodo **Start, int id);
Nodo* BuscarNodoPorClave(Nodo ** Start, char* clave);

int main(){
    srand(time(NULL));

    Nodo* StartListaPendiente=ListaVacia();
    Nodo* StartListaRealizadas=ListaVacia();

    char *Buff,*pdescripcion;
    Buff=(char *) malloc(100*sizeof(char));

    int opcion,id=999,longNombre,duracion,idAux,opcion2,control;
    
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

    printf("\n ------------------Lista de Tareas Pendientes cargadas con exito----------------");
    RecorrerLista(StartListaPendiente);
    
    //parte para buscar id en la lista de pendientes. 
    do{
        printf("\n\t DESEA MARCA UNA TAREA PENDIENTE A REALIZADA\n 1.SI\n 2.NO\n\t Ingresar OPCION: ");
        scanf("%d",&control);
        if(control==1){
            printf("\n\tIngresar ID de Tarea a marcar realizada: ");
            scanf("%d",&idAux); //id auxiliar como dato para buscar el id en la lista. 
            getchar();
            fflush(stdin);
    /*Nodo * Buscardor=BuscarNodo(&StartListaPendiente,idAux); //recibe el nodo si lo encuntra y NULL si no lo encuntra.
    if(Buscardor){ //con este if filtramos si esta o no el nodo encontrado.. 
        printf("\n ID ENCONTRADO -------");
         printf("\nid del nodo: %d",Buscardor->T.TareaID);
        printf("\ndescripcion:");
        puts(Buscardor->T.Descripcion);
        printf("duracion: %d",Buscardor->T.Duracion);
    }
    */

            //esta parate la hacemos para quitar un nodo de la lista pendientes. 

            Nodo *NodoAotraLista= QuitarNodo(&StartListaPendiente,idAux); //devuelve el nodo quitado en la lista anterior.. 
    
            if(NodoAotraLista){ //si encontro el nodo se cumple la condicion
            InsertarNodo(&StartListaRealizadas,NodoAotraLista); //inserta el nodo en la nueva lista

            }else printf("Id no encontrado en la lista de pendientes."); //caso en que devuelva NULL la funcion quitar nodo. 
        }  }while(control!=2);      
    //muestro ambas listas:
    printf("\nLista tareas realizadas quedo como : \n");
    RecorrerLista(StartListaRealizadas);
    printf("\nLista tareas pendiente quedo como : \n");
    RecorrerLista(StartListaPendiente);
   
    
    printf("\n\t\t Menu busqueda: Ingrese si va a buscar por---- \n 1. por ID. \n 2. Por palabra Clave\n INGRESAR ELECCION: ");
    scanf("%d",&opcion2);
    getchar();
    fflush(stdin);
    


    switch (opcion2)
    {
    case 1: {
                    printf("\nIngresar ID a buscar: ");
                    scanf("%d",&idAux);
                    
                    Nodo * Buscardor=BuscarNodo(&StartListaPendiente,idAux); //recibe el nodo si lo encuntra y NULL si no lo encuntra.
                    if(Buscardor){ //con este if filtramos si esta o no el nodo encontrado.. 
                        printf("\n ID ENCONTRADO EN LISTA DE PENDIENTES");
                        printf("\nid del nodo: %d",Buscardor->T.TareaID);
                        printf("\ndescripcion:");
                        puts(Buscardor->T.Descripcion);
                        printf("duracion: %d",Buscardor->T.Duracion);
                    }else{
                            Nodo * Buscardor=BuscarNodo(&StartListaRealizadas,idAux);
                                if(Buscardor){
                                    printf("\n ID ENCONTRADO EN LISTA DE REALIZADOS");
                                    printf("\nid del nodo: %d",Buscardor->T.TareaID);
                                    printf("\ndescripcion:");
                                    puts(Buscardor->T.Descripcion);
                                    printf("duracion: %d",Buscardor->T.Duracion);
                                    } else printf("NO SE ENCONTRO EL ID EN NINGUNA LISTA.");
                    }
    }
        
        break;
        
     case 2:
                {
                    printf("\nIngresar palabra clave a buscar en la descripcion de la tarde : ");
                    gets(Buff);
                    longNombre=strlen(Buff);
                    pdescripcion= (char *) malloc((longNombre+1)*sizeof(char));
                    strcpy(pdescripcion,Buff);
                    
                    Nodo *Buscador=BuscarNodoPorClave(&StartListaPendiente,pdescripcion);
                    if(Buscador){
                        printf("\n ID ENCONTRADO EN LISTA DE PENDIENTES");
                        printf("\nid del nodo: %d",Buscador->T.TareaID);
                        printf("\ndescripcion:");
                        puts(Buscador->T.Descripcion);
                        printf("duracion: %d",Buscador->T.Duracion);

                    }else {
                         Nodo *Buscador=BuscarNodoPorClave(&StartListaPendiente,pdescripcion);
                            if(Buscador){
                            printf("\n ID ENCONTRADO EN LISTA DE REALIZADAS");
                            printf("\nid del nodo: %d",Buscador->T.TareaID);
                            printf("\ndescripcion:");
                            puts(Buscador->T.Descripcion);
                            printf("duracion: %d",Buscador->T.Duracion);}
                            else printf("NO SE ENCONTRO LA PALABRA CLAVE EN NINGUNA LISTA.");
                    }
                }
        break;    
    
    default: printf("No ingreso ninguna opcion valida");
        break;
    }


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

Nodo* BuscarNodo(Nodo ** Start,int id)
{
  Nodo* Aux = *Start;
  while (Aux && Aux->T.TareaID != id)
  {
    Aux = Aux->Siguiente;
  }
  return Aux;
}


Nodo * QuitarNodo(Nodo **Start, int id) {
    Nodo ** aux = Start;  // Usamos un puntero doble para apuntar al puntero actual  de la lista enlazada. 
    
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.
    while (*aux != NULL && (*aux)->T.TareaID != id) {
        aux = &(*aux)->Siguiente;
    }

    // Si encontramos el nodo con el dato especificado, lo quitamos de la lista y retornamos al programa para su posterior eliminación.
    if (*aux) {
        Nodo *temporal = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
        temporal->Siguiente =NULL; // Ponemos en NULL el puntero siguiente para asegura no llevar vinculos por fuera de la lista
        return temporal;
    }
    return NULL;
}

Nodo* BuscarNodoPorClave(Nodo ** Start, char* clave)
{
  Nodo* Aux = *Start;
  
  while (Aux && strstr(Aux->T.Descripcion,clave)==NULL )
  {
    Aux = Aux->Siguiente;
  }
  return Aux;
}