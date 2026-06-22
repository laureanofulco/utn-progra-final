#include <stdio.h>
#include <stdlib.h>

#include "menu_admin.h"
#include "../capa_sistema/admin.h"
#include "../libs/scanner.h"
#include "../capa_sistema/artista.h"
#include "../capa_sistema/escenario.h"
#include "../capa_sistema/presentacion.h"
#include "../../funciones/libs/utils.h"

////// SOLUCIONAR PROBLEMAS EN EL MENU

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
		opc = scanInt();
		
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
			
			default:
				mensaje("Error", "Ingrese una opcion valida");
				getchar();
				break;
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
        		limpiar_pantalla();
        		alta_artista();
				break;
			}
			case 2:{
				limpiar_pantalla();
				baja_artista();
				getchar();
				break;
			}
			case 3:{
				limpiar_pantalla();
				modificar_artista();
				getchar();
				break;
			}
			case 4:{
				limpiar_pantalla();
				listar_artista();
				getchar();
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
        		limpiar_pantalla();
        		alta_escenario();
        		getchar();
				break;
			}
			case 2:{
				limpiar_pantalla();
				baja_escenario();
				getchar();
				break;
			}
			case 3:{
				limpiar_pantalla();
				modificar_escenario();
				getchar();
				break;
			}
			case 4:{
				limpiar_pantalla();
				listar_escenarios();
				getchar();
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
        		limpiar_pantalla();
        		alta_presentacion();
        		getchar();
				break;
			}
			case 2:{
				limpiar_pantalla();
				
				getchar();
				break;
			}
			case 3:{
				limpiar_pantalla();
				
				getchar();
				break;
			}
			case 4:{
				limpiar_pantalla();
				listar_presentaciones();
				getchar();
				break;
			}
			case 5:{
				limpiar_pantalla();
				
				getchar();
				break;
			}
			case 6:{
				limpiar_pantalla();
				
				getchar();
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