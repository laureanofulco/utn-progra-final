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

/**
 * @brief Muestra todos los administradores registrados.
 *
 * Recorre el archivo de administradores e imprime los nombres
 * de cada registro almacenado.
 */
void ver_admins(void)
{
	FILE* archivo = fopen(ARCHIVO_ADMINS, "rb");

	Administrador aux;
	
	if(archivo != NULL)
    {
		while(fread(&aux, sizeof(Administrador), 1, archivo) > 0)
        {
			printf(" - Nombre: %s -\n", aux.nombre);
		}
		
        fclose(archivo);
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	pausarf();
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
int modificar_admin(void)
{
	Administrador admin_aux;
	char nombre[50];
	int opc_mod;
	int encontrado = 0;
	
	printf("==== Modificar admin ====\n\n");
	printf(" Ingrese el nombre: ");
	scanString(nombre, 50);
	
	FILE* archivo = fopen(ARCHIVO_ADMINS, "r+b");
	
	if(archivo == NULL)
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
		return 0;
	}
	
	while(fread(&admin_aux, sizeof(Administrador), 1, archivo) > 0)
    {
		if(strcmp(admin_aux.nombre, nombre) == 0)
        {
			encontrado = 1;
			
			printf("=== Admin encontrado ===\n");
			printf(" nombre    | password   \n");
			printf(" %s        | %s         \n", admin_aux.nombre, admin_aux.password);
			
			printf("\nQue desea modificar\n");
			printf("1 - nombre\n2 - password\n3 - ambos\n");
			printf("Opcion: ");
			opc_mod = scanInt();
			
			switch(opc_mod)
            {
				case 1:
                {
					printf("Nuevo nombre: ");
					scanString(admin_aux.nombre, 50); 
					break;
				}
				case 2:
                {
					printf("Nueva contraseña: ");
					scanString(admin_aux.password, 50);
					break;
				}
				case 3:
                {
					printf("Nuevo nombre: ");
					scanString(admin_aux.nombre, 50); 
					
					printf("\nNueva contraseña: ");
					scanString(admin_aux.password, 50);
					break;
				}
			}
			
			fseek(archivo, -(long)sizeof(Administrador), SEEK_CUR);
			fwrite(&admin_aux, sizeof(Administrador), 1, archivo);
		}
	}
	
	fclose(archivo);
	
	if(encontrado == 0)
    {
		mensaje("ERROR", "Admin no encontrado");
	}
    else
    {
		mensaje("OK", "Admin modificado con exito");
	}
	
	return 1;
}