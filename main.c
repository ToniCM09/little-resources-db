/*
Programa que simula una pequeña base de datos en la que podemos almacenar recursos con la siguiente estructura:
    - Nombre
    - Categoría
    - Descricpción
    - Enlace

Los datos se almacenan en un fichero que podemos consultar para buscar un recurso concreto y que nos lo muestre por pantalla.

El programa se gestiona desde un menú con las opciones de añadir un recurso, buscarlo o guardar el fichero y salir del programa.
*/

#include "libdb.h"

int main(int argc, char *argv[]) {
    // Definición de variables
    int optionMenu = 0;
    FILE *database;
    
    while (optionMenu != 3) { //Bucle para mantener el programa en ejecución hasta que se indique su cierre
        
        printf("\n---- MENU ----\n");
        printf("¿Que quieres hacer?\n");
        printf("1. A%cadir un recurso a la base de datos.\n", (char)164);
        printf("2. Buscar un recurso.\n");
        printf("3. Guardar el programa y salir.\n");
        scanf("%d", &optionMenu);

        while (optionMenu < 0 || optionMenu > 3) // Comprobación de datos de entrada
        {
            printf("Lo siento. No es una opci%cn v%clida, vuelve a intentarlo:\n", (char) 162, (char)160);
            scanf("%d", &optionMenu);
        }
        
        if (optionMenu == 1) {
            // Declaración de estructura y asignación de memoria
            resource *newResource;
            newResource = (resource *) malloc(sizeof(resource)); 
            printf("Introduce el nombre del nuevo recurso:\n");
            getchar();
            newResource->name = sAlloc(newResource->name);
            printf("Introduce la categoria del recurso:\n");
            newResource->category= sAlloc(newResource->category);
            printf("Introduce una peque%ca descripcion del recurso (Maximo 200 caracteres):\n", (char)164);
            newResource->description = sAlloc(newResource->description);
            printf("Introduce el enlace al recurso:\n");
            newResource->link = sAlloc(newResource->link);
            
            addResource(newResource, database); //Añadir el recurso al fichero
            freeMemory(newResource); // Liberar la memoria
        }
            
        else if (optionMenu == 2) {
            database = fopen(FILENAME, "r");
            checkFileErrors(database); // Comprobación de errores
            int idLine = listResources(database); // Lista los recursos almacenados y devuelve el recurso seleccionado
            printResource(database, idLine); // Imprime por pantalla el recurso seleccionado
            fclose(database);
        } 
    } 
    saveAndExitProgram(database); //Salir del programa

    return 0;
}