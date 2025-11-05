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

/*
 * Mejoras respecto al código anterior (07):
 * - Se activaron los mecanismos de exclusión mutua y sincronización condicional.
 * - Ahora el hilo "reportar" espera correctamente la señal antes de imprimir.
 * - Se eliminó la condición de carrera, garantizando que el valor mostrado sea siempre el actualizado.
 */

/* Variables globales */
int valor = 100;
bool notificar = false;
/* bloqueoCC: protege el acceso a la variable compartida */
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condiCC = PTHREAD_COND_INITIALIZER;

void *reportar(void *nousada) {
	// Aquí el hilo espera hasta recibir la señal de actualización
	pthread_mutex_lock(&bloqueoCC);
	while (!notificar)
		pthread_cond_wait(&condiCC, &bloqueoCC);
	printf("\n\tEl valor es: %d\n", valor);
	pthread_mutex_unlock(&bloqueoCC);
	return NULL;
}

void *asignar(void *nousada) {
	// Aquí el hilo asigna el nuevo valor y notifica al hilo que reporta
	valor = 20;
	pthread_mutex_lock(&bloqueoCC);
	notificar = true;
	pthread_cond_signal(&condiCC);
	pthread_mutex_unlock(&bloqueoCC);
	return NULL;
}

int main() {
	pthread_t reporte, asigne;

	// Se crean los hilos para asignar y reportar el valor
	pthread_create(&reporte, NULL, &reportar, NULL);
	pthread_create(&asigne, NULL, &asignar, NULL);

	// Se espera a que ambos hilos finalicen
	void *nousada;
	pthread_join(reporte, &nousada);
	pthread_join(asigne, &nousada);

	return 0;
}
