/**
 * @file funciones.h
 * @brief Punto de acceso principal a los módulos del proyecto.
 *
 * Incluye las dependencias necesarias para el funcionamiento
 * del sistema de gestión de festivales:
 *
 * - Bibliotecas estándar de C.
 * - Librerías auxiliares desarrolladas para el proyecto.
 * - Módulos de la capa de usuario.
 * - Módulos de la capa de sistema.
 *
 * Su objetivo es simplificar la inclusión de dependencias
 * dentro de los distintos archivos fuente del proyecto.
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libs/pila.h"
#include "libs/scanner.h"

#include "capa_usuario/menu.h"
#include "capa_usuario/menu_admin.h"
#include "capa_usuario/menu_usuario.h"
#include "capa_usuario/login.h"
#include "capa_usuario/reportes.h"
#include "capa_usuario/exportacion.h"

#include "capa_sistema/admin.h"
#include "capa_sistema/autenticacion.h"
#include "capa_sistema/cifrado.h"

#include "capa_sistema/artista.h"
#include "capa_sistema/escenario.h"
#include "capa_sistema/presentacion.h"
#include "capa_sistema/horario.h"
#include "capa_sistema/validaciones.h"

#endif