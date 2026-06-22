#include <stdio.h>
#include <stdlib.h>
#include "horario.h"

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
Horario crear_horario(int horas, int minutos){
	Horario h;
	h.horas = horas;
	h.minutos = minutos;
	
	h.esValido = validar_horario(h);
	
	return h;
}

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
Duracion crear_duracion(int horas, int minutos){
	Duracion d;
	d.horas = horas;
	d.minutos = minutos;
	
	if(horas >= 0 && minutos >= 0 && minutos <= 59){
		d.esValido = 1;
	}else{
		d.esValido = 0;
	}
	return d;
}

/**
 * @brief Verifica si una fecha es válida.
 *
 * Comprueba que el día, mes y año existan considerando
 * meses de distinta duración y años bisiestos.
 *
 * @param f Fecha a validar.
 * @return 1 si la fecha es válida, 0 en caso contrario.
 */
int validar_fecha(Fecha f){
	if(f.anio < 1){
		return 0;
	}
	
	if(f.mes < 1 || f.mes > 12){
		return 0;
	}
	
	if(f.dia < 1){
		return 0;
	}
	
	switch(f.mes){
		case 4:
		case 6:
		case 9:
		case 11:
			return f.dia <= 30;
		case 2:{
			if((f.anio % 4 == 0 && f.anio % 100 != 0) || (f.anio % 400 == 0)){
				return f.dia <= 29;
			}
			return f.dia <= 28;
		}
		default:
			return f.dia <= 31;
	}
}

/**
 * @brief Verifica si un horario es válido.
 *
 * Comprueba que las horas estén entre 0 y 23 y los
 * minutos entre 0 y 59.
 *
 * @param h Horario a validar.
 * @return 1 si el horario es válido, 0 en caso contrario.
 */
int validar_horario(Horario h){
	if(h.horas < 0 || h.horas > 23){
		return 0;
	}
	if(h.minutos < 0 || h.minutos > 59){
		return 0;
	}
	
	return 1;
}


/**
 * @brief Verifica si una duración es válida.
 *
 * Comprueba que la duración posea valores positivos
 * y que los minutos se encuentren entre 0 y 59.
 *
 * @param d Duración a validar.
 * @return 1 si la duración es válida, 0 en caso contrario.
 */
int validar_duracion(Duracion d){
	if(d.horas < 0){
		return 0;
	}
	
	if(d.minutos < 0 || d.minutos > 59){
		return 0;
	}
	
	return 1;
}


/**
 * @brief Compara dos fechas.
 *
 * @param f1 Primera fecha.
 * @param f2 Segunda fecha.
 * @return 1 si f1 es posterior a f2.
 * @return -1 si f1 es anterior a f2.
 * @return 0 si ambas fechas son iguales.
 */
int comparar_fecha(Fecha f1, Fecha f2){
	
	if(f1.anio > f2.anio){
		return 1;
	}
	
	if(f1.anio < f2.anio){
		return -1;
	}
	
	if(f1.mes > f2.mes){
		return 1;
	}
	
	if(f1.mes < f2.mes){
		return -1;
	}
	
	if(f1.dia > f2.dia){
		return 1;
	}
	
	if(f1.dia < f2.dia){
		return -1;
	}
	return 0;
}


/**
 * @brief Compara dos horarios.
 *
 * @param h1 Primer horario.
 * @param h2 Segundo horario.
 * @return 1 si h1 es posterior a h2.
 * @return -1 si h1 es anterior a h2.
 * @return 0 si ambos horarios son iguales.
 */
int comparar_horario(Horario h1, Horario h2){
	Horario h;
	
	if(h1.horas > h2.horas){
		return 1;
	}
	
	if(h1.horas < h2.horas){
		return -1;
	}
	
	if(h1.minutos > h2.minutos){
		return 1;
	}
	
	if(h1.minutos < h2.minutos){
		return -1;
	}
	
	return 0;
}

/**
 * @brief Verifica si una fecha pertenece al festival.
 *
 * Determina si una fecha se encuentra dentro del rango
 * comprendido entre el inicio y el fin del festival.
 *
 * @param f Fecha a verificar.
 * @param inicio_festival Fecha de inicio.
 * @param final_festival Fecha de finalización.
 * @return 1 si la fecha pertenece al festival,
 *         0 en caso contrario.
 */
int fecha_festival(Fecha f, Fecha inicio_festival, Fecha final_festival){
	return (comparar_fecha(f, inicio_festival) >= 0 && comparar_fecha(f, final_festival) <= 0);
}


/**
 * @brief Verifica si un rango de fechas es válido.
 *
 * Comprueba que la fecha inicial no sea posterior
 * a la fecha final.
 *
 * @param inicio Fecha inicial.
 * @param final Fecha final.
 * @return 1 si el rango es válido, 0 en caso contrario.
 */
int rango(Fecha inicio, Fecha final){
	if(comparar_fecha(inicio, final) == 1){
		return 0;
	} 
	
	return 1;
}