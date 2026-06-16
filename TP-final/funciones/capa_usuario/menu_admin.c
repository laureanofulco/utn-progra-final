#include <stdio.h>
#include <stdlib.h>

#include "menu_admin.h"
#include "../capa_sistema/admin.h"
#include "../libs/scanner.h"

void limpiar_pantalla(){
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
#endif
}

void pausa(){
	printf("\n\nPresione ENTER para continuar");
	getchar();
}

void menu_admin(){
	int opc = 0;
	
	do{
		limpiar_pantalla();
		printf("===================\n");
		printf("    MENU ADMIN     \n");
		printf("===================\n");
		printf(" 1 - Gestion de artistas\n");
		printf(" 2 - Gestion de escenarios\n");
		printf(" 3 - Gestion de presentaciones\n");
		printf(" 4 - Administracion\n");
		printf(" 0 - Cerrar sesion\n");
		printf(" opcion: ");
		scanf("%d", &opc);
		
		switch(opc){
			case 0:{
				printf("Cerrando sesion . . .");
				break;
			}
			case 1:{
				menu_artistas();
				break;
			}
			case 2:{
				menu_escenarios();
				break;
			}
			case 3:{
				menu_presentaciones();
				break;
			}
			case 4:{
				administracion();
				break;
			}
	   }
	}while(opc != 0);
}

void menu_artistas(){
	int menu_opcion;
	
	do{
		limpiar_pantalla();
		printf("==== Gestion de artistas ====\n");
        printf("1 - Alta\n");
        printf("2 - Baja\n");
        printf("3 - Modificar\n");
        printf("4 - Listar\n");
        printf("0 - Volver\n");
        printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion){
        	case 1:{
        		printf("Opcion 1");
				break;
			}
		}
		
	}while(menu_opcion != 0);
}

void menu_escenarios(){
	int menu_opcion;
	
	do{
		limpiar_pantalla();
		printf("==== Gestion de escenarios ====\n");
        printf("1 - Alta\n");
        printf("2 - Baja\n");
        printf("3 - Modificar\n");
        printf("4 - Listar\n");
        printf("0 - Volver\n");
        printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion){
        	case 1:{
        		printf("Opcion 1");
				break;
			}
		}
		
	}while(menu_opcion != 0);
}

void menu_presentaciones(){
	int menu_opcion;
	
	do{
		limpiar_pantalla();
		printf("==== Gestion de presentaciones ====\n");
        printf("1 - Alta\n");
        printf("2 - Baja\n");
        printf("3 - Modificar\n");
        printf("4 - Listar\n");
        printf("5 - Buscar por artista\n");
        printf("6 - Buscar por escenario\n");
        printf("0 - Volver\n");
        printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion){
        	case 1:{
        		printf("Opcion 1");
				break;
			}
		}
		
	}while(menu_opcion != 0);
}

void administracion(){
	int menu_opcion;
	
	do{
		limpiar_pantalla();
		printf("==== Administracion ====\n");
        printf("1 - Reportes\n");
        printf("2 - Exportar datos\n");
        printf("3 - Crear admin\n");
        printf("4 - Listar admins\n");
        printf("5 - Modificar admin\n"); 
        printf("0 - Volver\n");
        printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion){
        	case 1:{
        		limpiar_pantalla();
        		printf("[ADMIN] Generar reportes");
				break;
			}
			
			case 3:{
				limpiar_pantalla();
				printf("[ADMIN] crear administrador\n");
				alta_admin();
				break;
			}
			
			case 4:{
				limpiar_pantalla();
				printf("[ADMIN] ver lista de admins\n");
				ver_admins();
				break;
			}
			case 5:{
				limpiar_pantalla();
				printf("[ADMIN] Modificar admin\n");
				modificar_admin();
				pausa();
				break;
			}
			
			case 0:{
				
				break;
			}
		}
		
	}while(menu_opcion != 0);
}