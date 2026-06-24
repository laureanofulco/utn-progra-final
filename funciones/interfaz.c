#include <stdlib.h>
#include <stdio.h>
#include "herramientas.h"
#include "dominio.h"
#include "logica.h"
#include "interfaz.h"


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
			break;
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
		limpiarf();
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
 * @brief Lista todos los escenarios activos en orden alfabético.
 * Utiliza memoria dinámica, ordena mediante Selección y permite exportar a .txt.
 */
void listar_escenarios(void)
{
    FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de escenarios");
        return;
    }

    int capacidad = 10;
    int validos = 0;
    Escenario* arreglo = (Escenario*)malloc(capacidad * sizeof(Escenario));
    
    if(arreglo == NULL)
    {
        mensaje("ERROR", "Fallo la asignacion inicial de memoria");
        fclose(archivo);
        return;
    }

    Escenario aux;
    while(fread(&aux, sizeof(Escenario), 1, archivo) > 0)
    {
        if(aux.escenario_activo == 1)
        {
            if(validos == capacidad)
            {
                capacidad = capacidad + 10;
                Escenario* temp = (Escenario*)realloc(arreglo, capacidad * sizeof(Escenario));
                
				if(temp == NULL)
                {
                    mensaje("ERROR", "Fallo al redimensionar memoria");
                    free(arreglo);
                    fclose(archivo);
                    return;
                }

                arreglo = temp;
            }

            arreglo[validos] = aux;
            validos++;
        }
    }

    fclose(archivo);

    if(validos == 0)
    {
        mensaje("AVISO", "No hay escenarios activos para mostrar");
        free(arreglo);
        return;
    }

    ordenar_escenarios_seleccion(arreglo, validos);

    limpiarf();

    printf("<---- LISTADO DE ESCENARIOS (A-Z) ---->\n");
    for(int i = 0; i < validos; i++)
    {
        printf("\n-----------------------------\n");
        printf(" - Id: %d\n", arreglo[i].id);
        printf(" - Nombre: %s\n", arreglo[i].nombre);
    }
    printf("-----------------------------\n");

    printf("\n¿Desea exportar este listado a un archivo .txt?\n");
    printf(" 1 - Si\n");
    printf(" 2 - No\n");
    printf(" Opcion: ");
    int opc = scanInt();

    if(opc == 1)
    {
        FILE* arch_txt = fopen("archivos/escenarios.txt", "w");
        if(arch_txt != NULL)
        {
            fprintf(arch_txt, "=======================================\n");
            fprintf(arch_txt, "     LISTADO DE ESCENARIOS (A-Z)       \n");
            fprintf(arch_txt, "=======================================\n");
            for(int i = 0; i < validos; i++)
            {
                fprintf(arch_txt, "ID: %d | Nombre: %s\n", arreglo[i].id, arreglo[i].nombre);
            }
            fclose(arch_txt);
            mensaje("OK", "Exportado correctamente en archivos/escenarios.txt");
        }
        else
        {
            mensaje("ERROR", "No se pudo crear el archivo de exportacion");
        }
    }

    free(arreglo);
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

/**
 * @brief Realiza la baja lógica de un escenario.
 *
 * Solicita el identificador de un escenario activo y modifica
 * su estado estableciendo el campo escenario_activo en 0.
 *
 * El registro permanece almacenado en el archivo.
 */
