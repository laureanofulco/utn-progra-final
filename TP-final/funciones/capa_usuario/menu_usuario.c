#include "menu_usuario.h"
#include <stdio.h>
#include <stdlib.h>

void menu_usuario(){
	int opc = 0;
	
	do{
		limpiar_pantalla();
		printf("==========================\n");
		printf("     MENU DE USUARIO      \n");
		printf("==========================\n");
		printf(" 1 - Ver lista de artistas\n");
		printf(" 2 - Buscar artistas por nombre\n");
		printf(" 3 - Ver informacion de un artista\n");
		printf(" 4 - Ver presentaciones de artistas\n");
		printf(" 5 - Ver listado de escenarios\n");
		printf(" 6 - Ver informacion de un escenario\n");
		printf(" 7 - Ver todas las presentaciones\n");
		printf(" 8 - Filtrar por artista\n");
		printf(" 9 - Filtrar por escenario\n");
		printf(" 10 - Filtrar por fecha\n");	
		printf(" 11 - Ver horarios\n");
		printf(" 12 - Ver reportes generados\n");
		printf(" 13 - Consultar información exportada\n");
		printf(" 0 - volver\n");
		printf(" opcion: ");
		opc = scanInt();
		
		switch(opc){
			case 0:{
				limpiar_pantalla();
				menu();
				break;
			}
			case 1:{
				printf(" seleccion la opcion 1\n");
				break;
			}
		}	
	}while(opc != 0);
}