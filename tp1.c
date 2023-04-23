#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CENTINELA ','
#define ESTADOS 7
#define CARACTERES 256
#define ESTADO_INCIAL 0

int main() {
    FILE *archivoEntrada, *archivoSalida;
    char nombreArchivoEntrada[] = "entrada.txt";
    char nombreArchivoSalida[] = "salida.txt";
    char tablaTransicion[ESTADOS][CARACTERES];
    char *traduccionEstados[ESTADOS] = {"NO RECONOCIDO", "OCTAL", "DECIMAL", "NO RECONOCIDO", "HEXADECIMAL", "OCTAL", "NO RECONOCIDO"};

    // Inicializar la tabla de transición en estado 6
    memset(tablaTransicion, 6, sizeof(tablaTransicion));

    archivoEntrada = fopen(nombreArchivoEntrada, "r");
    archivoSalida = fopen(nombreArchivoSalida, "w");

    if (archivoEntrada == NULL) {
        printf("No se pudo abrir el archivo de entrada\n");
        return 1;
    }

    if (archivoSalida == NULL) {
        printf("No se pudo abrir el archivo de salida\n");
        return 1;
    }

    tablaTransicion[0]['0'] = 1;
    tablaTransicion[1]['x'] = 3;
    tablaTransicion[1]['X'] = 3;

    // Por ser valores consecutivos, podemos asignarlos todos juntos
    memset(&tablaTransicion[0]['1'], 2, 9);

    memset(&tablaTransicion[1]['0'], 5, 8);

    memset(&tablaTransicion[2]['0'], 2, 10);

    memset(&tablaTransicion[3]['0'], 4, 10);
    memset(&tablaTransicion[3]['A'], 4, 6);
    memset(&tablaTransicion[3]['a'], 4, 6);

    memset(&tablaTransicion[4]['0'], 4, 10);
    memset(&tablaTransicion[4]['A'], 4, 6);
    memset(&tablaTransicion[4]['a'], 4, 6);

    memset(&tablaTransicion[5]['0'], 5, 8);

    char caracter;
    char estado = ESTADO_INCIAL;
    char *palabra = "";
    char *palabraAux;
    int largoPalabra = 0;

    while (fread(&caracter, 1, 1, archivoEntrada)) {
        if (caracter == CENTINELA) {
            fprintf(archivoSalida, "%-30s%s\n", palabra, traduccionEstados[estado]);
            estado = ESTADO_INCIAL;
            largoPalabra = 0;
            palabra = "";
            continue;
        }

        if (caracter == ' ') {
            continue;
        }

        largoPalabra = strlen(palabra);
        palabraAux = malloc(largoPalabra + 2);
        strcpy(palabraAux, palabra);
        palabraAux[largoPalabra] = caracter;
        palabraAux[largoPalabra + 1] = '\0';
        free(palabra);
        palabra = palabraAux;

        estado = tablaTransicion[estado][caracter];
    }

    free(palabra);

    fprintf(archivoSalida, "%-30s%s", palabra, traduccionEstados[estado]);

    fclose(archivoEntrada);
    fclose(archivoSalida);
    return 0;
}
