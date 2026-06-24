// Guardas
#ifndef PRESENTACION_H
#define PRESENTACION_H
#include "horario.h"
#include "artista.h"
#include "escenario.h"

// Estructuras
typedef struct stPresentacion
{
	int id_presentacion;
	int idArtista;
	int idEscenario;
	Horario inicio;
	Duracion duracion;
	int presentacion_activo;
		
} Presentacion;

// Funciones
void alta_presentacion();			//
void listar_presentaciones();
int obtener_id_presentacion();

// Guardas
#endif