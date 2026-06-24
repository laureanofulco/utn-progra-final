#include <stdio.h>
#include <stdlib.h>
#include "herramientas.h"

/**
 * @brief Muestra un mensaje formateado por pantalla.
 *
 * Imprime un título y un mensaje dentro de un bloque
 * delimitado para mejorar la visualización de avisos,
 * errores y confirmaciones.
 *
 * @param titulo Texto que identifica el tipo de mensaje.
 * @param mensaje Contenido del mensaje a mostrar.
 */
void mensaje(const char *titulo, const char *mensaje){
	printf("\n==================================\n");
	printf(" %s\n", titulo);
	printf("\n==================================\n");
	printf(" %s\n", mensaje);
	printf("\n==================================\n");
} 

/**
 * @brief limpia la pantalla, en reemplazo de system("clean") y system("cls")
 * @returns nada, es una función void
 * @note Utiliza códigos de entrada ANSI
 */
void limpiarf(void)
{
    printf("\033[H\033[J");

    // \033[H mueve el cursor al inicio (arriba a la izquierda)
    // \033[J limpia la pantalla desde el cursor hasta el final (abajo a la derecha)
}

/**
 * @brief Pausa la ejecución, reemplazando system("pause")
 * @returns nada, es una función void
 * @note Utiliza fflush y getchar, para trampear y no recurrir a system
 */
void pausarf(void)
{
    printf("Presione una tecla para continuar...\n");       // Llamada a la acción

    fflush(stdout);                                         // Asegura que se muestra el mensaje antes de continuar

    getchar();                                              // Espera un ingreso por teclado
}