/*#########################################
#    Pontificia Universidad Javeriana
# Autor: Giovanny Andres Duran Renteria
# Fecha: 30-10-2025
# Tema: Hilos en API POSIX
# Variables de Condición y Exclusión Mutua
######################################### */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Declaración de los mutex y la variable de condición */
pthread_mutex_t contador_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_Cond = PTHREAD_COND_INITIALIZER;

/* Variables globales */
int counter = 0;
#define FIN_CONTADOR 15
#define ALTO_CONTADOR_01 4
#define ALTO_CONTADOR_02 11

void *contador01() {
	for (;;) {
		// Aquí se bloquea el acceso mientras el contador está en el rango restringido
		pthread_mutex_lock(&condition_Mutex);
		while (counter >= ALTO_CONTADOR_01 && counter <= ALTO_CONTADOR_02)
			pthread_cond_wait(&condition_Cond, &condition_Mutex);
		pthread_mutex_unlock(&condition_Mutex);

		// Aquí se incrementa el contador de forma protegida
		pthread_mutex_lock(&contador_Mutex);
		counter++;
		printf("Valor de contador en función ==01==: %d\n", counter);
		pthread_mutex_unlock(&contador_Mutex);

		// Aquí se notifica a la otra función que puede continuar
		pthread_mutex_lock(&condition_Mutex);
		pthread_cond_signal(&condition_Cond);
		pthread_mutex_unlock(&condition_Mutex);

		// Aquí se detiene el hilo cuando el contador llega al valor final
		if (counter >= FIN_CONTADOR)
			return NULL;
	}
}

void *contador02() {
	for (;;) {
		// Aquí el hilo espera hasta que el contador esté dentro del rango permitido
		pthread_mutex_lock(&condition_Mutex);
		while (counter < ALTO_CONTADOR_01 || counter > ALTO_CONTADOR_02)
			pthread_cond_wait(&condition_Cond, &condition_Mutex);
		pthread_mutex_unlock(&condition_Mutex);

		// Se incrementa el contador protegido por el mutex
		pthread_mutex_lock(&contador_Mutex);
		counter++;
		printf("Valor de contador en función ==02==: %d\n", counter);
		pthread_mutex_unlock(&contador_Mutex);

		// Se envía una señal para reactivar el otro hilo
		pthread_mutex_lock(&condition_Mutex);
		pthread_cond_signal(&condition_Cond);
		pthread_mutex_unlock(&condition_Mutex);

		// El hilo finaliza cuando se alcanza el valor máximo
		if (counter >= FIN_CONTADOR)
			return NULL;
	}
}

int main() {
	// Declaración de los dos hilos del tipo pthread_t
	pthread_t hilos01, hilos02;

	// Creación de los hilos
	pthread_create(&hilos01, NULL, &contador01, NULL);
	pthread_create(&hilos02, NULL, &contador02, NULL);

	// Esperar a que cada hilo finalice su ejecución
	pthread_join(hilos01, NULL);
	pthread_join(hilos02, NULL);

	return 0;
}