void baja_escenario(void)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "r+b");
	Escenario aux_escenario;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL)
	{
		printf("id del escenario: ");
		id = scanInt();

		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0)
		{
			if(aux_escenario.id == id && aux_escenario.escenario_activo == 1)
			{
				aux_escenario.escenario_activo = 0;

				fseek(archivo, -(long)sizeof(Escenario), SEEK_CUR);
				fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);
				
				encontrado = 1;
				break;
			}
		}

		fclose(archivo);

		mensaje("OK", "Escenario dado de baja exitosamente");
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(!encontrado){
		mensaje("ERROR", "No se encontro el escenario");
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
		aux.id = obtener_id_artista();
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
 * @brief Lista todos los artistas activos en orden alfabético.
 * Utiliza memoria dinámica para cargar los registros, los ordena,
 * los muestra en pantalla y ofrece la opción de exportarlos.
 */
void listar_artista(void)
{
    FILE* archivo = fopen(ARCHIVO_ARTISTAS, "rb");
    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de artistas");
        return;
    }

    int capacidad = 10;
    int validos = 0;
    Artista* arreglo = (Artista*)malloc(capacidad * sizeof(Artista));
    
    if(arreglo == NULL)
    {
        mensaje("ERROR", "Fallo la asignacion inicial de memoria");
        fclose(archivo);
        return;
    }

    Artista aux;

    while(fread(&aux, sizeof(Artista), 1, archivo) > 0)
    {
        if(aux.activo == 1)
        {
            if(validos == capacidad)
            {
                capacidad = capacidad + 10;
                Artista* temp = (Artista*)realloc(arreglo, capacidad * sizeof(Artista));
				
                if(temp == NULL)
                {
                    mensaje("ERROR", "Fallo al redimensionar memoria");
                    free(arreglo);
                    fclose(archivo);
                    return;
                }

                arreglo = temp;
            }
            
            arreglo[validos] = aux;
            validos++;
        }
    }

    fclose(archivo);

    if(validos == 0)
    {
        mensaje("AVISO", "No hay artistas activos para mostrar");
        free(arreglo);
        return;
    }

    ordenar_artistas_seleccion(arreglo, validos);

    limpiarf();

    printf("<---- LISTADO DE ARTISTAS (A-Z) ---->\n");

    for(int i = 0; i < validos; i++)
    {
        printf("\n-----------------------------\n");
        printf(" - Id: %d\n", arreglo[i].id);
        printf(" - Nombre: %s\n", arreglo[i].nombre);
        printf(" - Genero: %s\n", arreglo[i].genero);
    }
    printf("-----------------------------\n");

    printf("\n¿Desea exportar este listado a un archivo .txt?\n");
    printf(" 1 - Si\n");
    printf(" 2 - No\n");
    printf(" Opcion: ");
    int opc = scanInt();

    if(opc == 1)
    {
        FILE* arch_txt = fopen("archivos/artistas.txt", "w");
        if(arch_txt != NULL)
        {
            fprintf(arch_txt, "=======================================\n");
            fprintf(arch_txt, "      LISTADO DE ARTISTAS (A-Z)        \n");
            fprintf(arch_txt, "=======================================\n");
            for(int i = 0; i < validos; i++)
            {
                fprintf(arch_txt, "ID: %d | Nombre: %s | Genero: %s\n", arreglo[i].id, arreglo[i].nombre, arreglo[i].genero);
            }

            fclose(arch_txt);

            mensaje("OK", "Exportado correctamente en archivos/artistas.txt");
        }
        else
        {
            mensaje("ERROR", "No se pudo crear el archivo de exportacion");
        }
    }

    free(arreglo);
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
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0)
        {
			if(strcmp(nombre, aux.nombre) == 0)
            {
				encontrado = 1;
				printf("- ARTISTA -\n");
				printf(" Nombre: %s", aux.nombre);
				printf(" Genero: %s", aux.genero);
			}

			if(encontrado == 0)
            {
				mensaje("ERROR", "No se encontro el artista");
			}
		
		}
		
		fclose(archivo);
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
				printf("[Artista encontrado: %s]\n", aux.nombre);
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

    return 1;
}

/**
 * @brief Da de baja un artista del sistema.
 *
 * Solicita el identificador de un artista y, si existe
 * y se encuentra activo, modifica su estado lógico a
 * inactivo estableciendo el campo activo en 0.
 *
 * La baja es lógica, por lo que el registro permanece
 * almacenado en el archivo de artistas.
 *
 * @see alta_artista()
 * @see modificar_artista()
 */
