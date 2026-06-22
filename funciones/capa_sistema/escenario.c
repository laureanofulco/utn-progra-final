#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "escenario.h"
#include "../libs/scanner.h"
#include "../libs/utils.h"
#include "../../funciones/libs/utils.h"

#define ARCHIVO_ESCENARIOS "escenarios.dat"

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
void alta_escenario(){
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "ab");
	char nombreEscenario[50];
	Escenario aux_escenario;
	
	if(archivo != NULL){
		printf(" - ALTA ESCENARIO -\n");
		printf(" Nombre: ");
		scanString(aux_escenario.nombre, 50);
		
		convertir_minuscula(nombreEscenario);
		
		aux_escenario.id = obtener_id_escenario();
		aux_escenario.escenario_activo = 1;
		
		fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);
		fclose(archivo);
		mensaje("OK", "Escenario creado con exito");
		
	}else{
		mensaje("ERROR", "No se pudo abrir el documento");
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
void baja_escenario(){
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "r+b");
	Escenario aux_escenario;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL){
		printf("id del escenario: ");
		id = scanInt();
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0){
			if(aux_escenario.id == id && aux_escenario.escenario_activo == 1){
				aux_escenario.escenario_activo = 0;
				fseek(archivo, -(long)sizeof(Escenario), SEEK_CUR);
				fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);
				
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
 * @brief Modifica los datos de un escenario existente.
 *
 * Busca un escenario activo mediante su identificador y permite
 * actualizar su nombre. Los cambios se almacenan directamente
 * en el archivo de escenarios.
 */
void modificar_escenario(){
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "r+b");
	Escenario aux_escenario;
	int encontrado = 0;
	char nombre[50];
	int id;
	
	if(archivo != NULL){
		printf("- MODIFICAR ESCENARIO -\n");
		printf(" Ingrese id: ");
		id = scanInt();
		
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo)>0){
			if(aux_escenario.id == id && aux_escenario.escenario_activo == 1){
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
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
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
void listar_escenarios(){
	int escenario_activo = 0;
	Escenario aux_escenario;
	
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	if(archivo != NULL){
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0){
			if(aux_escenario.escenario_activo == 1){ 
				escenario_activo = 1;
				printf("\n-----------------------------\n");
				printf(" - Id: %d -\n", aux_escenario.id);
				printf(" - Nombre: %s -\n", aux_escenario.nombre);
				printf(" - Estado: Activo -\n");
				printf("\n-----------------------------\n");
			}
		}
		
		if(escenario_activo == 0){
			mensaje("ERROR", "No hay artistas activos");
		}
		
		fclose(archivo); 
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
}


/**
 * @brief Obtiene el próximo identificador disponible.
 *
 * Recorre el archivo de escenarios buscando el mayor
 * identificador registrado y devuelve dicho valor
 * incrementado en una unidad.
 *
 * @return Último identificador encontrado más uno.
 */
int obtener_id_escenario(){
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	int ultimoIdEscenario = 0;
	Escenario aux_escenario;
	
	if(archivo != NULL){
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0){
			if(aux_escenario.id > ultimoIdEscenario){
				ultimoIdEscenario = aux_escenario.id;
			}
		}
		fclose(archivo);	
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	return ultimoIdEscenario +1;
}


/**
 * @brief Busca un escenario activo por identificador.
 *
 * Recorre el archivo de escenarios verificando si existe
 * un registro activo con el identificador indicado.
 *
 * @param id Identificador del escenario a buscar.
 * @return 1 si el escenario existe y está activo,
 *         0 en caso contrario.
 */
int buscar_escenario_id(int id){
	FILE * archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	int encontrado = 0;
	Escenario aux;
	
	if(archivo != NULL){
		while(fread(&aux, sizeof(Escenario), 1, archivo) > 0){
			if(aux.id == id && aux.escenario_activo == 1){
				encontrado = 1;
			}
			fclose(archivo);
			if(encontrado == 0){
				mensaje("ERROR", "No se encontro el artista");
			}
		
		}
	}
	return encontrado;
}