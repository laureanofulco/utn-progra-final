#ifndef HORARIO_H
#define HORARIO_H

typedef struct st_Fecha{
	int dia;
	int mes;
	int anio;
}Fecha;

typedef struct st_Hora{
	int minuto;
	int hora;
}Horario;

int validar_fecha(Fecha f);
int validar_hora(Horario h); //verifica que la hora exista

//verifica si una fecha pertenece al festival
int fecha_festival(Fecha f, Fecha incio_festival, Fecha final_festival);


int comparar_fecha(Fecha f1, Fecha f2);
int misma_fecha(Fecha f1, Fecha f2); //Verifica si dos fechas son iguales
int mismo_horario(Horario h1, Horario h2); // igual que misma fecha
int rango(Fecha f, Fecha inicio, Fecha final); // verifica si una fecha se encuentra dentro de un rango
int verificar_horario(Horario h1, Horario h2); //verifica si hay congflicto entre dos horarios que coinciden


#endif