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

    pausarf();
}

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
int buscar_admin(char nombre[], Administrador* admin)
{
	FILE* archivo = fopen(ARCHIVO_ADMINS, "rb");

	Administrador admin_aux;

	int encontrado = 0;
	
	if(archivo != NULL)
    {
		while(fread(&admin_aux, sizeof(Administrador), 1, archivo) > 0)
        {
			if(strcmp(admin_aux.nombre, nombre) == 0)
            {
				encontrado = 1;

				if(admin != NULL)
                {
					*admin = admin_aux;
				}

				break;
			}
		}

		fclose(archivo);
	} else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}

	return encontrado;
}


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
	
	if(buscar_admin(admin.nombre, NULL) == 1)
    {
		mensaje("ERROR", "Admin existente");
		pausarf();
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