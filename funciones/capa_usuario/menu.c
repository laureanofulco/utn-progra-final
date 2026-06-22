#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "login.h"
#include "menu_admin.h"
#include "menu_usuario.h"
#include "../libs/scanner.h"
#include "../libs/utils.h"

void menu(){
	int opc;
	
	do{
		limpiar_pantalla();
		printf("======================\n");
		printf("         MENU         \n");
		printf("======================\n");
		printf(" 1 - Modo admin\n");
		printf(" 2 - Modo usuario\n");
		printf(" 0 - Salir\n");
		printf("\nopcion: ");
		opc = scanInt();
		
		switch(opc){
			case 1:{
				if(login_admin()){
					menu_admin();
				}else{
					menu_usuario();
				}
				break;
			}
			case 2:{
				menu_usuario();
				break;
			}
			
			case 0:{
				printf("Saliendo del sistema . . .\n");
				break;
			}
			default:{
				mensaje("ERROR", "Ingrese opcion valida");
				getchar();	
				break;
			}
		}
	}while(opc != 0);
}