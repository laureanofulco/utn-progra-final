// Guardas
#ifndef ADMIN_H
#define ADMIN_H

// Estructuras
typedef struct st_Administrador{
	
	char nombre[50];
	char password[50];
}Administrador;

// Funciones
int buscar_admin(const char nombre[], Administrador *admin);
void alta_admin();
void baja_admin();
int modificar_admin();
void generar_archivo_admins();
void ver_admins();

// Guardas
#endif