# Robot de revisión 🤖

Este es un programa que ve que hay en el repositorio, compila y ejecuta
algunos chequeos adicionales.

Esto _no_ es la corrección, es una ayuda a la misma.


## Repositorio
**branch/revision:** master, d2345f6
,
Informe creado el jue 26 sep 2024 16:56:23 -03

### Archivos contenidos
```total 4,0K
-rw-rw-r-- 1 mrtin mrtin 3,0K sep 26 16:56 lector_archivos.c

```
## Analisis
### sobre `final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c

#### gcc -Wall -Wextra

```
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c: In function ‘main’:
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:35:22: warning: initialization of ‘char’ from ‘void *’ makes integer from pointer without a cast [-Wint-conversion]
   35 |     char word[25] = {NULL};
      |                      ^~~~
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:35:22: note: (near initialization for ‘word[0]’)
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:24:31: warning: dereference of possibly-NULL ‘nombre_archivo’ [CWE-690] [-Wanalyzer-possible-null-dereference]
   24 |     while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF)
      |            ~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~
  ‘main’: events 1-2
    |
    |   22 |     nombre_archivo = malloc(memoria_asignada * sizeof(char));
    |      |                      ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                      |
    |      |                      (1) this call could return NULL
    |   23 |     printf("Escriba el nombre exacto del archivo que quiere escanear\n");
    |   24 |     while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF)
    |      |            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                               |
    |      |                               (2) ‘nombre_archivo + (sizetype)i’ could be NULL: unchecked value from (1)
    |
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:29:28: warning: leak of ‘nombre_archivo’ [CWE-401] [-Wanalyzer-malloc-leak]
   29 |             nombre_archivo = realloc(nombre_archivo, memoria_asignada * sizeof(char));
      |             ~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ‘main’: events 1-2
    |
    |   22 |     nombre_archivo = malloc(memoria_asignada * sizeof(char));
    |      |                      ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                      |
    |      |                      (1) allocated here
    |   23 |     printf("Escriba el nombre exacto del archivo que quiere escanear\n");
    |   24 |     while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF)
    |      |            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                               |
    |      |                               (2) assuming ‘nombre_archivo’ is non-NULL
    |
  ‘main’: events 3-8
    |
    |   24 |     while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF)
    |      |                                                    ^
    |      |                                                    |
    |      |                                                    (3) following ‘true’ branch...
    |   25 |     {
    |   26 |         if (strlen(nombre_archivo) > memoria_asignada)
    |      |            ~~~~~~~~~~~~~~~~~~~~~~~                  
    |      |            ||
    |      |            |(4) ...to here
    |      |            (5) following ‘true’ branch...
    |   27 |         {
    |   28 |             memoria_asignada += 2;
    |      |                              ~~                     
    |      |                              |
    |      |                              (6) ...to here
    |   29 |             nombre_archivo = realloc(nombre_archivo, memoria_asignada * sizeof(char));
    |      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                            | |
    |      |                            | (7) when ‘realloc’ fails
    |      |                            (8) ‘nombre_archivo’ leaks here; was allocated at (1)
    |
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:47:24: warning: use of possibly-NULL ‘buffer’ where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
   47 |     for (size_t n = 0; strlen(buffer) >= n; n++)
      |                        ^~~~~~~~~~~~~~
  ‘main’: events 1-2
    |
    |   44 |     char *buffer = malloc((largo_archivo * sizeof(char)));
    |      |                    ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                    |
    |      |                    (1) this call could return NULL
    |......
    |   47 |     for (size_t n = 0; strlen(buffer) >= n; n++)
    |      |                        ~~~~~~~~~~~~~~
    |      |                        |
    |      |                        (2) argument 1 (‘buffer’) from (1) could be NULL where non-null expected
    |
In file included from final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:3:
/usr/include/string.h:407:15: note: argument 1 of ‘strlen’ must be non-null
  407 | extern size_t strlen (const char *__s)
      |               ^~~~~~
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:60:54: warning: dereference of NULL ‘lista_palabras’ [CWE-476] [-Wanalyzer-null-dereference]
   60 |             lista_palabras[cantidad_de_palabras - 1] = malloc(strlen(word) + 1);
      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
  ‘main’: events 1-10
    |
    |   36 |     char **lista_palabras = NULL;
    |      |            ^~~~~~~~~~~~~~
    |      |            |
    |      |            (1) ‘lista_palabras’ is NULL
    |      |            (2) ‘lista_palabras’ is NULL
    |      |            (3) ‘lista_palabras’ is NULL
    |......
    |   47 |     for (size_t n = 0; strlen(buffer) >= n; n++)
    |      |                        ~~~~~~~~~~~~~~~~~~~
    |      |                                       |
    |      |                                       (4) following ‘true’ branch...
    |   48 |     {
    |   49 |         if (buffer[n] == ' ')
    |      |            ~      ~
    |      |            |      |
    |      |            |      (5) ...to here
    |      |            (6) following ‘true’ branch...
    |   50 |         {
    |   51 |             p_1 = n + 1;
    |      |                   ~~~~~
    |      |                     |
    |      |                     (7) ...to here
    |......
    |   59 |             lista_palabras = realloc(lista_palabras , cantidad_de_palabras * sizeof(char*));
    |      |                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                              |
    |      |                              (8) when ‘realloc’ fails
    |   60 |             lista_palabras[cantidad_de_palabras - 1] = malloc(strlen(word) + 1);
    |      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                           |                          |
    |      |                           |                          (10) dereference of NULL ‘lista_palabras + ((long unsigned int)cantidad_de_palabras * 8 + 18446744073709551608)’
    |      |                           (9) ‘lista_palabras’ is NULL
    |
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:61:13: warning: use of possibly-NULL ‘*lista_palabras_169 + _62’ where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
   61 |             strcpy(lista_palabras[cantidad_de_palabras - 1], word);
      |             ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ‘main’: events 1-7
    |
    |   47 |     for (size_t n = 0; strlen(buffer) >= n; n++)
    |      |                        ~~~~~~~~~~~~~~~^~~~
    |      |                                       |
    |      |                                       (1) following ‘true’ branch...
    |   48 |     {
    |   49 |         if (buffer[n] == ' ')
    |      |            ~      ~                    
    |      |            |      |
    |      |            |      (2) ...to here
    |      |            (3) following ‘true’ branch...
    |   50 |         {
    |   51 |             p_1 = n + 1;
    |      |                   ~~~~~                
    |      |                     |
    |      |                     (4) ...to here
    |......
    |   59 |             lista_palabras = realloc(lista_palabras , cantidad_de_palabras * sizeof(char*));
    |      |                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                              |
    |      |                              (5) when ‘realloc’ succeeds, moving buffer
    |   60 |             lista_palabras[cantidad_de_palabras - 1] = malloc(strlen(word) + 1);
    |      |                                                        ~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                                                        |
    |      |                                                        (6) this call could return NULL
    |   61 |             strcpy(lista_palabras[cantidad_de_palabras - 1], word);
    |      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |             |
    |      |             (7) argument 1 (‘*lista_palabras_169 + _62’) from (6) could be NULL where non-null expected
    |
/usr/include/string.h:141:14: note: argument 1 of ‘strcpy’ must be non-null
  141 | extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
      |              ^~~~~~

```

 [0]

