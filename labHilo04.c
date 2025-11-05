/*#########################################
#    Pontificia Universidad Javeriana
# Autor: Giovanny Andres Duran Renteria
# Fecha: 30-10-2025
# Tema: Hilos en API POSIX
# Variables de Condición y Exclusión Mutua
# Sincronización de salidas de cada hilo
######################################### */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Variables globales */
int counter = 0;
pthread_t IDhilo[3];
pthread_mutex_t bloqueo;

void *cargaHilo() {
	unsigned long i = 0;

	// Aquí se protege el acceso al contador con el mutex
	pthread_mutex_lock(&bloqueo);
	counter += 1;
	int num = counter;
	printf("\n\t=> Carga %d ha iniciado <=\n", num);
	pthread_mutex_unlock(&bloqueo);

	// Aquí se simula un proceso de carga o trabajo
	for (i = 0; i < (0xFFFFFFFF); i++);

	// Se vuelve a usar el mutex para sincronizar las salidas
	pthread_mutex_lock(&bloqueo);
	printf("\n\t=> Carga %d ha finalizado <=\n", num);
	pthread_mutex_unlock(&bloqueo);

	return NULL;
}

int main() {
	int error;

	// Inicializa el mutex antes de crear los hilos
	pthread_mutex_init(&bloqueo, NULL);

	// Aquí se crean los tres hilos definidos en el arreglo
	for (int i = 0; i < 3; i++) {
		error = pthread_create(&(IDhilo[i]), NULL, &cargaHilo, NULL);
		if (error != 0)
			printf("\nHILO NO CREADO: [%d]\n", error);
	}

	// Aquí se espera la finalización de cada hilo
	for (int i = 0; i < 3; i++) {
		pthread_join(IDhilo[i], NULL);
	}

	// Se destruye el mutex para liberar los recursos
	pthread_mutex_destroy(&bloqueo);

	return 0;
}