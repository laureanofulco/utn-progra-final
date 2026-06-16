#include "admin.h"
#include <stdlib.h>
#include <stdio.h>
#include "cifrado.h"
#include <string.h>
#include <ctype.h> //tolower
#include "../libs/scanner.h"

#define ARCHIVO_ADMINS "admins.dat"


void mensaje(const char *titulo, const char *mensaje){
	printf("\n============================\n");
	printf("  %s\n", titulo);
	printf("\n============================\n");
	printf("  %s\n", mensaje);
	printf("\n============================\n");
}

void convertir_minuscula(char * cadena){
	for(int i=0; cadena[i] != '\0'; i++){
		cadena[i] = tolower((unsigned char)cadena[i]);
	}
}

int buscar_admin(const char nombre[], Administrador *admin){
	FILE * archivo = fopen(ARCHIVO_ADMINS, "rb");
	Administrador admin_aux;
	int encontrado = 0;
	
	if(archivo != NULL){
		while(fread(&admin_aux, sizeof(Administrador), 1, archivo) > 0){
			if(strcmp(admin_aux.nombre, nombre) == 0){
				encontrado = 1;
				if(admin != NULL){
					*admin = admin_aux;
				}
				break;
			}
		}
		fclose(archivo);
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	return encontrado;
}

void generar_archivo_admins(){
	FILE * archivo = fopen(ARCHIVO_ADMINS, "rb");
	
	if(archivo != NULL){
		fclose(archivo);
		return;
	}
	
	archivo = fopen(ARCHIVO_ADMINS, "wb");
	if(archivo){
		Administrador admin;
		limpiar_pantalla();
		printf("\n==== Creacion primer admin ====\n");
		printf(" Nombre: ");
		scanString(admin.nombre, sizeof(admin.nombre));
		printf(" Password: ");
		scanString(admin.password, sizeof(admin.password));
		
		convertir_minuscula(admin.nombre);
		convertir_minuscula(admin.password);
		
		cifrar(admin.password);
		fwrite(&admin, sizeof(Administrador), 1, archivo);
		fclose(archivo);
		mensaje("OK", "Administrador creado correctamente");
		getchar();
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}

void alta_admin(){
	Administrador admin;
	
	printf("Ingrese nombre: ");
	scanString(admin.nombre, 50);
	convertir_minuscula(admin.nombre);
	
	if(buscar_admin(admin.nombre, NULL) == 1){
		mensaje("ERROR", "Admin existente");
		getchar();
		return;
	}
		
	FILE * archivo = fopen(ARCHIVO_ADMINS, "ab");
	
	if(archivo != NULL){		
		printf("Ingrese password: ");
		scanString(admin.password, 50);
		cifrar(admin.password);
			
		fwrite(&admin, sizeof(Administrador), 1, archivo);
		fclose(archivo);
		
		mensaje("0K", "Admin creado exitosamente");	
		getchar();	
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
		getchar();
	}
}

void ver_admins(){
	FILE * archivo = fopen(ARCHIVO_ADMINS, "rb");
	Administrador aux;
	
	if(archivo != NULL){
		while(fread(&aux, sizeof(Administrador), 1, archivo) > 0){
			printf(" - Nombre: %s -\n", aux.nombre);
		}
		fclose(archivo);
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	getchar();
}

int modificar_admin(){
	Administrador admin_aux;
	char nombre[50];
	int opc_mod;
	int encontrado = 0;
	
	printf("==== Modificar admin ====\n\n");
	printf(" ingrese nombre: ");
	scanString(nombre, 50);
	
	convertir_minuscula(admin_aux.nombre);
	
	FILE * archivo = fopen(ARCHIVO_ADMINS, "r+b");
	
	if(archivo == NULL){
		mensaje("ERROR", "No se pudo abrir el archivo");
		return 0;
	}
	
	while(fread(&admin_aux, sizeof(Administrador), 1, archivo) > 0){
		if(strcmp(admin_aux.nombre, nombre) == 0){
			encontrado = 1;
			
			printf("=== Admin encontrado ===\n");
			printf(" nombre    | password   \n");
			printf(" %s        | %s         \n", admin_aux.nombre, admin_aux.password);
			
			printf("\nQue desea modificar\n");
			printf("1 - nombre\n2 - password\n3 - ambos\n");
			printf("Opcion: ");
			opc_mod = scanInt();
			
			switch(opc_mod){
				case 1:{
					printf("Nuevo nombre: ");
					scanString(admin_aux.nombre, 50); 
					convertir_minuscula(admin_aux.nombre);
					break;
				}
				case 2:{
					printf("Nueva contraseña: ");
					scanString(admin_aux.password, 50);
					convertir_minuscula(admin_aux.password);
					cifrar(admin_aux.password);
					break;
				}
				case 3:{
					printf("Nuevo nombre: ");
					scanString(admin_aux.nombre, 50); 
					convertir_minuscula(admin_aux.nombre);
					
					printf("\nNueva contraseña: ");
					scanString(admin_aux.password, 50);
					convertir_minuscula(admin_aux.password);
					cifrar(admin_aux.password);
					break;
				}
			}
			
			fseek(archivo, -(long)sizeof(Administrador), SEEK_CUR);
			fwrite(&admin_aux, sizeof(Administrador), 1, archivo);
		}
	}
	
	fclose(archivo);
	
	if(!encontrado){
		mensaje("ERROR", "Admin no encontrado");
	}else{
		mensaje("OK", "Admin modificado con exito");
	}
	
	return 1;
}