#### cppcheck

```
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:1:0: information: Include file: "stdio.h" not found. [missingInclude]
#include "stdio.h"
^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:2:0: information: Include file: "stdlib.h" not found. [missingInclude]
#include "stdlib.h"
^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:3:0: information: Include file: "string.h" not found. [missingInclude]
#include "string.h"
^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:4:0: information: Include file: <time.h> not found. Please note: Cppcheck does not need standard library headers to get proper results. [missingIncludeSystem]
#include <time.h>
^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:29:13: error: Common realloc mistake: 'nombre_archivo' nulled but not freed upon failure [memleakOnRealloc]
            nombre_archivo = realloc(nombre_archivo, memoria_asignada * sizeof(char));
            ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:59:13: error: Common realloc mistake: 'lista_palabras' nulled but not freed upon failure [memleakOnRealloc]
            lista_palabras = realloc(lista_palabras , cantidad_de_palabras * sizeof(char*));
            ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:13:14: style: Local variable 'i' shadows outer variable [shadowVariable]
    for (int i = indice; i < *cantidad_de_strings - 1; i++) {
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: note: Shadowed declaration
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:13:14: note: Shadow variable
    for (int i = indice; i < *cantidad_de_strings - 1; i++) {
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:70:14: style: Local variable 'i' shadows outer variable [shadowVariable]
    for (int i = 0; i < cantidad_de_palabras;)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: note: Shadowed declaration
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:70:14: note: Shadow variable
    for (int i = 0; i < cantidad_de_palabras;)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:85:14: style: Local variable 'i' shadows outer variable [shadowVariable]
    for (int i = 0; i < cantidad_de_palabras; i++)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: note: Shadowed declaration
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:85:14: note: Shadow variable
    for (int i = 0; i < cantidad_de_palabras; i++)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:89:14: style: Local variable 'i' shadows outer variable [shadowVariable]
    for (int i = 0; i < cantidad_de_palabras; i++)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: note: Shadowed declaration
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:89:14: note: Shadow variable
    for (int i = 0; i < cantidad_de_palabras; i++)
             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:46:35: style: Variable 'cantidad_de_caracteres' is assigned a value that is never used. [unreadVariable]
    size_t cantidad_de_caracteres = fread(buffer, sizeof(char), largo_archivo, archivo_abierto);
                                  ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:78:40: style: Variable 'cantidad_de_caracteres' is assigned a value that is never used. [unreadVariable]
                cantidad_de_caracteres -= 1;
                                       ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:6:7: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
char *nombre_archivo;
      ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:7:8: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
size_t memoria_asignada = 2;
       ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:22:5: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    nombre_archivo = malloc(memoria_asignada * sizeof(char));
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:24:13: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF)
            ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:26:20: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
        if (strlen(nombre_archivo) > memoria_asignada)
                   ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:28:13: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
            memoria_asignada += 2;
            ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:29:13: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
            nombre_archivo = realloc(nombre_archivo, memoria_asignada * sizeof(char));
            ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:31:9: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
        i += 1;
        ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:33:5: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    nombre_archivo[i] = '\0';
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:34:30: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    printf("Buscando: %s\n", nombre_archivo);
                             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:41:35: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    FILE *archivo_abierto = fopen(nombre_archivo, "r");
                                  ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:94:62: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    printf("El archivo %s ha sido filtrado de duplicados\n", nombre_archivo);
                                                             ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:96:10: error: Regla 11: No esta permitido el uso de variables globales, {token.str} [chequeos-globales]
    free(nombre_archivo);
         ^

```

 [0]

