/*
Mini base de datos
1 - Definir la estructura que queremos almacenar (Nombre, categoria, descripcion, enlace (por ejemplo))
2 - Trabajar con ficheros para que no se pierda la información
    Cargamos la información (Métodos de búsqueda y ordenación)
    Guardamos la información
3 - Creación de un menú de trabajo
    Insertar nueva referencia
    Buscar una referencia
    Guardar, actualizar fichero y salir del programa
    

Consejos:
Guardado de información(Podemos utilizar un buffer lineal o un arbol)
Guardar todas las estructuras en un fichero de texto
    (Podemos inventarnos una extensión, no tiene por qué ser txt)
    Leer referencias almacenadas y actualizarlas antes de salir del programa
Métodos de búsqueda y ordenación utilizados durante el curso para la carga de estructura de referencias


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char *name;
    char *category;
    char *description;
    char *link;
} resource;

void addResource(resource *input, FILE *output);
void searchResource(char *name, FILE *f);
void saveAndExitProgram(FILE *f);
char* sAlloc(char *scannedString);

int main(int argc, char *argv[]) {
    int id = 0;
    int optionMenu = 0;
    FILE *database;


    printf("---- MENU ----\n");
    printf("¿Que quieres hacer?\n");
    printf("1. A%cadir un recurso a la base de datos.\n", (char)164);
    printf("2. Buscar un recurso.\n");
    printf("3. Guardar el programa y salir.\n");
    scanf("%d", &optionMenu);

    while (optionMenu < 0 || optionMenu > 3)
    {
        printf("Lo siento. No es una opci%cn v%clida, vuelve a intentarlo:\n", (char) 162, (char)160);
        scanf("%d", &optionMenu);
    }
    
    if (optionMenu == 1) {
        resource *newResource;
        newResource = (resource *) malloc(sizeof(resource));

        newResource->id = id++;

        printf("Introduce el nombre del nuevo recurso:\n");
        getchar();
        newResource->name = sAlloc(newResource->name);

        printf("Introduce la categoria del recurso:\n");
        newResource->category= sAlloc(newResource->category);

        printf("Introduce una pequeña descripcion del recurso (Maximo 200 caracteres):\n");
        newResource->description = sAlloc(newResource->description);

        printf("Introduce el enlace al recurso:\n");
        newResource->link = sAlloc(newResource->link);

        addResource(newResource, database);

    }
        
    else if (optionMenu == 2) {
        char *resourceName;

        searchResource(resourceName, database);
    } 
        
    else   
        saveAndExitProgram(database);



    return 0;
}

void addResource(resource *input, FILE *output) {
    printf("%d", input->id);
    printf("%s", input->name);
    printf("%s", input->category);
    printf("%s", input->description);
    printf("%s", input->link);

    printf("Nuevo recurso anyadido correctamente.");
}

void searchResource(char *name, FILE *f) {

}

void saveAndExitProgram(FILE *f) {

}

char* sAlloc(char *scannedString) {
    char temp[202];
    fgets(temp, 202, stdin);
    scannedString = strdup(temp);

    return scannedString;
}