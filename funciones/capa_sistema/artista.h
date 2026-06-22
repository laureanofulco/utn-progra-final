/**
 * @file artista.h
 * @brief Definiciones y funciones para la gestión de artistas.
 */
#ifndef ARTISTA_H
#define ARTISTA_H

#include "horario.h"
#include "escenario.h"

typedef struct st_Artista{
	int id;
	char nombre[50];
	char genero[50];
	int activo; // 1 = activo
}Artista;

/**
 *@brief registra un nuevo artista
*/
void alta_artista();

/**
 *@brief realiza la debaja un artista
*/
void baja_artista();

/**
 *@brief Permite modificar los campos de un artista
 *@return retona 0 si la operacion es candelada
*/
int modificar_artista();

/**
 *@brief Lista todos los artias activos
 *@return void
*/
void listar_artista();

/**
 *@brief busca artistas por nombre
 *@para nombre del artista
 *@return retorna 1 si eixste, 0 si no
*/
int buscar_artista(char nombre[]);

/**
 *@brief valida que un artista exita
 *@param nombre de artista a validar
 *@return retorna 1 si existe, 0 si no
*/
int validar_artista(char nombre[]);

/**
 *@brief obtiene el siguiente id
 *@return retorna el ultimo id incrementado 1
*/
int obtener_id();

/**
 *@brief busca un artista por su id
 *@param id para realizar las busquedas
 *@return retorna 1 si existe 0 si no
*/
int buscar_artista_id(int id);

#endif