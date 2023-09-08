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

#define FILENAME "resources.txt"


typedef struct {
    int id;
    char *name;
    char *category;
    char *description;
    char *link;
} resource;

void addResource(resource *input, FILE *output);
void searchResource(char *name, FILE *f);
int saveAndExitProgram(FILE *f);
char* sAlloc(char *scannedString);
void printResource(FILE *stream, int idLine);

int main(int argc, char *argv[]) {
    int id = 0;
    int optionMenu = 0;
    int idLine = 5;
    FILE *database;

    database = fopen(FILENAME, "r+");
    fscanf(database, "%d", &id);

    while (optionMenu != 3) {
        
        printf("%d", id);
        printf("\n---- MENU ----\n");
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
            printf("Introduce una peque%ca descripcion del recurso (Maximo 200 caracteres):\n", (char)164);
            newResource->description = sAlloc(newResource->description);
            printf("Introduce el enlace al recurso:\n");
            newResource->link = sAlloc(newResource->link);

            addResource(newResource, database);

            fseek(database, 0, SEEK_SET);
            fprintf(database, "%d", (newResource->id + 1));

        }
            
        else if (optionMenu == 2) {
            char *resourceName;
            searchResource(resourceName, database);
            printResource(database, idLine);
        } 
    } 
    saveAndExitProgram(database);

    return 0;
}

void addResource(resource *input, FILE *output) {
    output = fopen(FILENAME, "a");
    //todo error al abrir el fichero
    fprintf(output, "\n");
    fprintf(output, "Id: %d\n", input->id);
    fprintf(output, "Nombre: %s", input->name);
    fprintf(output, "Categoria: %s", input->category);
    fprintf(output, "Descripcion: %s", input->description);
    fprintf(output, "Enlace: %s", input->link);


    fclose(output);

    printf("\nNuevo recurso anyadido correctamente.\n");
}

void searchResource(char *name, FILE *f) {

}

int saveAndExitProgram(FILE *stream) {
    fclose(stream);
    printf("Base de datos guardada correctamente.\n");

    return 0;
}

char* sAlloc(char *scannedString) {
    char temp[202];
    fgets(temp, 202, stdin);
    scannedString = strdup(temp);

    return scannedString;
}

void printResource(FILE *stream, int idLine) {
    char c;

    stream = fopen("resources.txt", "r");
    fseek(stream, idLine + 1, SEEK_SET);
    printf("%ld", ftell(stream));

    for (int i = 0; i < 4; i++) {
        c = fgetc(stream);
        while (c != '\n') {
            printf("%c", c);
            c = fgetc(stream);
        }
        printf("\n");
    }
    
   
   /* printf("Categoria: %s\n", fgets(idLine + 2, maxLenght, stream));
    printf("Descripcion: %s\n", fgets(idLine + 3, maxLenght, stream));
    printf("Enlace: %s\n", fgets(idLine + 4, maxLenght, stream));*/
}