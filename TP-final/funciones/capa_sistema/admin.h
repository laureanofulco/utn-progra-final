#ifndef ADMIN_H
#define ADMIN_H

typedef struct st_Administrador{
	char nombre[50];
	char password[50];
}Administrador;


int buscar_admin(const char nombre[], Administrador *admin);
void alta_admin(); // agregar admin
void baja_admin(); // Eliminar admin
int modificar_admin();
void generar_archivo_admins();
void ver_admins();

#endif