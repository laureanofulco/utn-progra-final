#ifndef LOGICA_H
#define LOGICA_H

#include "dominio.h"

// Administradores
void generar_archivo_admins(void);
int buscar_admin(char nombre[], Administrador *admin);
int validar_admin(char nombre[], char contraseña[]);

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
int buscar_artista_id(int id);
int validar_artista(char nombre[]);
void baja_artista(void);


#endif