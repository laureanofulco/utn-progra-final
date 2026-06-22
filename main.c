#include "funciones/funciones.h"
#include "funciones/libs/utils.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	int opc = 0;
	
	generar_archivo_admins();
	limpiar_pantalla();
	menu();
	
	return 0;
}