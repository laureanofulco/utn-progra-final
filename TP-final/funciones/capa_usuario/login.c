#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include <string.h>


/**
 * @brief Permite autenticar a un administrador.
 *
 * Solicita el nombre de usuario y la contraseña,
 * normaliza los datos ingresados y valida las
 * credenciales contra los administradores registrados.
 *
 * El usuario dispone de un máximo de tres intentos
 * antes de que la autenticación falle.
 *
 * @return 1 si el inicio de sesión fue exitoso.
 * @return 0 si se agotaron los intentos permitidos.
 *
 * @see validar_admin()
 * @see cifrar()
 */
int login_admin(){
	char nombre[50];
	char password[50];
	int contador_errores = 0;
	
	while(contador_errores < 3){
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
		
		contador_errores++;
		printf("Credenciales incorrectas, intentos %d/3", contador_errores);
		getchar();
	}
	
	return 0;
}