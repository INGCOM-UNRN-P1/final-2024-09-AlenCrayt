#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *nombre_archivo;
size_t memoria_asignada = 2;
int i = 0;

struct Nodo
{
    char *palabra;
    struct Nodo* siguiente;
};

struct Nodo* nodo_nuevo(char palabra_recibida[25], struct Nodo* proximo_nodo)
{
    struct Nodo* nodo = malloc(sizeof(struct Nodo));
    nodo->palabra = palabra_recibida;
    nodo->siguiente = proximo_nodo;
    return nodo;
}

struct Node* constructList(char palabras[], int n)
{
    struct Node *cabeza = NULL, *nodo = NULL;

    for (int i = n - 1; i >= 0; i--)
    {
        nodo = nodo_nuevo(palabras, nodo);
        cabeza = nodo;
    }
 
    return cabeza;
}

int main()
{
    nombre_archivo = malloc(memoria_asignada * sizeof(char));
    printf("Escriba el nombre exacto del archivo que quiere escanear\n");
    while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF) 
    {
        if (strlen(nombre_archivo) > memoria_asignada) 
        {
            memoria_asignada += 2;
            nombre_archivo = realloc(nombre_archivo, memoria_asignada * sizeof(char));
        }
        i += 1;
    }
    nombre_archivo[i] = '\0';
    printf("Asignado %lu bytes de memoria para el nombre del archivo\n", memoria_asignada);
    printf("Buscando: %s\n", nombre_archivo);
    char word[25];
    int p_1;
    int z = 0;
    //A base de un espacio hay que separar las palabras individualmente
    FILE *archivo_abierto = fopen(nombre_archivo, "r");
    fseek(archivo_abierto, 0, SEEK_END);
    //printf("Longitud de archivo: %lu\n", (ftell(archivo_abierto) * sizeof(char)));
    long largo_archivo = ftell(archivo_abierto);
    char *buffer = malloc((largo_archivo * sizeof(char)));
    fseek(archivo_abierto, 0, SEEK_SET);
    size_t cantidad_palabra = fread(buffer, sizeof(char), largo_archivo, archivo_abierto);
    printf("Longitud en caracteres del archivo: %lu\n", cantidad_palabra);
    for (size_t n = 0; strlen(buffer) >= n; n++) {
        //la violacion de segmento que esta ocurriendo parece ser por que el contador esta yendo mas alla de los limites de longitud del archivo
        //el iterador se ejecuta pero no puede leer el contenido de los valores del buffer con lo cual no se llevan a cabo las operaciones
        //tendría que usar p_! como el espacio al principio y p_2 como el espacio al final de una palabra para asi extraer una palabra individual del archivo
        //printf("%lu\n", n);
        if (buffer[n] == ' ') {
            p_1 = n + 1;//como conseguir extraer la primera palabra si no hay un espacio al principio?
            //printf("%d\n", p_1);
            while (buffer[p_1] != ' ' && buffer[p_1] != EOF && buffer[p_1] != '\n') {//extrae la segunda palabra correctamente pero produce errores con el resto
                word[z] = buffer[p_1];
                z += 1;//el problema parece ser que como encuentra el primer espacio se ejecuta el iterador while incluso si es el ultimo espacio disponible en el archivo
                p_1 += 1;
                //ya que z es redeclarado adentro del if entonces se sobreescriben las palabra ya existes en el arreglo word
            }//con la palabras separadas obtenidas, hay que guardarlas en una lista enlazada y filtrar por duplicados
            printf("%s\n", word);
            memset(word, '\0', sizeof(word));
            z = 0;
            //printf("Escaneado\n");
        }//como seguir con el recorrido por el arreglo hasta llegar al proximo espacio?

    }
    printf("programa ejecutado\n");
    free(nombre_archivo);
    return 0;
}