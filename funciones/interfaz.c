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

/**
 * @brief Permite autenticar a un administrador.
 *
 * Solicita el nombre de usuario y la contraseña,
 * normaliza los datos ingresados y valida las
 * credenciales contra los administradores registrados.
 *
 * El usuario dispone de un máximo de tres intentos
 * antes de que la autenticación falle.
 *
 * @return 1 si el inicio de sesión fue exitoso.
 * @return 0 si se agotaron los intentos permitidos.
 *
 * @see validar_admin()
 * @see cifrar()
 */
int login_admin(void)
{
	char nombre[50];
	char password[50];
	int contador_errores = 0;
	
	while(contador_errores < 3)
	{
		limpiar_pantalla();
		printf("==== LOGIN ADMIN ====\n");

		printf(" Nombre: ");
		scanString(nombre, 50);

		printf(" Password: ");
		scanString(password, 50);
		
		if(validar_admin(nombre, password))
		{
			return 1;
		}
		
		contador_errores++;
		
		printf("Credenciales incorrectas, intentos %d/3", contador_errores);
		pausarf();
	}
	
	return 0;
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

/**
 * @brief Modifica los datos de un escenario existente.
 *
 * Busca un escenario activo mediante su identificador y permite
 * actualizar su nombre. Los cambios se almacenan directamente
 * en el archivo de escenarios.
 */
void modificar_escenario(void)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "r+b");
	Escenario aux_escenario;
	int encontrado = 0;
	char nombre[50];
	int id;
	
	if(archivo != NULL)
    {
		printf("- MODIFICAR ESCENARIO -\n");
		printf(" Ingrese id: ");
		id = scanInt();
		
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo)>0)
        {
			if(aux_escenario.id == id && aux_escenario.escenario_activo == 1)
            {
				printf(" Ingrese nombre nuevo: ");
				scanString(nombre, 50);
				
				strcpy(aux_escenario.nombre, nombre);
				fseek(archivo, -(long)sizeof(Escenario), SEEK_CUR);
				fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);
			
				mensaje("OK", "Nombre modificado con exito");
				fclose(archivo);
			}
		}

		fclose(archivo);
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}


/********* Artistas *********/
/**
 * @brief Registra un nuevo artista en el sistema.
 *
 * Solicita al usuario el nombre y género del artista,
 * normaliza los datos ingresados, asigna un identificador
 * único y almacena el registro en el archivo de artistas.
 *
 * El artista se crea con estado activo por defecto.
 *
 * @see obtener_id()
 * @see convertir_minuscula()
 */

