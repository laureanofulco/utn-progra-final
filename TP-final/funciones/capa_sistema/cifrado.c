#include <stdio.h>
#include <stdlib.h>
#include "cifrado.h"

void cifrar(char texto[]){
	int str_len = strlen(texto);
	
	for(int i=0; i<str_len; i++){
		texto[i] = texto[i] ^ (0x54 + i);
	}
	
}