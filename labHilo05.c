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

/* Variables globales */
int acumulado = 0;

void *cuadrados(void *x) {
	// Aquí cada hilo toma el valor recibido y calcula su cuadrado
	int xi = (intptr_t)x;
	acumulado += xi * xi;
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

/*
 * Nota:
 * Este código no manda el mismo resultado en cada ejecucion,
 * ya que varios hilos acceden y modifican la variable global "acumulado"
 * al mismo tiempo sin protección mediante un mutex.
 * Esto genera una condición de carrera, por lo que el resultado correcto
 * se obtiene solo una parte de las veces (aproximadamente entre 96% y 99%).
 */