void baja_artista(void)
{
	FILE* archivo = fopen(ARCHIVO_ARTISTAS, "r+b");
	Artista aux;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL)
	{
		printf("id del artista: ");
		id = scanInt();

		while(fread(&aux, sizeof(Artista), 1, archivo) > 0)
		{
			if(aux.id == id && aux.activo == 1)
			{
				aux.activo = 0;
				fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
				fwrite(&aux, sizeof(Artista), 1, archivo);
				
				encontrado = 1;
				break;
			}
		}
		
		fclose(archivo);

		mensaje("OK", "Artistas dado de baja exitosamente");
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(!encontrado)
	{
		mensaje("ERROR", "No se encontro el artista");
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
 * @brief Registra una nueva presentación en el sistema.
 * * Valida la existencia del artista y el escenario, solicita los
 * horarios y verifica que no existan solapamientos de tiempo.
 */
void alta_presentacion(void)
{
    Presentacion nueva;
    Artista art_aux;
    Escenario esc_aux;
    
    limpiarf();

    printf("- ALTA DE PRESENTACION -\n");
    
    printf(" Ingrese ID del Artista: ");
    nueva.idArtista = scanInt();

    if(buscar_artista_id(nueva.idArtista, &art_aux) != 1)
    {
        mensaje("ERROR", "El artista no existe o fue dado de baja.");
        return;
    }
    
    printf(" Ingrese ID del Escenario: ");
    nueva.idEscenario = scanInt();

    if(buscar_escenario_id(nueva.idEscenario, &esc_aux) != 1)
    {
        mensaje("ERROR", "El escenario no existe o fue dado de baja.");
        return;
    }
    
    printf("\n-- HORARIO DE INICIO --\n");

    printf(" Horas (0-23): ");
    nueva.inicio.horas = scanInt();

    printf(" Minutos (0-59): ");
    nueva.inicio.minutos = scanInt();
    
    if(!validar_horario(nueva.inicio))
    {
        mensaje("ERROR", "Horario de inicio invalido.");
        return;
    }

    printf("\n-- DURACION ESTIMADA --\n");
    printf(" Horas: ");
    nueva.duracion.horas = scanInt();
    printf(" Minutos: ");
    nueva.duracion.minutos = scanInt();
    
    int conflicto = verificar_solapamiento(nueva.idArtista, nueva.idEscenario, nueva.inicio, nueva.duracion, -1); // Le pasamos -1 porque es un alta nueva y todavía no tenemos un ID
    
    if(conflicto == 1)
    {
        mensaje("ERROR", "Solapamiento: El artista ya tiene otro show en ese mismo horario.");
        return;
    }
    else if(conflicto == 2)
    {
        mensaje("ERROR", "Solapamiento: El escenario ya esta ocupado por otro show a esa hora.");
        return;
    }
    
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "ab");

    if(archivo != NULL) 
    {
        nueva.id_presentacion = obtener_id_presentacion(); 
        nueva.presentacion_activo = 1;
        fwrite(&nueva, sizeof(Presentacion), 1, archivo);
        fclose(archivo);
        mensaje("OK", "Presentacion programada y registrada con exito.");
    }
    else 
    {
        mensaje("ERROR", "No se pudo abrir el archivo de presentaciones para guardar.");
    }
}

/**
 * @brief Lista todas las presentaciones activas en orden cronológico.
 * Utiliza memoria dinámica, ordena por horario de inicio y permite exportar a .txt.
 */
void listar_presentaciones(void)
{
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de presentaciones");
        return;
    }

    int capacidad = 10;
    int validos = 0;
    Presentacion* arreglo = (Presentacion*)malloc(capacidad * sizeof(Presentacion));

    if(arreglo == NULL)
    {
        mensaje("ERROR", "Fallo la asignacion inicial de memoria");
        fclose(archivo);
        return;
    }

    Presentacion aux;
    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
    {
        if(aux.presentacion_activo == 1)
        {
            if(validos == capacidad)
            {
                capacidad = capacidad + 10;
                Presentacion* temp = (Presentacion*)realloc(arreglo, capacidad * sizeof(Presentacion));
                if(temp == NULL)
                {
                    mensaje("ERROR", "Fallo al redimensionar memoria");
                    free(arreglo);
                    fclose(archivo);
                    return;
                }
				
                arreglo = temp;
            }

            arreglo[validos] = aux;
            validos++;
        }
    }

    fclose(archivo);

    if(validos == 0)
    {
        mensaje("AVISO", "No hay presentaciones activas para mostrar");
        free(arreglo);
        return;
    }

    ordenar_presentaciones_cronologico(arreglo, validos);

    limpiarf();

    printf("<---- LISTADO DE PRESENTACIONES (CRONOLOGICO) ---->\n");
    
    Artista artista;
    Escenario escenario;

    for(int i = 0; i < validos; i++)
    {
        printf("\n----------------------\n");
        printf("ID Presentacion: %d\n", arreglo[i].id_presentacion);

        if(buscar_artista_id(arreglo[i].idArtista, &artista) == 1)
        {
            printf("Artista: %s\n", artista.nombre);
        }
        else
        {
            printf("Artista: [Dado de baja o no encontrado]\n");
        }

        if(buscar_escenario_id(arreglo[i].idEscenario, &escenario) == 1)
        {
            printf("Escenario: %s\n", escenario.nombre);
        }
        else
        {
            printf("Escenario: [Dado de baja o no encontrado]\n");
        }

        printf("Inicio: %02d:%02d\n", arreglo[i].inicio.horas, arreglo[i].inicio.minutos);
        printf("Duracion: %02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
    }
    printf("----------------------\n");

    printf("\n¿Desea exportar este listado a un archivo .txt?\n");
    printf(" 1 - Si\n");
    printf(" 2 - No\n");
    printf(" Opcion: ");
    int opc = scanInt();

    if(opc == 1)
    {
        FILE* arch_txt = fopen("archivos/presentaciones.txt", "w");

        if(arch_txt != NULL)
        {
            fprintf(arch_txt, "========================================================\n");
            fprintf(arch_txt, "      LISTADO DE PRESENTACIONES (CRONOLOGICO)           \n");
            fprintf(arch_txt, "========================================================\n\n");
            
            for(int i = 0; i < validos; i++)
            {
                fprintf(arch_txt, "ID: %d\n", arreglo[i].id_presentacion);
                
                if(buscar_artista_id(arreglo[i].idArtista, &artista) == 1)
                {
                    fprintf(arch_txt, "Artista: %s\n", artista.nombre);
                }
                else
                {
                    fprintf(arch_txt, "Artista: [No encontrado]\n");
                }

                if(buscar_escenario_id(arreglo[i].idEscenario, &escenario) == 1)
                {
                    fprintf(arch_txt, "Escenario: %s\n", escenario.nombre);
                }
                else
                {
                    fprintf(arch_txt, "Escenario: [No encontrado]\n");
                }

                fprintf(arch_txt, "Inicio: %02d:%02d | Duracion: %02d:%02d\n", 
                        arreglo[i].inicio.horas, arreglo[i].inicio.minutos,
                        arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
                fprintf(arch_txt, "--------------------------------------------------------\n");
            }
            
			fclose(arch_txt);
            
			mensaje("OK", "Exportado correctamente en archivos/presentaciones.txt");
        }
        else
        {
            mensaje("ERROR", "No se pudo crear el archivo de exportacion");
        }
    }

    free(arreglo);
}

/**
 * @brief Realiza la baja lógica de una presentación.
 *
 * Solicita el identificador de una presentación activa y modifica
 * su estado estableciendo el campo presentacion_activo en 0.
 */
void baja_presentacion(void)
{
	FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "r+b");
	Presentacion aux;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL)
	{
		printf("ID de la presentacion a dar de baja: ");
		id = scanInt();

		while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
		{
			if(aux.id_presentacion == id && aux.presentacion_activo == 1)
			{
				aux.presentacion_activo = 0;

				fseek(archivo, -(long)sizeof(Presentacion), SEEK_CUR);
				fwrite(&aux, sizeof(Presentacion), 1, archivo);
				
				encontrado = 1;
				break;
			}
		}

		fclose(archivo);
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo de presentaciones");
		return;
	}
	
	if(encontrado)
	{
		mensaje("OK", "Presentacion dada de baja exitosamente");
	}
	else
	{
		mensaje("ERROR", "No se encontro una presentacion activa con ese ID");
	}
}

