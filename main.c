#include "funciones/herramientas.h"
#include "funciones/interfaz.h"

int main()
{
	int opc = 0;
	
	generar_archivo_admins();
	limpiar_pantalla();
	menu();
	
	return 0;
}