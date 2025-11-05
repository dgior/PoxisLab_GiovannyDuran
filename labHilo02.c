/*
* ============================================================================
*       Pontificia Universidad Javeriana
* Autor: Giovanny Andres Duran Renteria
* Materia: Sistemas Operativos
* Fecha: 04/11/2025
* Descripción:
*    Este programa demuestra la creación de múltiples hilos en C
*    utilizando la biblioteca pthread, junto con la sincronización
*    mediante un mutex. Cada hilo incrementa un contador global,
*    asegurando el acceso controlado para evitar condiciones de carrera.
*
* Flujo:
*    - Se define un número total de hilos (NTHREADS).
*    - Cada hilo imprime su número y su identificador (ID).
*    - Se protege el acceso al contador global con un mutex.
*    - Una vez que todos los hilos terminan, el programa principal
*      muestra el valor final del contador.
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Número total de hilos a crear
#define NTHREADS 10

// Declaración del mutex y del contador global compartido
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

/*
 * Aquí se define la función que ejecutará cada hilo.
 * Recibe como argumento un número entero que identifica el hilo.
 * Dentro de la función:
 *    - Se imprime el número del hilo y su ID.
 *    - Se bloquea el mutex antes de modificar el contador.
 *    - Se incrementa el valor compartido "counter".
 *    - Finalmente, se libera el mutex.
 */
void *thread_function(void *arg) {
    int i = *(int *)arg;
    printf("Thread number: %d | Thread ID: %ld\n", i, pthread_self());

    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

/*
 * Aquí se encuentra el proceso principal del programa.
 * Se encarga de crear todos los hilos, esperar su finalización
 * y finalmente mostrar el valor total del contador.
 */
int main(void) {

    // Declaración del arreglo de identificadores de hilos
    pthread_t thread_id[NTHREADS];

    // Arreglo auxiliar para pasar los índices de los hilos
    int args[NTHREADS];

    // Aquí se crean los hilos en un ciclo for
    for (int i = 0; i < NTHREADS; i++) {
        args[i] = i + 1;
        pthread_create(&thread_id[i], NULL, thread_function, &args[i]);
    }

    // Aquí el programa principal espera a que todos los hilos terminen
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Una vez que todos los hilos han finalizado, se imprime el resultado final
    printf("Final counter value: %d\n", counter);

    return 0;
}
