#ifndef FUNCIONES_H
#define FUNCIONES_H


// Librerías Estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Librerías de la cátedra
#include "libs/pila.h"
#include "libs/scanner.h"

// Funciones: Capa de Usuario
#include "capa_usuario/menu.h"
#include "capa_usuario/menu_admin.h"
#include "capa_usuario/menu_usuario.h"
#include "capa_usuario/login.h"
#include "capa_usuario/reportes.h"
#include "capa_usuario/exportacion.h"

// Funciones: Login
#include "capa_sistema/admin.h"
#include "capa_sistema/autenticacion.h"

// Funciones: Capa de Sistema
#include "capa_sistema/artista.h"
#include "capa_sistema/escenario.h"
#include "capa_sistema/presentacion.h"
#include "capa_sistema/horario.h"
#include "capa_sistema/validaciones.h"

#include "funciones/herramientas.h"
#include "funciones/interfaz.h"
#include "funciones/logica.h"
#include "funciones/dominio.h"

#endif