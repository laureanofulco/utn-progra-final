#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief funcion auxiliar que limpia el buffer de entrada
 * todas las funciones de esta librería dejan el buffer de entrada limpio
 * es decir que ninguna función provocará que la siguiente entrada por teclado
 * sea omitida.
 */
void limpiarBuferDeEntrada(void)
{
    int c;
    while ((c = getchar() != '\n' && c != EOF));
}

/**
 * @brief funcion utilitaria para verificar si una precondicion
 * es igual a una postcondicion.
 * Es util para sentencias como while (confirmar('s'))
 * o if (confirmar('n')), etc
 * @return 1 o 0 dependiendo si la condicion es igual al dato escaneado por teclado
 */
int confirmar(char condicion)
{
    char aux = '\0';
    scanf("%c", &aux);
    limpiarBuferDeEntrada();
    return tolower(aux) == tolower(condicion);
}

/**
 * @brief abstracción de scanf para datos de tipo int
 * @return el dato escaneado por teclado
 */
int scanInt(void)
{
    int aux = 0;
    scanf("%d", &aux);
    limpiarBuferDeEntrada();
    return aux;
}

/**
 * @brief abstracción de scanf para datos de tipo float
 * @return el dato escaneado por teclado
 */
float scanFloat(void)
{
    float aux = 0;
    scanf("%f", &aux);
    limpiarBuferDeEntrada();
    return aux;
}

/**
 * @brief abstraccion de la funcion fgets que permite controlar la dimension
 * de la cadena que ingresa por teclado.
 * Garantiza que el string no termine con un salto de linea,
 * efecto conocido e indeseable de fgets.
 * Permite que ingrese una cadena vacía
 * @param string cadena sobre la cual guardar lo escaneado por teclado
 * @param maxLength dimension máxima de la cadena
 * @return la longitud de la cadena escaneada, puede ser mayor o igual a cero
 */
int scanString(char* string, int maxLength)
{
    if (fgets(string, maxLength, stdin) == NULL)
    {
        return -1;
    }
    int ult = strlen(string) - 1;
    if (string[ult] == '\n')
    {
        string[ult] = '\0';
    }
    else
    {
        limpiarBuferDeEntrada();
    }
    return strlen(string);
}
