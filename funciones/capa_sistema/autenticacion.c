#include <stdio.h>
#include <stdlib.h>
#include "autenticacion.h"
#include "admin.h"
#include <string.h>

/**
 * @brief Verifica las credenciales de un administrador.
 *
 * Busca el administrador indicado y compara la contraseña
 * cifrada recibida con la almacenada en el sistema.
 *
 * @param nombre Nombre del administrador.
 * @param pass_cifrada Contraseña cifrada a validar.
 * @return 1 si las credenciales son correctas, 0 en caso contrario.
 *
 * @see buscar_admin()
 */
int validar_admin(const char nombre[], const char pass_cifrada[]){
	Administrador admin;
	
	if(buscar_admin(nombre, &admin)){
		if(strcmp(admin.password, pass_cifrada) == 0){
			return 1;	
		}
	}
	return 0;
}