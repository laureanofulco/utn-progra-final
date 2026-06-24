#ifndef DOMINIO_H
#define DOMINIO_H

#include <stdlib.h>
#include <stdio.h>
#include "funciones/herramientas.h"

#define ARCHIVO_ADMINS "archivos/admins.dat"

typedef struct st_Administrador
{
	
	char nombre[50];
	char password[50];
} Administrador;

typedef struct st_Fecha
{
	int dia;
	int mes;
	int anio;
} Fecha;

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

typedef struct st_Artista
{
	int id;
	char nombre[50];
	char genero[50];
	int activo; // 1 = activo
} Artista;



#endif