#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "funciones/logica.h"

// Administradores
void alta_admin(void);
void ver_admins(void);
int modificar_admin(void);
int login_admin(void);

// Escenarios
void alta_escenario(void);
void listar_escenarios(void);
void modificar_escenario(void);

// Artistas
void alta_artista(void);
void listar_artista(void);
int buscar_artista(char nombre[]);
int modificar_artista(void);

// Presentaciones
int obtener_id_presentacion(void);
void alta_presentacion(void);
void listar_presentaciones(void);

// Menúes
void menu_admin(void);
void menu_artistas(void);
void menu_escenarios(void);
void menu_presentaciones(void);
void menu_administracion(void);
void menu_usuario(void);

#endif