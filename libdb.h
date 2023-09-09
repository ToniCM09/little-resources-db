// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de constantes
#define FILENAME "resources.txt"

// Estructura para el almacenamiento de recursos
typedef struct {
    char *name;
    char *category;
    char *description;
    char *link;
} resource;

// Prototipos de funciones
void addResource(resource *input, FILE *output);
int listResources(FILE *f);
void printResource(FILE *stream, int idLine);
int saveAndExitProgram(FILE *f);
void checkFileErrors(FILE *f);
void freeMemory(resource *r);
char* sAlloc(char *scannedString);