void alta_artista(void)
{
	Artista aux;
	FILE* archivo = fopen(ARCHIVO_ARTISTAS, "ab");
	char nombre_archivo[50];
	char nombre[50];
	char genero[50];
	
	if(archivo != NULL)
    {
		printf("\n- Cargar artista -\n");
		printf(" Nombre: ");
		scanString(nombre, 50);
		printf("\n Genero: ");
		scanString(genero, 50);
		
		strcpy(aux.nombre, nombre);
		strcpy(aux.genero, genero);
		aux.id = obtener_id();
		aux.activo = 1;
		
		fwrite(&aux, sizeof(Artista), 1, archivo);

		fclose(archivo);

		mensaje("OK", "Artista guardado con exito");

		pausarf();
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}

/**
 * @brief Lista todos los artistas activos.
 *
 * Recorre el archivo de artistas y muestra únicamente
 * aquellos cuyo campo "activo" es igual a 1.
 * Si no existen artistas activos, informa el error.
 */
void listar_artista(void)
{
	int activos = 0;
	
	FILE* archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;

	if(archivo != NULL)
    {
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0)
        {
			if(aux.activo == 1)
            { 
				activos = 1;
			
				printf("\n-----------------------------\n");
				printf(" - Id: %d -\n", aux.id);
				printf(" - Nombre: %s -\n", aux.nombre);
				printf(" - Genero: %s     -\n", aux.genero);
				printf(" - Estado: Activo -\n");
				printf("\n-----------------------------\n");
			}
		}
		
		if(activos == 0)
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

/**
 * @brief Busca un artista por nombre.
 *
 * Solicita un nombre al usuario, lo normaliza y lo compara
 * con los registros almacenados en el archivo de artistas.
 * Si encuentra coincidencias, muestra la información del artista.
 *
 * @param nombre Arreglo donde se almacena temporalmente el nombre ingresado.
 * @return 1 si el artista fue encontrado, 0 en caso contrario.
 */
int buscar_artista(char nombre[])
{
	FILE* archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;
	int encontrado = 0;

	if(archivo != NULL)
    {
		printf("Nombre: ");
		scanString(nombre, 50);
	
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0)
        {
			if(strcmp(nombre, aux.nombre) == 0)
            {
				encontrado = 1;
				printf("- ARTISTA -\n");
				printf(" Nombre: %s", aux.nombre);
				printf(" Genero: %s", aux.genero);
			}

			fclose(archivo);

			if(encontrado == 0)
            {
				mensaje("ERROR", "No se encontro el artista");
			}
		
		}
	}

	return encontrado;
}

/**
 * @brief Modifica los datos de un artista existente.
 *
 * Busca un artista activo mediante su identificador y permite
 * modificar su nombre, género o estado. Una vez realizada la
 * modificación, los cambios se guardan en el archivo de artistas.
 *
 * @return 0 si el usuario cancela la operación.
 */
int modificar_artista(void)
{
	FILE* archivo = fopen(ARCHIVO_ARTISTAS, "r+b");
	char nombre[50];
	Artista aux;
	int opc;
	char genero[50];
	int encontrado = 0;
	int id;
	
	if(archivo != NULL)
	{
		printf("- Modificar artista -\n");
		printf("id: ");
		id = scanInt();
				
		while(fread(&aux, sizeof(Artista), 1, archivo)>0)
		{
			if(aux.id == id && aux.activo == 1)
			{
				encontrado = 1;
				printf("[Artista encontrado: %s]\n", nombre);
				printf("Que desea modificar?\n");
				printf(" 1 - nombre\n");
				printf(" 2 - genero\n");
				printf(" 3 - estado\n");
				printf(" 0 - salir\n");
				printf("opcion: ");
				opc = scanInt();
				
				switch(opc)
				{
					case 1:
					{
						printf("Ingrese nombre nuevo: ");
						scanString(nombre, 50);
						
						strcpy(aux.nombre, nombre);
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						mensaje("OK", "Nombre modificado con exito");
						
						fclose(archivo);
						break;
					}
					
					case 2:
					{
						printf("Ingrese genero nuevo: ");
						scanString(genero, 50);
						
						strcpy(aux.genero, genero);
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						mensaje("OK", "Genero modificado con exito");
						
						fclose(archivo);
						break;
					}
					
					case 3:
					{
						aux.activo = 0;
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						
						mensaje("OK", "Estado modificado con exito");
						
						fclose(archivo);
						break;
					}
					
					case 0:
					{
						fclose(archivo);
						return 0;
					}
				}
			}
		}

		fclose(archivo);
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(encontrado != 1)
	{
		mensaje("ERROR", "No se pudo encontrar el artista");
	}
}


/********* Presentaciones *********/
/**
 *@brief Obtiene siguiente id para la presentacion
 *
 * Recorre el archivo de presentacion buscandoe el 
 * mayor id existente, devolviendo el valor incrementado en 1
 * Si el archivo no existe, o no se puede abrir, devuelve 1
 *
 *@return el utlimo id encontrado + 1.
*/
int obtener_id_presentacion(void)
{
	FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
	int ultimoId = 0;
	Presentacion aux;
	
	if(archivo != NULL)
	{
		while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
		{
			if(aux.id_presentacion > ultimoId)
			{
				ultimoId = aux.id_presentacion;
			}
		}

		fclose(archivo);	
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	return ultimoId +1;
}

/**
 *@brief Permite registrar una presentacion
 *
 * Guarada los datos de presentacion en un binario
 *
 *@return void
*/
void alta_presentacion(void)
{
	FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "ab");
	Presentacion aux;
	
	if(archivo != NULL)
	{
		printf("<---- ALTA PRESENTACIONES  ---->\n");
		printf(" Ingrese id artista: ");
		aux.idArtista = scanInt();
		
		if(!buscar_artista_id(aux.idArtista))
		{
			mensaje("ERROR", "No se encontro el artista");
			fclose(archivo);
			return;
		}
		
		printf(" Ingrese id del escenario: ");
		aux.idEscenario = scanInt();
		
		if(!buscar_escenario_id(aux.idEscenario))
		{
			mensaje("ERROR", "No se encontro el escenario");
			fclose(archivo);
			return;
		}
		
		printf("\n -- HORAD DE INCIO --\n");
		printf(" Ingrese hora: ");
		aux.inicio.horas = scanInt();
		printf(" Ingrese minutos: ");
		aux.inicio.minutos = scanInt();
		
		if(!validar_horario(aux.inicio))
		{
			mensaje("ERROR", "Horario no valido");
			fclose(archivo);
			return;
		}
		
		printf("\n -- DURACION --\n");
		printf(" Ingrese hora: ");
		aux.duracion.horas = scanInt();
		printf(" Ingrese minutos: ");
		aux.duracion.minutos = scanInt();
		
		if(!validar_duracion(aux.duracion))
		{
			mensaje("ERROR", "Horario no valido");
			fclose(archivo);
			return;
		}
		
		aux.id_presentacion = obtener_id_presentacion();
		aux.presentacion_activo = 1;
		
		fwrite(&aux, sizeof(Presentacion), 1, archivo);
		mensaje("OK", "Presentacion agregada existosamente");
		fclose(archivo);
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}

/**
 *@brief permite listar todas las presentaciones activas
 *
 * Recorre el archivo presentaciones, y muestra unicamente 
 * cuyo campo "presentacion_Activo" es igual a 1.
 * Para cada presentacion, se busca y muestra la informacion
 * relacionada
 * @see buscar_artista_id 
 * @see  
 *@return void
*/
void listar_presentaciones(void)
{
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
    Presentacion aux;
    Artista artista;
    Escenario escenario;

    if(archivo == NULL)
	{
        mensaje("ERROR", "No se pudo abrir el archivo");
        return;
    }

    printf("<---- PRESENTACIONES ---->\n");

    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
	{
        if(aux.presentacion_activo == 1)
		{
            printf("\n----------------------\n");
            printf("ID: %d\n", aux.id_presentacion);

            if(buscar_artista_id(aux.idArtista) != -1)
			{
                printf("Artista: %s\n", artista.nombre);
            }
			else
			{
                printf("Artista: [no encontrado]\n");
            }

            if(buscar_escenario_id(aux.idEscenario) != -1)
			{
                printf("Escenario: %s\n", escenario.nombre);
            }
			else
			{
                printf("Escenario: [no encontrado]\n");
            }

            printf("Inicio: %02d:%02d\n", aux.inicio.horas, aux.inicio.minutos);
            printf("Duracion: %02d:%02d\n",aux.duracion.horas, aux.duracion.minutos);
        }
    }

    fclose(archivo);
}


// Menúes
void menu_admin(void)
{
	int opc = 0;

	do
	{
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
		
		switch(opc)
		{
			case 0:
			{
				printf("Cerrando sesion . . .");
				break;
			}
			case 1:
			{
				menu_artistas();
				break;
			}
			case 2:
			{
				menu_escenarios();
				break;
			}
			case 3:
			{
				menu_presentaciones();
				break;
			}
			case 4:
			{
				administracion();
				break;
			}
			
			default:
			{
				mensaje("Error", "Ingrese una opcion valida");
				pausarf();
				break;
			}
	   }
	} while(opc != 0);
}

