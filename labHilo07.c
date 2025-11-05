/*#########################################
#    Pontificia Universidad Javeriana
# Autor: Giovanny Andres Duran Renteria
# Fecha: 30-10-2025
# Tema: Hilos en API POSIX
# Descripción: 
# Supone que x*x es un cálculo altamente costoso
# computacionalmente. Se desea calcular la suma de
# cuadrados usando HILOS POSIX. Se debe aplicar
# paralelismo de cada cuadrado usando los hilos.
######################################### */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

/* Variables globales */
int valor = 100;
bool notificar = false;
/* bloqueoCC: protege el acceso compartido entre hilos */
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condiCC = PTHREAD_COND_INITIALIZER;

void *reportar(void *nousada) {
	// Este hilo imprime el valor actual de la variable compartida
	// pthread_mutex_lock(&bloqueoCC);
	// while (!notificar)
	//	pthread_cond_wait(&condiCC, &bloqueoCC);
	printf("\n\tEl valor es: %d\n", valor);
	// pthread_mutex_unlock(&bloqueoCC);
	return NULL;
}

void *asignar(void *nousada) {
	// Este hilo cambia el valor compartido
	valor = 20;
	// pthread_mutex_lock(&bloqueoCC);
	// notificar = true;
	// pthread_cond_signal(&condiCC);
	// pthread_mutex_unlock(&bloqueoCC);
	return NULL;
}

int main() {
	pthread_t reporte, asigne;

	// Se crean ambos hilos, uno para asignar y otro para reportar
	pthread_create(&reporte, NULL, &reportar, NULL);
	pthread_create(&asigne, NULL, &asignar, NULL);

	// Se espera a que ambos hilos terminen
	void *nousada;
	pthread_join(reporte, &nousada);
	pthread_join(asigne, &nousada);

	return 0;
}

/*
 * Nota:
 * Este código no presenta resultados iguales.
 * En ciertos casos, el hilo que imprime el valor lo hace antes de que
 * el hilo asignador cambie la variable, mostrando aún el valor 100.
 * Esto ocurre por falta de sincronización entre los hilos,
 * generando una condición de carrera al acceder simultáneamente
 * a la variable compartida "valor".
 */
