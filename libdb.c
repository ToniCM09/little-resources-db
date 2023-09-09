#include "libdb.h"

void addResource(resource *input, FILE *output) {
    output = fopen(FILENAME, "a");
    checkFileErrors(output);
    fprintf(output, "\n");
    fprintf(output, "Nombre: %s", input->name);
    fprintf(output, "Categoria: %s", input->category);
    fprintf(output, "Descripcion: %s", input->description);
    fprintf(output, "Enlace: %s", input->link);

    fclose(output);

    printf("\nNuevo recurso anyadido correctamente.\n");
}

int listResources(FILE *f) {
    char stringToFind[50];
    int resourcePos[20];
    int counter = -1;
    int resourceSelected = -1;
    printf("--------\n");
    printf("Listado de recursos almacenados. Escribe el numero del recurso para ver el contenido completo:\n");
    while (fscanf(f, "%s", stringToFind) > 0) {
        if (strcmp(stringToFind, "Nombre:") == 0) {
            resourcePos[++counter] = ftell(f);
            fgets(stringToFind, 100, f);
            printf("%d -%s", counter, stringToFind);
        }
    }
    if (counter == -1)
        printf("No se han encontrado recursos\n");
    else 
        scanf("%d", &resourceSelected);
    printf("--------\n");
    return resourcePos[resourceSelected];
}

void printResource(FILE *stream, int idLine) {
    char c;
    int numRows = 4;
    int bytesUntilName = 7;

    fseek(stream, idLine - bytesUntilName, SEEK_SET);

    for (int i = 0; i < numRows; i++) {
        c = fgetc(stream);
        while (c != '\n') {
            printf("%c", c);
            c = fgetc(stream);
        }
        printf("\n");
    }
    
}

// Cerramos el fichero si estuviera abierto y finalizamos el programa.
int saveAndExitProgram(FILE *stream) {
    fclose(stream);
    printf("Base de datos guardada correctamente.\n");

    return 0;
}

void checkFileErrors(FILE *f) {
    if (f == NULL) {
        printf("Ha ocurrido un error, revisa el archivo error.log");
        freopen("error.log", "w", stderr);
        fprintf(stderr, "No se puede abrir el fichero %s", FILENAME);
        fclose(stderr);
        exit(-1);
    }
}

char* sAlloc(char *scannedString) {
    int maxLenght = 201;
    char temp[maxLenght];
    if (fgets(temp, maxLenght, stdin) == NULL) {
        printf("Error, el texto es demasiado largo.");
        return "Error";
    };
    scannedString = strdup(temp);

    return scannedString;
}

// Se libera la memoria de cada elemento de la estructura y finalmente de la estructura en sí
void freeMemory(resource *r) {
    free(r->name);
    free(r->category);
    free(r->description);
    free(r->link);
    free(r);
}

