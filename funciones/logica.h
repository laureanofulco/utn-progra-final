#ifndef LOGICA_H
#define LOGICA_H

#include "funciones/dominio.h"

// Administradores
void generar_archivo_admins(void);
int buscar_admin(char nombre[], Administrador *admin);
void alta_admin(void);

// Horarios
int validar_horario(Horario h);
Horario crear_horario(int horas, int minutos);
int comparar_horario(Horario h1, Horario h2);

// Duración
Duracion crear_duracion(int horas, int minutos);

// Escenarios
int obtener_id_escenario(void);
int buscar_escenario_id(int id);
void baja_escenario(void);

// Artistas
int obtener_id_artista(void);


#endif