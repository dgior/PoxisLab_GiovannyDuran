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
#include <pthread.h>

/*
 * Mejoras respecto al código anterior (05):
 * - Se añadió un mutex (bloqueoCC) para proteger la variable compartida "acumulado".
 * - Con esta exclusión mutua se elimina la condición de carrera presente en la versión anterior.
 * - Ahora el resultado es correcto el 100 % de las veces, sin interferencia entre los hilos.
 */

/* Variables globales */
int acumulado = 0;
/* bloqueoCC: protege el acceso concurrente a la variable acumulado */
pthread_mutex_t bloqueoCC = PTHREAD_MUTEX_INITIALIZER;

void *cuadrados(void *x) {
	// Cada hilo calcula el cuadrado de su valor y lo suma de forma protegida
	int xi = (intptr_t)x;
	pthread_mutex_lock(&bloqueoCC);
	acumulado += xi * xi;
	pthread_mutex_unlock(&bloqueoCC);
	return NULL;
}

int main() {
	pthread_t WorkersTh[20];

	// Aquí se crean 20 hilos, cada uno con un valor distinto
	for (int i = 0; i < 20; i++)
		pthread_create(&WorkersTh[i], NULL, &cuadrados, (void *)(intptr_t)(i + 1));

	// Se espera la finalización de todos los hilos creados
	for (int i = 0; i < 20; i++) {
		void *acumulado;
		pthread_join(WorkersTh[i], &acumulado);
	}

	// Aquí se muestra el resultado final de la suma de cuadrados
	printf("Valor suma cuadrados = %d\n", acumulado);

	return 0;
}