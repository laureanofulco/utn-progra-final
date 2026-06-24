#include "funciones/logica.h"

/********* Administradores *********/
/**
 * @brief Genera el archivo inicial de administradores.
 *
 * Verifica si el archivo de administradores existe. En caso
 * contrario, solicita los datos del primer administrador y
 * crea el archivo correspondiente.
 */
void generar_archivo_admins(void)
{
	FILE* archivo = fopen(ARCHIVO_ADMINS, "rb");
	
	if(archivo != NULL)
	{
		fclose(archivo);
		return;
	}
	
	archivo = fopen(ARCHIVO_ADMINS, "wb");

    Administrador admin;

    limpiar_pantalla();

    printf("\n==== Creacion primer admin ====\n");

    printf("- Nombre: ");
    scanString(admin.nombre, 50);

    printf("\n- Password: ");
    scanString(admin.password, 50);

    fwrite(&admin, sizeof(Administrador), 1, archivo);

    fclose(archivo);

    mensaje("OK", "Administrador creado correctamente");

    pausarf();
}

/**
 * @brief Busca un administrador por nombre.
 *
 * Recorre el archivo de administradores buscando una coincidencia
 * con el nombre indicado. Si se encuentra y el parámetro admin
 * no es NULL, copia los datos encontrados en dicha estructura.
 *
 * @param nombre Nombre del administrador a buscar.
 * @param admin Puntero donde se almacenará el administrador encontrado.
 * @return 1 si el administrador existe, 0 en caso contrario.
 */
int buscar_admin(char nombre[], Administrador* admin)
{
	FILE* archivo = fopen(ARCHIVO_ADMINS, "rb");

	Administrador admin_aux;

	int encontrado = 0;
	
	if(archivo != NULL)
    {
		while(fread(&admin_aux, sizeof(Administrador), 1, archivo) > 0)
        {
			if(strcmp(admin_aux.nombre, nombre) == 0)
            {
				encontrado = 1;

				if(admin != NULL)
                {
					*admin = admin_aux;
				}

				break;
			}
		}

		fclose(archivo);
	}
    else
    {
		mensaje("ERROR", "No se pudo abrir el archivo");
	}

	return encontrado;
}


/********* Horarios *********/
/**
 * @brief Verifica si un horario es válido.
 *
 * Comprueba que las horas estén entre 0 y 23 y los
 * minutos entre 0 y 59.
 *
 * @param h Horario a validar.
 * @return 1 si el horario es válido, 0 en caso contrario.
 */
int validar_horario(Horario h)
{
	if(h.horas < 0 || h.horas > 23)
    {
		return 0;
	}

	if(h.minutos < 0 || h.minutos > 59)
    {
		return 0;
	}
	
	return 1;
}

/**
 * @brief Crea un horario seguro.
 *
 * Construye una estructura Horario a partir de horas y minutos
 * e indica si el valor generado es válido mediante el campo
 * esValido.
 *
 * @param horas Hora del día.
 * @param minutos Minutos de la hora.
 * @return Horario inicializado y validado.
 */
Horario crear_horario(int horas, int minutos)
{
	Horario h;
	h.horas = horas;
	h.minutos = minutos;
	
	h.esValido = validar_horario(h);
	
	return h;
}

