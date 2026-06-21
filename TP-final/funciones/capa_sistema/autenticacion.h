/**
 *@file autenticacion.h
*/
#ifndef AUTENTICACION_H
#define AUTENTICACION_H

/**
 * @brief Verifica las credenciales de un administrador.
 *
 * Busca el administrador indicado y compara la contraseña
 * cifrada proporcionada con la almacenada en el sistema.
 *
 * @param nombre Nombre del administrador.
 * @param pass_cifrada Contraseña cifrada a validar.
 * @return 1 si las credenciales son correctas, 0 en caso contrario.
 */
int validar_admin(const char nombre[], const char pass_cifrada[]);

#endif