/**
 * @brief Modifica los datos de una presentación existente.
 *
 * Busca una presentación activa por su ID y permite modificarla.
 * Cada modificación propuesta (cambio de artista, escenario u horario)
 * pasa por el motor de validación para garantizar que no genere
 * solapamientos de tiempo antes de ser aplicada temporalmente.
 */
void modificar_presentacion(void)
{
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "r+b");
    Presentacion aux;
    Artista art_aux;       
    Escenario esc_aux;     
    int encontrado = 0;
    int id;
    int opc;

    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de presentaciones");
        return;
    }

    printf("- MODIFICAR PRESENTACION -\n");
    printf(" Ingrese ID de la presentacion: ");
    id = scanInt();

    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
    {
        if(aux.id_presentacion == id && aux.presentacion_activo == 1)
        {
            encontrado = 1;
            
            do
            {
                limpiarf();
                printf("=== Presentacion Encontrada (ID: %d) ===\n", aux.id_presentacion);
                printf(" 1 - Cambiar ID Artista (Actual: %d)\n", aux.idArtista);
                printf(" 2 - Cambiar ID Escenario (Actual: %d)\n", aux.idEscenario);
                printf(" 3 - Cambiar Horario de Inicio (Actual: %02d:%02d)\n", aux.inicio.horas, aux.inicio.minutos);
                printf(" 4 - Cambiar Duracion (Actual: %02d:%02d)\n", aux.duracion.horas, aux.duracion.minutos);
                printf(" 0 - Guardar cambios y salir\n");
                printf("\n Opcion: ");
                opc = scanInt();

                switch(opc)
                {
                    case 1:
                    {
                        int nuevoIdArtista;
                        printf("Nuevo ID Artista: ");
                        nuevoIdArtista = scanInt();
                        
                        if(buscar_artista_id(nuevoIdArtista, &art_aux) == 1)
                        {
                            int conflicto = verificar_solapamiento(nuevoIdArtista, aux.idEscenario, aux.inicio, aux.duracion, aux.id_presentacion);
                            
                            if(conflicto == 1)
                            {
                                mensaje("ERROR", "Solapamiento: El artista propuesto ya tiene otro show en este horario");
                            }
                            else
                            {
                                aux.idArtista = nuevoIdArtista;
                                mensaje("OK", "Artista modificado temporalmente");
                            }
                        }
                        else
                        {
                            mensaje("ERROR", "El artista no existe o no esta activo");
                        }
                        pausarf();
                        break;
                    }
                    case 2:
                    {
                        int nuevoIdEscenario;
                        printf("Nuevo ID Escenario: ");
                        nuevoIdEscenario = scanInt();
                        
                        if(buscar_escenario_id(nuevoIdEscenario, &esc_aux) == 1)
                        {
                            int conflicto = verificar_solapamiento(aux.idArtista, nuevoIdEscenario, aux.inicio, aux.duracion, aux.id_presentacion);
                            
                            if(conflicto == 2)
                            {
                                mensaje("ERROR", "Solapamiento: El escenario propuesto esta ocupado en este horario");
                            }
                            else
                            {
                                aux.idEscenario = nuevoIdEscenario;
                                mensaje("OK", "Escenario modificado temporalmente");
                            }
                        }
                        else
                        {
                            mensaje("ERROR", "El escenario no existe o no esta activo");
                        }
                        pausarf();
                        break;
                    }
                    case 3:
                    {
                        Horario nuevoInicio;
                        printf("\n-- NUEVA HORA DE INICIO --\n");
                        printf(" Ingrese hora: ");
                        nuevoInicio.horas = scanInt();
                        printf(" Ingrese minutos: ");
                        nuevoInicio.minutos = scanInt();
                        
                        if(validar_horario(nuevoInicio))
                        {
                            int conflicto = verificar_solapamiento(aux.idArtista, aux.idEscenario, nuevoInicio, aux.duracion, aux.id_presentacion);
                            
                            if(conflicto == 1)
                            {
                                mensaje("ERROR", "Solapamiento: El artista esta ocupado a esa nueva hora");
                            }
                            else if(conflicto == 2)
                            {
                                mensaje("ERROR", "Solapamiento: El escenario esta ocupado a esa nueva hora");
                            }
                            else
                            {
                                aux.inicio = nuevoInicio;
                                mensaje("OK", "Horario de inicio modificado temporalmente");
                            }
                        }
                        else
                        {
                            mensaje("ERROR", "Horario invalido (debe ser entre 00:00 y 23:59)");
                        }
                        pausarf();
                        break;
                    }
                    case 4:
                    {
                        Duracion nuevaDuracion;
                        printf("\n-- NUEVA DURACION --\n");
                        printf(" Ingrese hora: ");
                        nuevaDuracion.horas = scanInt();
                        printf(" Ingrese minutos: ");
                        nuevaDuracion.minutos = scanInt();
                        
                        int conflicto = verificar_solapamiento(aux.idArtista, aux.idEscenario, aux.inicio, nuevaDuracion, aux.id_presentacion);
                        
                        if(conflicto == 1)
                        {
                            mensaje("ERROR", "Solapamiento: Al extender la duracion choca con otro show del artista");
                        }
                        else if(conflicto == 2)
                        {
                            mensaje("ERROR", "Solapamiento: Al extender la duracion choca con otro show en el escenario");
                        }
                        else
                        {
                            aux.duracion = nuevaDuracion;
                            mensaje("OK", "Duracion modificada temporalmente");
                        }
                        pausarf();
                        break;
                    }
                    case 0:
                        break;
                    default:
                        mensaje("ERROR", "Opcion invalida");
                        pausarf();
                        break;
                }
            } while(opc != 0);

            fseek(archivo, -(long)sizeof(Presentacion), SEEK_CUR);
            fwrite(&aux, sizeof(Presentacion), 1, archivo);
            break;
        }
    }

    fclose(archivo);

    if(encontrado == 0)
    {
        mensaje("ERROR", "No se encontro ninguna presentacion activa con ese ID");
    }
    else
    {
        mensaje("OK", "Presentacion actualizada exitosamente en la base de datos");
    }
}

