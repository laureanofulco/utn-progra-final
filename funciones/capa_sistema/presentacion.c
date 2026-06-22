#include "presentacion.h"

#include <stdio.h>
#include <stdlib.h>

#include "../libs/scanner.h"
#include "../../funciones/libs/utils.h"

#define ARCHIVO_PRESENTACIONES "presentaciones.dat"

/**
 *@brief Permite registrar una presentacion
 *
 * Guarada los datos de presentacion en un binario
 *
 *@return void
*/
void alta_presentacion(){
	FILE * archivo = fopen(ARCHIVO_PRESENTACIONES, "ab");
	Presentacion aux;
	
	if(archivo != NULL){
		printf("<---- ALTA PRESENTACIONES  ---->\n");
		printf(" Ingrese id artista: ");
		aux.idArtista = scanInt();
		
		if(!buscar_artista_id(aux.idArtista)){
			mensaje("ERROR", "No se encontro el artista");
			fclose(archivo);
			return;
		}
		
		printf(" Ingrese id del escenario: ");
		aux.idEscenario = scanInt();
		
		if(!buscar_escenario_id(aux.idEscenario)){
			mensaje("ERROR", "No se encontro el escenario");
			fclose(archivo);
			return;
		}
		
		printf("\n -- HORAD DE INCIO --\n");
		printf(" Ingrese hora: ");
		aux.inicio.horas = scanInt();
		printf(" Ingrese minutos: ");
		aux.inicio.minutos = scanInt();
		
		if(!validar_horario(aux.inicio)){
			mensaje("ERROR", "Horario no valido");
			fclose(archivo);
			return;
		}
		
		printf("\n -- DURACION --\n");
		printf(" Ingrese hora: ");
		aux.duracion.horas = scanInt();
		printf(" Ingrese minutos: ");
		aux.duracion.minutos = scanInt();
		
		if(!validar_duracion(aux.duracion)){
			mensaje("ERROR", "Horario no valido");
			fclose(archivo);
			return;
		}
		
		aux.id_presentacion = obtener_id_presentacion();
		aux.presentacion_activo = 1;
		
		fwrite(&aux, sizeof(Presentacion), 1, archivo);
		mensaje("OK", "Presentacion agregada existosamente");
		fclose(archivo);
	}else{
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
void listar_presentaciones(){
    FILE * archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
    Presentacion aux;
    Artista artista;
    Escenario escenario;

    if(archivo == NULL){
        mensaje("ERROR", "No se pudo abrir el archivo");
        return;
    }

    printf("<---- PRESENTACIONES ---->\n");
    while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0){
        if(aux.presentacion_activo == 1){
            printf("\n----------------------\n");
            printf("ID: %d\n", aux.id_presentacion);

            if(buscar_artista_id(aux.idArtista) != -1){
                printf("Artista: %s\n", artista.nombre);
            }else{
                printf("Artista: [no encontrado]\n");
            }
            if(buscar_escenario_id(aux.idEscenario) != -1){
                printf("Escenario: %s\n", escenario.nombre);
            }else{
                printf("Escenario: [no encontrado]\n");
            }
            printf("Inicio: %02d:%02d\n", aux.inicio.horas, aux.inicio.minutos);
            printf("Duracion: %02d:%02d\n",aux.duracion.horas, aux.duracion.minutos);
        }
    }

    fclose(archivo);
}



/**
 *@brief Obtiene siguiente id para la presentacion
 *
 * Recorre el archivo de presentacion buscandoe el 
 * mayor id existente, devolviendo el valor incrementado en 1
 * Si el archivo no existe, o no se puede abrir, devuelve 1
 *
 *@return el utlimo id encontrado + 1.
*/
int obtener_id_presentacion(){
	FILE * archivo = fopen(ARCHIVO_PRESENTACIONES, "rb");
	int ultimoId = 0;
	Presentacion aux;
	
	if(archivo != NULL){
		while(fread(&aux, sizeof(Presentacion), 1, archivo) > 0){
			if(aux.id_presentacion > ultimoId){
				ultimoId = aux.id_presentacion;
			}
		}
		fclose(archivo);	
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	return ultimoId +1;
}