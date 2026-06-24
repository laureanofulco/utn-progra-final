#include <stdlib.h>
#include <stdio.h>
#include "funciones/herramientas.h"
#include "funciones/dominio.h"
#include "funciones/logica.h"
#include "funciones/interfaz.h"

#define ARCHIVO_ADMINS "archivos/admins.dat"

/**
 * @brief Registra un nuevo administrador.
 *
 * Solicita nombre y contraseña, verifica que el administrador
 * no exista previamente y almacena los datos en el archivo.
 * La contraseña es cifrada antes de ser guardada.
 */
void alta_admin(void)
{
	Administrador admin;
	
	printf("Ingrese nombre: ");
	scanString(admin.nombre, 50);
	
	while(buscar_admin(admin.nombre, NULL) == 1)
    {
		mensaje("ERROR", "Admin existente. Por favor, ingrese un nuevo nombre");

		printf("Ingrese nombre: ");

	    scanString(admin.nombre, 50);
	}
		
	FILE* archivo = fopen(ARCHIVO_ADMINS, "ab");
	
	if(archivo != NULL)
    {		
		printf("Ingrese password: ");
		scanString(admin.password, 50);
			
		fwrite(&admin, sizeof(Administrador), 1, archivo);
        
		fclose(archivo);
		
		mensaje("0K", "Admin creado exitosamente");	
		pausarf();
	} 
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
		pausarf();
	}
}