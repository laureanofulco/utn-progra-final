// Guardas
#ifndef ARTISTA_H
#define ARTISTA_H

// Includes
#include "horario.h"
#include "escenario.h"

// Estructuras
typedef struct st_Artista{
	int id;
	char nombre[50];
	char genero[50];
	int activo; // 1 = activo
}Artista;

// Funciones
void alta_artista();
void baja_artista();
int modificar_artista();
void listar_artista();
int buscar_artista(char nombre[]);
int validar_artista(char nombre[]);
int obtener_id();
int buscar_artista_id(int id);

// Guardas
#endif