#ifndef DOMINIO_H
#define DOMINIO_H


#include <stdlib.h>
#include <stdio.h>
#include "funciones/herramientas.h"


#define ARCHIVO_ADMINS "archivos/admins.dat"
#define ARCHIVO_ESCENARIOS "archivos/escenarios.dat"
#define ARCHIVO_ARTISTAS "archivos/artistas.dat"
#define ARCHIVO_PRESENTACIONES "presentaciones.dat"


typedef struct st_Administrador
{
	
	char nombre[50];
	char password[50];
} Administrador;

typedef struct st_Horario
{
	int horas;
	int minutos;
	int esValido;
} Horario;

typedef struct stDuracion
{
	int horas;
	int minutos;
	int esValido;
} Duracion;

typedef struct st_Escenario
{
	int id;
	char nombre[50];
	int escenario_activo; 
} Escenario;

typedef struct st_Artista
{
	int id;
	char nombre[50];
	char genero[50];
	int activo; // 1 = activo
} Artista;

typedef struct stPresentacion
{
	int id_presentacion;
	int idArtista;
	int idEscenario;
	Horario inicio;
	Duracion duracion;
	int presentacion_activo;
		
} Presentacion;


#endif