#include <stdlib.h>
#include <stdio.h>
#include "funciones/dominio.h"
#include "funciones/herramientas.h"
#include "funciones/logica.h"

#define ARCHIVO_ADMINS "archivos/admins.dat"


/********* Administradores *********/

/**
 * @brief Genera el archivo inicial de administradores.
 *
 * Verifica si el archivo de administradores existe. En caso
 * contrario, solicita los datos del primer administrador y
 * crea el archivo correspondiente.
 */
void generar_archivo_admins(void)
{
	FILE* archivo = fopen(ARCHIVO_ADMINS, "rb");
	
	if(archivo != NULL)
	{
		fclose(archivo);
		return;
	}
	
	archivo = fopen(ARCHIVO_ADMINS, "wb");

    Administrador admin;

    limpiar_pantalla();

    printf("\n==== Creacion primer admin ====\n");

    printf("- Nombre: ");
    scanString(admin.nombre, 50);

    printf("\n- Password: ");
    scanString(admin.password, 50);

    fwrite(&admin, sizeof(Administrador), 1, archivo);

    fclose(archivo);

    mensaje("OK", "Administrador creado correctamente");

    getchar();
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
void alta_admin(void)
{
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