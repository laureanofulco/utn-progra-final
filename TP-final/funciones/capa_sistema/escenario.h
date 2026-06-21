/**
 *@file escenario.h
 * Implementa las operaciones de alta, baja, modificación,
 * búsqueda y listado de escenarios almacenados en archivos
 * binarios.
*/
#ifndef ESCENARIO_H
#define ESCENARIO_H

typedef struct st_Escenario{
	int id;
	char nombre[50];
	int escenario_activo; 
}Escenario;

void alta_escenario();
void baja_escenario();
void modificar_escenario();
void listar_escenarios();
int obtener_id_escenario();
int buscar_escenario_id(int id);

#endif