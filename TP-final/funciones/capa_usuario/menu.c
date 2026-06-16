#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "login.h"

void menu(){
	int opc = 0;
	char archivo_admins[] = {"admins.dat"};

	
	do{
		limpiar_pantalla();
		printf("======================\n");
		printf("         MENU         \n");
		printf("======================\n");
		printf(" 1 - Modo admin\n");
		printf(" 2 - Modo usuario\n");
		printf(" 0 - Salir\n");
		printf("\nopcion: ");
		scanf("%d", &opc);
		
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
				
		}
	}while(opc != 0);
}