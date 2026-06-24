#include "funciones/interfaz.h"


/********* Administradores *********/
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


/********* Escenarios *********/
/**
 * @brief Registra un nuevo escenario.
 *
 * Solicita el nombre del escenario, genera un identificador
 * único y almacena el registro en el archivo de escenarios.
 *
 * El escenario se crea con estado activo por defecto.
 *
 * @see obtener_id_escenario()
 */
void alta_escenario(void)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "ab");
	char nombreEscenario[50];
	Escenario aux_escenario;
	
	if(archivo != NULL)
    {
		printf(" - ALTA ESCENARIO -\n");
		printf(" Nombre: ");
		scanString(aux_escenario.nombre, 50);
		
		aux_escenario.id = obtener_id_escenario();
		aux_escenario.escenario_activo = 1;
		
		fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);

		fclose(archivo);

		mensaje("OK", "Escenario creado con exito");
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el documento");
	}	
}

/**
 * @brief Lista todos los escenarios activos.
 *
 * Recorre el archivo de escenarios y muestra únicamente los
 * registros cuyo campo escenario_activo es igual a 1.
 *
 * Si no existen escenarios activos, informa dicha situación.
 */
void listar_escenarios(void)
{
	int escenario_activo = 0;
	Escenario aux_escenario;
	
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	if(archivo != NULL)
    {
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0)
        {
			if(aux_escenario.escenario_activo == 1)
            { 
				escenario_activo = 1;
				printf("\n-----------------------------\n");
				printf(" - Id: %d -\n", aux_escenario.id);
				printf(" - Nombre: %s -\n", aux_escenario.nombre);
				printf(" - Estado: Activo -\n");
				printf("\n-----------------------------\n");
			}
		}
		
		if(escenario_activo == 0)
        {
			mensaje("ERROR", "No hay artistas activos");
		}
		
		fclose(archivo);
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}


