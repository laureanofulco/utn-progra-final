#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include <string.h>

int login_admin(){
	char nombre[50];
	char password[50];
	
	limpiar_pantalla();
	printf("==== LOGIN ADMIN ====\n");
	printf(" Nombre: ");
	fflush(stdin);
	scanString(nombre, 50);
	fflush(stdin);
	printf(" Password: ");
	scanString(password, 50);
	
	convertir_minuscula(nombre);
	convertir_minuscula(password);
	cifrar(password);
	
	if(validar_admin(nombre, password)){
		return 1;
	}
	
	printf("Credenciales incorrectas");
	getchar();
	
	return 0;
}