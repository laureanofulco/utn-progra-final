#include "admin.h"
#include <stdlib.h>
#include <stdio.h>
#include "cifrado.h"
#include <string.h>
#include <ctype.h> //tolower
#include "../libs/scanner.h"

#define ARCHIVO_ADMINS "admins.dat"


/**
 * @brief Busca un administrador por nombre.
 *
 * Recorre el archivo de administradores buscando una coincidencia
 * con el nombre indicado. Si se encuentra y el parámetro admin
 * no es NULL, copia los datos encontrados en dicha estructura.
 *
 * @param nombre Nombre del administrador a buscar.
 * @param admin Puntero donde se almacenará el administrador encontrado.
 * @return 1 si el administrador existe, 0 en caso contrario.
 */
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


/**
 * @brief Genera el archivo inicial de administradores.
 *
 * Verifica si el archivo de administradores existe. En caso
 * contrario, solicita los datos del primer administrador y
 * crea el archivo correspondiente.
 */
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

/**
 * @brief Registra un nuevo administrador.
 *
 * Solicita nombre y contraseña, verifica que el administrador
 * no exista previamente y almacena los datos en el archivo.
 * La contraseña es cifrada antes de ser guardada.
 *
 * @see buscar_admin()
 * @see cifrar()
 */
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


/**
 * @brief Muestra todos los administradores registrados.
 *
 * Recorre el archivo de administradores e imprime los nombres
 * de cada registro almacenado.
 */
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


/**
 * @brief Modifica los datos de un administrador.
 *
 * Busca un administrador por nombre y permite modificar
 * su nombre, contraseña o ambos. Los cambios se guardan
 * directamente en el archivo.
 *
 * @return 1 si la operación finaliza correctamente,
 *         0 si ocurre un error al abrir el archivo.
 *
 * @see cifrar()
 */
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