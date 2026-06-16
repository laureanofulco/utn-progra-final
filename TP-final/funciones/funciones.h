#ifndef FUNCIONES_H
#define FUNCIONES_H

/* ===========================
   LIBRERÍAS ESTÁNDAR
   =========================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ===========================
   LIBRERÍAS PROPIAS
   =========================== */

#include "libs/pila.h"
#include "libs/scanner.h"

/* ===========================
   CAPA USUARIO
   =========================== */

#include "capa_usuario/menu.h"
#include "capa_usuario/menu_admin.h"
#include "capa_usuario/menu_usuario.h"
#include "capa_usuario/login.h"
#include "capa_usuario/reportes.h"
#include "capa_usuario/exportacion.h"

/* ===========================
   CAPA SISTEMA
   =========================== */

#include "capa_sistema/admin.h"
#include "capa_sistema/autenticacion.h"
#include "capa_sistema/cifrado.h"

#include "capa_sistema/artista.h"
#include "capa_sistema/escenario.h"
#include "capa_sistema/presentacion.h"
#include "capa_sistema/horario.h"
#include "capa_sistema/validaciones.h"

#endif