#### splint

```
Splint 3.1.2 --- 21 Feb 2021

< loading standard library /usr/share/splint/lib/standard.lcd .... >
< preprocessing >
< checking final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c >
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c: (in function eliminar_string)
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:11:10:
    Unqualified storage strings[indice] passed as only param:
    free (strings[indice])
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:13:13:
    Parse Error. (For help on parse errors, see splint -help parseerrors.)
*** Cannot continue.

```

 [1]

#### clang

```
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:35:22: error: incompatible pointer to integer conversion initializing 'char' with an expression of type 'void *' [-Wint-conversion]
    char word[25] = {NULL};
                     ^~~~
/usr/lib/llvm-16/lib/clang/16/include/stddef.h:89:16: note: expanded from macro 'NULL'
#  define NULL ((void*)0)
               ^~~~~~~~~~
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:46:12: warning: variable 'cantidad_de_caracteres' set but not used [-Wunused-but-set-variable]
    size_t cantidad_de_caracteres = fread(buffer, sizeof(char), largo_archivo, archivo_abierto);
           ^
1 warning and 1 error generated.

```

 [1]

#### clang-tidy

```
38 warnings and 1 error generated.
Error while processing /home/mrtin/dev/pi/dredd/final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c.
76 warnings and 3 errors generated.
Error while processing /home/mrtin/dev/pi/dredd/final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c.
error: error reading 'pic' [clang-diagnostic-error]
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:6:7: warning: variable 'nombre_archivo' is non-const and globally accessible, consider making it const [cppcoreguidelines-avoid-non-const-global-variables]
char *nombre_archivo;
      ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:6:7: warning: variable 'nombre_archivo' provides global access to a non-const object; consider making the pointed-to data 'const' [cppcoreguidelines-avoid-non-const-global-variables]
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:7:8: warning: variable 'memoria_asignada' is non-const and globally accessible, consider making it const [cppcoreguidelines-avoid-non-const-global-variables]
size_t memoria_asignada = 2;
       ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:8:5: warning: variable 'i' is non-const and globally accessible, consider making it const [cppcoreguidelines-avoid-non-const-global-variables]
int i = 0;
    ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:24:33: warning: narrowing conversion from 'int' to signed type 'char' is implementation-defined [cppcoreguidelines-narrowing-conversions]
    while ((nombre_archivo[i] = getchar()) != '\n' && *nombre_archivo != EOF) 
                                ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:35:15: warning: 25 is a magic number; consider replacing it with a named constant [cppcoreguidelines-avoid-magic-numbers]
    char word[25] = {NULL};
              ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:35:22: error: incompatible pointer to integer conversion initializing 'char' with an expression of type 'void *' [clang-diagnostic-int-conversion]
    char word[25] = {NULL};
                     ^
/usr/lib/llvm-16/lib/clang/16/include/stddef.h:89:16: note: expanded from macro 'NULL'
#  define NULL ((void*)0)
               ^~~~~~~~~~
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:37:9: warning: variable 'p_1' is not initialized [cppcoreguidelines-init-variables]
    int p_1;
        ^
            = 0
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:46:12: warning: variable 'cantidad_de_caracteres' set but not used [clang-diagnostic-unused-but-set-variable]
    size_t cantidad_de_caracteres = fread(buffer, sizeof(char), largo_archivo, archivo_abierto);
           ^
final-2024-09-submissions/final-2024-09-AlenCrayt/lector_archivos.c:51:19: warning: narrowing conversion from 'size_t' (aka 'unsigned long') to signed type 'int' is implementation-defined [cppcoreguidelines-narrowing-conversions]
            p_1 = n + 1;
                  ^
Suppressed 58 warnings (58 in non-user code).
Use -header-filter=.* to display errors from all non-system headers. Use -system-headers to display errors from system headers as well.
Found compiler error(s).

```

 [1]

# Importante
_Este informe solo es una ayuda a quien corregirá el Trabajo Practico_
