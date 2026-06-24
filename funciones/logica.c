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

/**
 * @brief Compara dos horarios.
 *
 * @param h1 Primer horario.
 * @param h2 Segundo horario.
 * @returns 1 si h1 es posterior a h2, -1 si h1 es anterior a h2, 0 si ambos horarios son iguales.
 */
int comparar_horario(Horario h1, Horario h2)
{	
	if(h1.horas > h2.horas)
    {
		return 1;
	}
	
	if(h1.horas < h2.horas)
    {
		return -1;
	}
	
	if(h1.minutos > h2.minutos)
    {
		return 1;
	}
	
	if(h1.minutos < h2.minutos)
    {
		return -1;
	}
	
	return 0;
}


/********* Duración *********/
/**
 * @brief Crea una duración segura.
 *
 * Construye una estructura Duracion a partir de horas y minutos
 * verificando que los valores representen una duración válida.
 *
 * @param horas Horas de duración.
 * @param minutos Minutos de duración.
 * @return Duracion inicializada y validada.
 */
Duracion crear_duracion(int horas, int minutos)
{
	Duracion d;
	d.horas = horas;
	d.minutos = minutos;
	
	if(horas >= 0 && horas > 24 && minutos > 0 && minutos < 60)
    {
		d.esValido = 1;
	}
    else
    {
		d.esValido = 0;
	}

	return d;
}


/********* Escenarios *********/
int obtener_id_escenario(void)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	int ultimoIdEscenario = 0;
	Escenario aux_escenario;
	
	if(archivo != NULL)
	{
		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0)
		{
			if(aux_escenario.id > ultimoIdEscenario)
			{
				ultimoIdEscenario = aux_escenario.id;
			}
		}

		fclose(archivo);	

	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	return ultimoIdEscenario +1;
}

/**
 * @brief Busca un escenario activo por identificador.
 *
 * Recorre el archivo de escenarios verificando si existe
 * un registro activo con el identificador indicado.
 *
 * @param id Identificador del escenario a buscar.
 * @return 1 si el escenario existe y está activo,
 *         0 en caso contrario.
 */
int buscar_escenario_id(int id)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "rb");
	int encontrado = 0;
	Escenario aux;
	
	if(archivo != NULL)
	{
		while(fread(&aux, sizeof(Escenario), 1, archivo) > 0)
		{
			if(aux.id == id && aux.escenario_activo == 1)
			{
				encontrado = 1;
			}

			fclose(archivo);
		}
	}

	return encontrado;
}

/**
 * @brief Realiza la baja lógica de un escenario.
 *
 * Solicita el identificador de un escenario activo y modifica
 * su estado estableciendo el campo escenario_activo en 0.
 *
 * El registro permanece almacenado en el archivo.
 */
void baja_escenario(void)
{
	FILE* archivo = fopen(ARCHIVO_ESCENARIOS, "r+b");
	Escenario aux_escenario;
	int encontrado = 0;
	int id;
		
	if(archivo != NULL)
	{
		printf("id del escenario: ");
		id = scanInt();

		while(fread(&aux_escenario, sizeof(Escenario), 1, archivo) > 0)
		{
			if(aux_escenario.id == id && aux_escenario.escenario_activo == 1)
			{
				aux_escenario.escenario_activo = 0;

				fseek(archivo, -(long)sizeof(Escenario), SEEK_CUR);
				fwrite(&aux_escenario, sizeof(Escenario), 1, archivo);
				
				encontrado = 1;
				break;
			}
		}

		fclose(archivo);

		mensaje("OK", "Escenario dado de baja exitosamente");
	}
	else
	{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	if(!encontrado){
		mensaje("ERROR", "No se encontro el escenario");
	}
}


/********* Artistas *********/
/**
 * @brief Obtiene el próximo identificador disponible para un artista.
 *
 * Recorre el archivo de artistas buscando el mayor identificador
 * registrado y devuelve dicho valor incrementado en una unidad.
 *
 * @return El último identificador encontrado más uno.
 */
int obtener_id(){
	FILE * archivo = fopen(ARCHIVO_ARTISTAS, "rb");
	int ultimoId = 0;
	Artista aux;
	
	if(archivo != NULL){
		while(fread(&aux, sizeof(Artista), 1, archivo) > 0){
			if(aux.id > ultimoId){
				ultimoId = aux.id;
			}
		}
		fclose(archivo);	
	}else{
		mensaje("ERROR", "No se pudo abrir el archivo");
	}
	
	return ultimoId +1;
}
