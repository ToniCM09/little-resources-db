#include "libdb.h"
// Añadir un nuevo recurso al archivo
void addResource(resource *input, FILE *output) {
    output = fopen(FILENAME, "a"); //Abrimos el archivo en modo 'append' para no sobreescribir el contenido
    checkFileErrors(output);
    fprintf(output, "\n");
    // Escribimos en el archivo cada uno de los elementos
    fprintf(output, "Nombre: %s", input->name);
    fprintf(output, "Categoria: %s", input->category);
    fprintf(output, "Descripcion: %s", input->description);
    fprintf(output, "Enlace: %s", input->link);

    fclose(output);

    printf("\nNuevo recurso a%cadido correctamente.\n", (char)164);
}
// Busqueda de recursos dentro del fichero e impresión del nombre de cada uno de ellos
int listResources(FILE *f) {
    char stringToFind[50]; //Palabra que irá recogiendo la búsqueda
    int *resourcePos = NULL; // Numero del recurso dentro del fichero
    int counter = -1; // Numero de recurso
    int resourceSelected = -1; // Recurso elegido por el usuario
    printf("--------\n");
    printf("Listado de recursos almacenados. Escribe el numero del recurso para ver el contenido completo:\n");
    while (fscanf(f, "%s", stringToFind) > 0) {  //Bucle que va almacenando cada palabra del fichero
        if (strcmp(stringToFind, "Nombre:") == 0) {
            counter++;
            resourcePos = realloc(resourcePos, (counter + 1) * sizeof(int)); // Asignación de memoria dinámica según el número de recursos que haya
            resourcePos[counter] = ftell(f); // Asignamos la posición del puntero del fichero a el recurso correspondiente
            fgets(stringToFind, 100, f); // Recuperamos la línea entera del nombre
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
// Imprimimos el recurso seleccionado por el usuario
void printResource(FILE *stream, int idLine) {
    char c;
    int numFields = 4; // Número de elementos del recurso
    int bytesUntilName = 7; // Posiciones que debemos retroceder en el puntero del fichero para llegar a la posición deseada. Es un número fijo ya que siempre buscamos -> Nombre:

    fseek(stream, idLine - bytesUntilName, SEEK_SET); //Establecemos la posición del puntero en el fichero

    for (int i = 0; i < numFields; i++) { // Imprimimos caracter a caracter
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
// Comprobamos si hay algún problema con el fichero y, si lo hay, salimos del programa
void checkFileErrors(FILE *f) {
    if (f == NULL) {
        printf("Ha ocurrido un error, revisa el archivo error.log\n");
        freopen("error.log", "w", stderr); // los errores se envian al archivo error.log
        fprintf(stderr, "No se puede abrir el fichero %s", FILENAME);
        fclose(stderr);
        exit(-1); // Salimos del programa 
    }
}
// Reservamos memoria para los elementos *char del recurso
char* sAlloc(char *scannedString) {
    int maxLenght = 201; // Longitud máxima aceptada
    char temp[maxLenght];
    if (fgets(temp, maxLenght, stdin) == NULL) { // Comprobamos si el texto es demasiado largo y, si no lo es, lo asignamos a la variable temp
        printf("Error, el texto es demasiado largo.\n");
        return "Error"; // Se guardará la palabra error en el fichero
    };
    scannedString = strdup(temp); // Reservamos memoria 

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