/**
 * @brief Busca, ordena y lista las presentaciones de un artista específico.
 *
 * Utiliza memoria dinámica para almacenar las coincidencias, las ordena
 * cronológicamente por hora de inicio y permite exportarlas a .txt.
 */
void buscar_presentaciones_por_artista(void)
{
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de presentaciones");
        return;
    }

    int id_artista_buscar;
    Artista artista;
    Escenario escenario;

    printf("- BUSCAR PRESENTACIONES POR ARTISTA -\n");
    printf(" Ingrese el ID del artista: ");
    id_artista_buscar = scanInt();

    if(buscar_artista_id(id_artista_buscar, &artista) != 1)
    {
        mensaje("ERROR", "El artista no existe o fue dado de baja");
        fclose(archivo);
        return;
    }

    int capacidad = 10;
    int validos = 0;
    Presentacion* arreglo = (Presentacion*)malloc(capacidad * sizeof(Presentacion));
    
    if(arreglo == NULL)
    {
        mensaje("ERROR", "Fallo la asignacion de memoria");
        fclose(archivo);
        return;
    }

    Presentacion aux;
    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
    {
        if(aux.idArtista == id_artista_buscar && aux.presentacion_activo == 1)
        {
            if(validos == capacidad)
            {
                capacidad += 10;
                Presentacion* temp = (Presentacion*)realloc(arreglo, capacidad * sizeof(Presentacion));
                if(temp == NULL)
                {
                    mensaje("ERROR", "Fallo al redimensionar memoria");
                    free(arreglo);
                    fclose(archivo);
                    return;
                }

                arreglo = temp;
            }
            arreglo[validos] = aux;
            validos++;
        }
    }

    fclose(archivo);

    if(validos == 0)
    {
        printf("\n [No hay presentaciones programadas para este artista]\n");
        pausarf();
        free(arreglo);
        return;
    }

    ordenar_presentaciones_cronologico(arreglo, validos);

    limpiarf();

    printf("<---- PRESENTACIONES DE: %s (CRONOLOGICO) ---->\n", artista.nombre);

    for(int i = 0; i < validos; i++)
    {
        printf("\n----------------------\n");
        printf("ID Presentacion: %d\n", arreglo[i].id_presentacion);

        if(buscar_escenario_id(arreglo[i].idEscenario, &escenario) == 1)
        {
            printf("Escenario: %s\n", escenario.nombre);
        }
        else
        {
            printf("Escenario: [Dado de baja o no encontrado]\n");
        }

        printf("Inicio: %02d:%02d\n", arreglo[i].inicio.horas, arreglo[i].inicio.minutos);
        printf("Duracion: %02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
    }
    printf("----------------------\n");

    printf("\n¿Desea exportar este listado a un archivo .txt?\n");
    printf(" 1 - Si\n");
    printf(" 2 - No\n");
    printf(" Opcion: ");
    int opc = scanInt();

    if(opc == 1)
    {
        FILE* arch_txt = fopen("archivos/presentaciones_artista.txt", "w");
        if(arch_txt != NULL)
        {
            fprintf(arch_txt, "========================================================\n");
            fprintf(arch_txt, "      PRESENTACIONES DE: %s (CRONOLOGICO)               \n", artista.nombre);
            fprintf(arch_txt, "========================================================\n\n");
            
            for(int i = 0; i < validos; i++)
            {
                fprintf(arch_txt, "ID: %d\n", arreglo[i].id_presentacion);
                
                if(buscar_escenario_id(arreglo[i].idEscenario, &escenario) == 1)
                {
                    fprintf(arch_txt, "Escenario: %s\n", escenario.nombre);
                }
                else
                {
                    fprintf(arch_txt, "Escenario: [No encontrado]\n");
                }

                fprintf(arch_txt, "Inicio: %02d:%02d | Duracion: %02d:%02d\n", arreglo[i].inicio.horas, arreglo[i].inicio.minutos, arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
                fprintf(arch_txt, "--------------------------------------------------------\n");
            }

            fclose(arch_txt);

            mensaje("OK", "Exportado correctamente en archivos/presentaciones_artista.txt");
        }
        else
        {
            mensaje("ERROR", "No se pudo crear el archivo de exportacion");
        }
    }

    free(arreglo);
}

/**
 * @brief Busca, ordena y lista las presentaciones de un escenario específico.
 *
 * Utiliza memoria dinámica para almacenar las coincidencias, las ordena
 * cronológicamente por hora de inicio y permite exportarlas a .txt.
 */
void buscar_presentaciones_por_escenario(void)
{
    FILE* archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
    if(archivo == NULL)
    {
        mensaje("ERROR", "No se pudo abrir el archivo de presentaciones");
        return;
    }

    int id_escenario_buscar;
    Artista artista;
    Escenario escenario;

    printf("- BUSCAR PRESENTACIONES POR ESCENARIO -\n");
    printf(" Ingrese el ID del escenario: ");
    id_escenario_buscar = scanInt();

    if(buscar_escenario_id(id_escenario_buscar, &escenario) != 1)
    {
        mensaje("ERROR", "El escenario no existe o fue dado de baja");
        fclose(archivo);
        return;
    }

    int capacidad = 10;
    int validos = 0;
    Presentacion* arreglo = (Presentacion*)malloc(capacidad * sizeof(Presentacion));
    
    if(arreglo == NULL)
    {
        mensaje("ERROR", "Fallo la asignacion de memoria");
        fclose(archivo);
        return;
    }

    Presentacion aux;
    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0)
    {
        if(aux.idEscenario == id_escenario_buscar && aux.presentacion_activo == 1)
        {
            if(validos == capacidad)
            {
                capacidad += 10;
                Presentacion* temp = (Presentacion*)realloc(arreglo, capacidad * sizeof(Presentacion));
                if(temp == NULL)
                {
                    mensaje("ERROR", "Fallo al redimensionar memoria");
                    free(arreglo);
                    fclose(archivo);
                    return;
                }
                arreglo = temp;
            }
            arreglo[validos] = aux;
            validos++;
        }
    }

    fclose(archivo);

    if(validos == 0)
    {
        printf("\n [No hay presentaciones programadas en este escenario]\n");
        pausarf();
        free(arreglo);
        return;
    }

    ordenar_presentaciones_cronologico(arreglo, validos);

    limpiarf();

    printf("<---- PRESENTACIONES EN ESCENARIO: %s (CRONOLOGICO) ---->\n", escenario.nombre);
    for(int i = 0; i < validos; i++)
    {
        printf("\n----------------------\n");
        printf("ID Presentacion: %d\n", arreglo[i].id_presentacion);

        if(buscar_artista_id(arreglo[i].idArtista, &artista) == 1)
        {
            printf("Artista: %s\n", artista.nombre);
        }
        else
        {
            printf("Artista: [Dado de baja o no encontrado]\n");
        }

        printf("Inicio: %02d:%02d\n", arreglo[i].inicio.horas, arreglo[i].inicio.minutos);
        printf("Duracion: %02d:%02d\n", arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
    }
    printf("----------------------\n");

    printf("\n¿Desea exportar este listado a un archivo .txt?\n");
    printf(" 1 - Si\n");
    printf(" 2 - No\n");
    printf(" Opcion: ");
    int opc = scanInt();

    if(opc == 1)
    {
        FILE* arch_txt = fopen("archivos/presentaciones_escenario.txt", "w");
        if(arch_txt != NULL)
        {
            fprintf(arch_txt, "========================================================\n");
            fprintf(arch_txt, "      PRESENTACIONES EN ESCENARIO: %s (CRONOLOGICO)     \n", escenario.nombre);
            fprintf(arch_txt, "========================================================\n\n");
            
            for(int i = 0; i < validos; i++)
            {
                fprintf(arch_txt, "ID: %d\n", arreglo[i].id_presentacion);
                
                if(buscar_artista_id(arreglo[i].idArtista, &artista) == 1)
                {
                    fprintf(arch_txt, "Artista: %s\n", artista.nombre);
                }
                else
                {
                    fprintf(arch_txt, "Artista: [No encontrado]\n");
                }

                fprintf(arch_txt, "Inicio: %02d:%02d | Duracion: %02d:%02d\n", 
                        arreglo[i].inicio.horas, arreglo[i].inicio.minutos,
                        arreglo[i].duracion.horas, arreglo[i].duracion.minutos);
                fprintf(arch_txt, "--------------------------------------------------------\n");
            }
            fclose(arch_txt);
            mensaje("OK", "Exportado correctamente en archivos/presentaciones_escenario.txt");
        }
        else
        {
            mensaje("ERROR", "No se pudo crear el archivo de exportacion");
        }
    }

    free(arreglo);
}


// Menúes
void menu_principal(void)
{
	int opc;
	
	do{
		limpiarf();

		printf("======================\n");
		printf("         MENU         \n");
		printf("======================\n");
		printf(" 1 - Modo admin\n");
		printf(" 2 - Modo usuario\n");
		printf(" 0 - Salir\n");
		
		printf("\nopcion: ");
		opc = scanInt();
		
		switch(opc)
		{
			case 1:
			{
				if(login_admin())
				{
					menu_admin();
				}
				else
				{
					menu_usuario();
				}
				break;
			}

			case 2:
			{
				menu_usuario();
				break;
			}
			
			case 0:
			{
				printf("Saliendo del sistema . . .\n");
				break;
			}

			default:
			{
				mensaje("ERROR", "Ingrese opcion valida");
				pausarf();
				break;
			}
		}
	} while(opc != 0);
}

void menu_admin(void)
{
	int opc = 0;

	do
	{
		limpiarf();
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
				menu_administracion();
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

void menu_artistas(void)
{
	int menu_opcion;
	
	do
	{
		limpiarf();

		printf("==== Gestion de artistas ====\n");
        printf("1 - Alta\n");
        printf("2 - Baja\n");
        printf("3 - Modificar\n");
        printf("4 - Listar\n");
        printf("0 - Volver\n");
        
		printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion)
		{
        	case 1:
			{
        		limpiarf();
        		alta_artista();
				break;
			}
			case 2:
			{
				limpiarf();
				baja_artista();
				pausarf();
				break;
			}
			case 3:
			{
				limpiarf();
				modificar_artista();
				pausarf();
				break;
			}
			case 4:
			{
				limpiarf();
				listar_artista();
				pausarf();
				break;
			}
		}
		
	} while(menu_opcion != 0);
}

void menu_escenarios(void)
{
	int menu_opcion;
	
	do
	{
		limpiarf();

		printf("==== Gestion de escenarios ====\n");
        printf("1 - Alta\n");
        printf("2 - Baja\n");
        printf("3 - Modificar\n");
        printf("4 - Listar\n");
        printf("0 - Volver\n");

        printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion)
		{
        	case 1:
			{
        		limpiarf();
        		alta_escenario();
        		pausarf();
				break;
			}
			case 2:{
				limpiarf();
				baja_escenario();
				pausarf();
				break;
			}
			case 3:{
				limpiarf();
				modificar_escenario();
				pausarf();
				break;
			}
			case 4:{
				limpiarf();
				listar_escenarios();
				pausarf();
				break;
			}
		}
		
	} while(menu_opcion != 0);
}

void menu_presentaciones(void)
{
	int menu_opcion;
	
	do
	{
		limpiarf();

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
        
        switch(menu_opcion)
		{
        	case 1:
			{
        		limpiarf();
        		alta_presentacion();
        		pausarf();
				break;
			}
			case 2:
			{
				limpiarf();
				baja_presentacion();
				pausarf();
				break;
			}
			case 3:
			{
				limpiarf();
				modificar_presentacion();
				pausarf();
				break;
			}
			case 4:
			{
				limpiarf();
				listar_presentaciones();
				pausarf();
				break;
			}
			case 5:
			{
				limpiarf();
				buscar_presentaciones_por_artista();
				pausarf();
				break;
			}
			case 6:
			{
				limpiarf();
				buscar_presentaciones_por_escenario();
				pausarf();
				break;
			}
		}
		
	}while(menu_opcion != 0);
}

void menu_administracion(void)
{
	int menu_opcion;
	
	do
	{
		limpiarf();

		printf("==== Administracion ====\n");
        printf("1 - Reporte general\n");
        printf("2 - Crear admin\n");
        printf("3 - Listar admins\n");
        printf("4 - Modificar admin\n"); 
        printf("0 - Volver\n");
        
		printf(" opcion: ");
        menu_opcion = scanInt();
        
        switch(menu_opcion)
		{
        	case 1:
			{
        		limpiarf();
        		mostrar_reporte_general();
				break;
			}
			
			case 2:{
				limpiarf();
				alta_admin();
				break;
			}
			
			case 3:{
				limpiarf();
				ver_admins();
				break;
			}
			case 4:{
				limpiarf();
				modificar_admin();
				pausarf();
				break;
			}
			
			case 0:{
				break;
			}
		}
		
	} while(menu_opcion != 0);
}

void menu_usuario(void)
{
    int opcion = 0;
    int id_busqueda;
    char nombre_busqueda[50];
    Artista art_aux;
    Escenario esc_aux;
    
    do
    {
        limpiarf();

        printf("==========================\n");
        printf("     MENU DE USUARIO      \n");
        printf("==========================\n");
        printf(" 1 - Ver lista de artistas\n");
        printf(" 2 - Buscar artistas por nombre\n");
        printf(" 3 - Ver informacion de un artista (por ID)\n");
        printf(" 4 - Ver presentaciones de artistas\n");
        printf(" 5 - Ver listado de escenarios\n");
        printf(" 6 - Ver informacion de un escenario (por ID)\n");
        printf(" 7 - Ver todas las presentaciones\n");
        printf(" 8 - Filtrar por escenario\n");
        printf(" 0 - Volver\n");

        printf("\n opcion: ");
        opcion = scanInt();
        
        switch(opcion)
        {
            case 1:
            {
                limpiarf();
                listar_artista();
                pausarf();
                break;
            }
            case 2:
            {
                limpiarf();
                printf("Ingrese el nombre del artista\n");
                scanString(nombre_busqueda, 50);
                buscar_artista(nombre_busqueda); 
                pausarf();
                break;
            }
            case 3:
            {
                limpiarf();
                printf("- BUSCAR INFO DE ARTISTA -\n");
                printf(" Ingrese ID del artista: ");
                id_busqueda = scanInt();
                
                if(buscar_artista_id(id_busqueda, &art_aux) == 1)
                {
                    printf("\n-----------------------------\n");
                    printf(" ID: %d\n", art_aux.id);
                    printf(" Nombre: %s\n", art_aux.nombre);
                    printf(" Genero: %s\n", art_aux.genero);
                    printf("-----------------------------\n");
                }
                else
                {
                    mensaje("ERROR", "El artista no existe o fue dado de baja");
                }
                pausarf();
                break;
            }
            case 4:
            {
                limpiarf();
                buscar_presentaciones_por_artista();
                pausarf();
                break;
            }
            case 5:
            {
                limpiarf();
                listar_escenarios();
                pausarf();
                break;
            }
            case 6:
            {
                limpiarf();
                printf("- BUSCAR INFO DE ESCENARIO -\n");
                printf(" Ingrese ID del escenario: ");
                id_busqueda = scanInt();
                
                if(buscar_escenario_id(id_busqueda, &esc_aux) == 1)
                {
                    printf("\n-----------------------------\n");
                    printf(" ID: %d\n", esc_aux.id);
                    printf(" Nombre: %s\n", esc_aux.nombre);
                    printf("-----------------------------\n");
                }
                else
                {
                    mensaje("ERROR", "El escenario no existe o fue dado de baja");
                }
                pausarf();
                break;
            }
            case 7:
            {
                limpiarf();
                listar_presentaciones();
                pausarf();
                break;
            }
            case 8:
            {
                limpiarf();
                buscar_presentaciones_por_escenario();
                pausarf();
                break;
            }
            case 0:
            {
                limpiarf();
                break;
            }
            default:
            {
                mensaje("ERROR", "Opcion invalida, intente nuevamente.");
                pausarf();
                break;
            }
        }   
    } while(opcion != 0);
}


// Reportes
/**
 * @brief Genera y muestra un reporte con estadísticas generales del sistema.
 *
 * Recorre los archivos de artistas, escenarios y presentaciones para
 * contar cuántos registros se encuentran actualmente activos y muestra
 * un resumen consolidado en pantalla.
 */
void mostrar_reporte_general(void)
{
    FILE* f_artistas = fopen(ARCHIVO_ARTISTAS, "rb");
    FILE* f_escenarios = fopen(ARCHIVO_ESCENARIOS, "rb");
    FILE* f_presentaciones = fopen(ARCHIVO_PRESENTACIONES, "rb");

    int contador_artistas = 0;
    int contador_escenarios = 0;
    int contador_presentaciones = 0;

    if(f_artistas != NULL)
    {
        Artista aux_art;
        while(fread(&aux_art, sizeof(Artista), 1, f_artistas) > 0)
        {
            if(aux_art.activo == 1)
            {
                contador_artistas++;
            }
        }

        fclose(f_artistas);
    }

    if(f_escenarios != NULL)
    {
        Escenario aux_esc;
        while(fread(&aux_esc, sizeof(Escenario), 1, f_escenarios) > 0)
        {
            if(aux_esc.escenario_activo == 1)
            {
                contador_escenarios++;
            }
        }

        fclose(f_escenarios);
    }

    if(f_presentaciones != NULL)
    {
        Presentacion aux_pres;
        while(fread(&aux_pres, sizeof(Presentacion), 1, f_presentaciones) > 0)
        {
            if(aux_pres.presentacion_activo == 1)
            {
                contador_presentaciones++;
            }
        }

        fclose(f_presentaciones);
    }

    printf("========================================\n");
    printf("       ESTADISTICAS DEL FESTIVAL        \n");
    printf("========================================\n\n");
    printf("  -> Total de Artistas Activos:       %d\n", contador_artistas);
    printf("  -> Total de Escenarios Activos:     %d\n", contador_escenarios);
    printf("  -> Total de Presentaciones Activas: %d\n", contador_presentaciones);
    printf("\n========================================\n");
}

