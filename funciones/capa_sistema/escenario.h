// Guardas
#ifndef ESCENARIO_H
#define ESCENARIO_H

// Estructuras
typedef struct st_Escenario{
	int id;
	char nombre[50];
	int escenario_activo; 
}Escenario;

// Funciones
void alta_escenario();		//
void baja_escenario();
void modificar_escenario();
void listar_escenarios();
int obtener_id_escenario();		//
int buscar_escenario_id(int id);

// Guardas
#endif