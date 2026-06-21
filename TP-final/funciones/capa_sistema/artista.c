#include <stdio.h>
#include <stdlib.h>
#include "artista.h"
#include "../libs/scanner.h"
#include "../../funciones/libs/utils.h"
#include <string.h>

#define ARCHIVO_ARTISTAS "artistas.dat"



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

void alta_artista(){
	Artista aux;
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "ab");
	char nombre_archivo[50];
	char nombre[50];
	char genero[50];
	
	if(archivo != NULL){
		printf("\n- Cargar artista -\n");
		printf(" Nombre: ");
		scanString(nombre, 50);
		printf("\n Genero: ");
		scanString(genero, 50);
		
		convertir_minuscula(nombre);
		convertir_minuscula(genero);
		
		strcpy(aux.nombre, nombre);
		strcpy(aux.genero, genero);
		
		aux.id = obtener_id(); 
		aux.activo = 1;
		
		fwrite(&aux, sizeof(Artista), 1, archivo);
		fclose(archivo);
		mensaje("OK", "Artista guardado con exito");
		getchar();
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
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
void baja_artista(){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "r+b");
	Artista aux;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL){
		printf("id del artista: ");
		id = scanInt();
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(aux.id == id && aux.activo == 1){
				aux.activo = 0;
				fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
				fwrite(&aux, sizeof(Artista), 1, archivo);
				
				encontrado = 1;
				break;
			}
		}
		
		fclose(archivo);
		mensaje("OK", "Artistas dado de baja exitosamente");
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(!encontrado){
		mensaje("ERROR", "No se encontro el artista");
	}
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
int modificar_artista(){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "r+b");
	char nombre[50];
	Artista aux;
	int opc;
	char genero[50];
	int encontrado = 0;
	int id;
	
	if(archivo != NULL){
		printf("- Modificar artista -\n");
		printf("id: ");
		id = scanInt();
				
		while(fread(&aux, sizeof(Artista), 1, archivo)>0){
			if(aux.id == id && aux.activo == 1){
				encontrado = 1;
				printf("[Artista encontrado: %s]\n", nombre);
				printf("Que desea modificar?\n");
				printf(" 1 - nombre\n");
				printf(" 2 - genero\n");
				printf(" 3 - estado\n");
				printf(" 0 - salir\n");
				printf("opcion: ");
				opc = scanInt();
				
				switch(opc){
					case 1:{
						printf("Ingrese nombre nuevo: ");
						scanString(nombre, 50);
						
						convertir_minuscula(nombre);
						strcpy(aux.nombre, nombre);
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						mensaje("OK", "Nombre modificado con exito");
						
						fclose(archivo);
						break;
					}
					
					case 2:{
						printf("Ingrese genero nuevo: ");
						scanString(genero, 50);
						
						convertir_minuscula(genero);
						strcpy(aux.genero, genero);
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						mensaje("OK", "Genero modificado con exito");
						
						fclose(archivo);
						break;
					}
					
					case 3:{
						aux.activo = 0;
						
						fseek(archivo, -(long)sizeof(Artista), SEEK_CUR);
						fwrite(&aux, sizeof(Artista), 1, archivo);
						
						mensaje("OK", "Estado modificado con exito");
						
						fclose(archivo);
						break;
					}
					case 0:{
						fclose(archivo);
						return 0;
					}
				}
			}
		}
		fclose(archivo);
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(encontrado != 1){
		mensaje("ERROR", "No se pudo encontrar el artista");
	}
}


/**
 * @brief Lista todos los artistas activos.
 *
 * Recorre el archivo de artistas y muestra únicamente
 * aquellos cuyo campo "activo" es igual a 1.
 * Si no existen artistas activos, informa el error.
 */
void listar_artista(){
	int activos = 0;
	
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;
	if(archivo != NULL){
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(aux.activo == 1){ 
				activos = 1;
			
				printf("\n-----------------------------\n");
				printf(" - Id: %d -\n", aux.id);
				printf(" - Nombre: %s -\n", aux.nombre);
				printf(" - Genero: %s     -\n", aux.genero);
				printf(" - Estado: Activo -\n");
				printf("\n-----------------------------\n");
			}
		}
		
		if(activos == 0){
				mensaje("ERROR", "No hay artistas activos");
		}
		
		fclose(archivo); 
	}else{
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
int buscar_artista(char nombre[]){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;
	int encontrado = 0;

	if(archivo != NULL){
		printf("Nombre: ");
		scanString(nombre, 50);
		convertir_minuscula(nombre);
	
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(strcmp(nombre, aux.nombre) == 0){
				encontrado = 1;
				printf("- ARTISTA -\n");
				printf(" Nombre: %s", aux.nombre);
				printf(" Genero: %s", aux.genero);
			}
			fclose(archivo);
			if(encontrado == 0){
				mensaje("ERROR", "No se encontro el artista");
			}
		
		}
	}
	return encontrado;
}


/**
 * @brief Verifica la existencia de un artista mediante su identificador.
 *
 * Recorre el archivo de artistas buscando un registro activo
 * cuyo identificador coincida con el indicado.
 *
 * @param id Identificador del artista a buscar.
 * @return 1 si el artista existe y está activo, 0 en caso contrario.
 */
int  buscar_artista_id(int id){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;
	int encontrado = 0;
	if(archivo != NULL){
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(aux.id == id && aux.activo == 1){
				encontrado = 1;
				break;
			}
		}
		fclose(archivo);
	}
	return encontrado;
}


/**
 * @brief Valida si un artista ya se encuentra registrado.
 *
 * Compara el nombre recibido con los nombres almacenados
 * en el archivo de artistas para determinar si ya existe.
 *
 * @param nombre Nombre del artista a validar.
 * @return 1 si el artista existe, 0 en caso contrario.
 */
int validar_artista(char nombre[]){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	Artista aux;
	int existe = 0;
	convertir_minuscula(nombre);

	if(archivo != NULL){
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(strcmp(nombre, aux.nombre) == 0){
				existe = 1;
			}
		}
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	return existe;
}


/**
 * @brief Obtiene el próximo identificador disponible para un artista.
 *
 * Recorre el archivo de artistas buscando el mayor identificador
 * registrado y devuelve dicho valor incrementado en una unidad.
 *
 * @return El último identificador encontrado más uno.
 */
int obtener_id(){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	int ultimoId = 0;
	Artista aux;
	
	if(archivo != NULL){
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(aux.id > ultimoId){
				ultimoId = aux.id;
			}
		}
		fclose(archivo);	
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	return ultimoId +1;
}