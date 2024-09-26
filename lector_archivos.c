#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>

char *nombre_archivo;
size_t memoria_asignada = 2;
int i = 0;

void eliminar_string(char **strings, int *cantidad_de_strings, int indice) {
    free(strings[indice]);

    for (int i = indice; i < *cantidad_de_strings - 1; i++) 
    {
        strings[i] = strings[i + 1];
    }

    (*cantidad_de_strings)--;
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
    printf("Buscando: %s\n", nombre_archivo);

    char word[25] = {NULL};
    char **lista_palabras = NULL;
    int p_1;
    int z = 0;
    int cantidad_de_palabras = 0;

    //A base de un espacio hay que separar las palabras individualmente
    FILE *archivo_abierto = fopen(nombre_archivo, "r");
    fseek(archivo_abierto, 0, SEEK_END);
    long largo_archivo = ftell(archivo_abierto);
    char *buffer = malloc((largo_archivo * sizeof(char)));
    fseek(archivo_abierto, 0, SEEK_SET);
    size_t cantidad_de_caracteres = fread(buffer, sizeof(char), largo_archivo, archivo_abierto);
    
    for (size_t n = 0; strlen(buffer) >= n; n++) 
    {
        if (buffer[n] == ' ') 
        {
            p_1 = n + 1;
            while (buffer[p_1] != ' ' && buffer[p_1] != EOF && buffer[p_1] != '\n') 
            {
                word[z] = buffer[p_1];
                z += 1;
                p_1 += 1;
            }
            cantidad_de_palabras += 1;
            lista_palabras = realloc(lista_palabras , cantidad_de_palabras * sizeof(char*));
            lista_palabras[cantidad_de_palabras - 1] = malloc(strlen(word) + 1);
            strcpy(lista_palabras[cantidad_de_palabras - 1], word);
            memset(word, '\0', strlen(word));
            z = 0;
        }

    }

    free(buffer);

    for (int i = 0; i < cantidad_de_palabras;) 
    {
        int x = i + 1;
        while (x < cantidad_de_palabras)
        {
            if (strcmp(lista_palabras[i], lista_palabras[x]) == 0) 
            {
                eliminar_string(lista_palabras, &cantidad_de_palabras, x);
            }
            x++;
        }
        i++;
    }
    FILE *nuevo_archivo = fopen("archivo_filtrado.txt", "w");
    for (int i = 0; i < cantidad_de_palabras; i++) 
    {
        fprintf(nuevo_archivo, "%s\n", lista_palabras[i]);
    }
    for (int i = 0; i < cantidad_de_palabras; i++) 
    {
        free(lista_palabras[i]);
    }
    fclose(nuevo_archivo);
    printf("El archivo %s ha sido filtrado de duplicados\n", nombre_archivo);
    free(lista_palabras);
    free(nombre_archivo);
    return 0;
}