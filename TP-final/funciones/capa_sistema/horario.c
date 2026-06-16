#include <stdio.h>
#include <stdlib.h>
#include "horario.h"

int validar_fecha(Fecha f){
	if(f.anio != 2026 || f.mes < 1 || f.mes > 12 || f.dia < 1){
		return 0;
	}
	
	int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	return f.dia <= dias_mes[f.mes - 1];
}

int validar_hora(Horario h){
	return (h.hora >=0 && h.hora <= 24) && (h.minuto >= 0 && h.minuto <= 60);
}

int comparar_fecha(Fecha f1, Fecha f2){
	if(f1.anio != f2.anio){
		return (f1.anio < f2.anio) ? -1 : 1;
	}
	
	if(f1.mes != f2.mes){
		return (f1.mes < f2.mes) ? -1 : 1;
	}
	
	if(f1.dia != f2.dia){
		return (f1.dia < f2.dia) ? -1 : 1;
	}
	
	return 0;
}

int misma_fecha(Fecha f1, Fecha f2){
	return (comparar_fecha(f1, f2) == 0);
}

int mismo_horario(Horario h1, Horario h2) {
    return (h1.hora == h2.hora && h1.minuto == h2.minuto);
}

int rango(Fecha f, Fecha inicio, Fecha final){
	return (comparar_fecha(f, inicio) >= 0 && comparar_fecha(f, final) <= 0);
}

int fecha_festival(Fecha f, Fecha incio_festival, Fecha final_festival){
	if(!validar_fecha(f)) return 0;
	return rango(f, incio_festival, final_festival);
}

int verificar_horario(Horario h1, Horario h2){
	int minuto1 = (h1.hora * 60) + h1.minuto;
	int minuto2 = (h2.hora * 60) + h2.minuto;
	int diferencia = minuto1 - minuto2;
	
	if(diferencia < 0 ) diferencia = -diferencia;
	return (diferencia < 60);
}