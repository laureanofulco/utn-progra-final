#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

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
 * @brief Limpia la consola.
 *
 * Ejecuta el comando correspondiente al sistema operativo
 * para borrar el contenido de la pantalla.
 *
 * Utiliza "cls" en Windows y "clear" en sistemas Unix/Linux.
 */
void limpiar_pantalla(){
	/*printf("\033[2J\033[H");
	fflush(stdin);*/
	#ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

/**
 * @brief Convierte una cadena a minúsculas.
 *
 * Recorre la cadena recibida y transforma todos los
 * caracteres alfabéticos a su equivalente en minúscula.
 *
 * La modificación se realiza sobre la cadena original.
 *
 * @param cadena Cadena a convertir.
 */
void convertir_minuscula(char * cadena){
	for(int i=0; cadena[i] != '\0'; i++){
		cadena[i] = tolower((unsigned char)cadena[i]);
	}
}