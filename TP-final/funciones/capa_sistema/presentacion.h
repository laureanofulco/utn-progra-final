#ifndef PRESENTACION_H
#define PRESENTACION_H
#include "horario.h"
#include "artista.h"
#include "escenario.h"

typedef struct stPresentacion
{
	int id_presentacion;
	int idArtista;
	int idEscenario;
	Horario inicio;
	Duracion duracion;
	int presentacion_activo;
		
} Presentacion;

/**
 *@file presentaciones.dat
 *@brief manejo de alta, baja, modificaion, listar presentacions
 *@brief obtener_id_presentacion func. aux para obtener id's de presentacion
*/
void alta_presentacion();
void listar_presentaciones();
int obtener_id_presentacion();

#endif