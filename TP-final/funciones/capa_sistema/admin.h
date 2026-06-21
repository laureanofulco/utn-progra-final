/**
 * @file admin.h
 * @brief Definiciones y funciones para la gestión de administradores.
 */
#ifndef ADMIN_H
#define ADMIN_H

typedef struct st_Administrador{
	
	char nombre[50];
	char password[50];
}Administrador;

/**
 * @brief Busca un administrador por nombre.
 *
 * @param nombre Nombre del administrador a buscar.
 * @param admin Puntero donde se almacenarán los datos encontrados.
 * @return 1 si el administrador existe, 0 en caso contrario.
 */
int buscar_admin(const char nombre[], Administrador *admin);

/**
 *@brief Agrega un nuevo admn
*/
void alta_admin();

/**
 *@brief da de baja un admin
*/ 
void baja_admin();

/**
 *@brief Modifica los campos de un admn
*/
int modificar_admin();

/**
 *@brief genera un admin en caso de que el archivo no exista
*/
void generar_archivo_admins();

/**
 *@brief lista los admins existentes
*/
void ver_admins();

#endif