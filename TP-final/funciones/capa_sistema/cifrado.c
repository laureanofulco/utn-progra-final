#include <stdio.h>
#include <stdlib.h>
#include "cifrado.h"

/**
 * @brief Cifra o descifra una cadena mediante XOR.
 *
 * Recorre la cadena recibida y aplica una operación XOR
 * utilizando una clave variable basada en la posición de
 * cada carácter. Debido a las propiedades del operador XOR,
 * la misma función permite cifrar y descifrar el texto.
 *
 * @param texto Cadena de caracteres a procesar.
 */
void cifrar(char texto[]){
	int str_len = strlen(texto);
	
	for(int i=0; i<str_len; i++){
		texto[i] = texto[i] ^ (0x54 + i);
	}
	
}