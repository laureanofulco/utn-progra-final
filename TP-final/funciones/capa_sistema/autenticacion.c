#include <stdio.h>
#include <stdlib.h>
#include "autenticacion.h"
#include "admin.h"
#include <string.h>

int validar_admin(const char nombre[], const char pass_cifrada[]){
	Administrador admin;
	
	if(buscar_admin(nombre, &admin)){
		if(strcmp(admin.password, pass_cifrada) == 0){
			return 1;	
		}
	}
	return 0;
}