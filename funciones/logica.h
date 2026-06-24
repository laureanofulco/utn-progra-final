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


#endif