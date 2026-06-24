// Guardas
#ifndef HORARIO_H
#define HORARIO_H

// Estructuras
typedef struct st_Fecha{
	int dia;
	int mes;
	int anio;
}Fecha;

typedef struct st_Horario{
	int horas;
	int minutos;
	int esValido;
}Horario;

typedef struct stDuracion{
	int horas;
	int minutos;
	int esValido;
} Duracion;

// Funciones
Horario crear_horario(int horas, int minutos);		//
Duracion crear_duracion(int horas, int minutos);		//

int validar_fecha(Fecha f);		//
int validar_horario(Horario h);		//
int validar_duracion(Duracion d);	//

int comparar_fecha(Fecha f1, Fecha f2);		//
int comparar_horario(Horario h1, Horario h2);	//

int fecha_festival(Fecha f, Fecha inicio_festival, Fecha final_festival);		//
int rango(Fecha incio, Fecha final);	//

int verificar_horario(Horario h1, Horario h2);		//

// Guardas
#endif