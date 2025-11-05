/*
* ============================================================================
*       Pontificia Universidad Javeriana
* Autor: Giovanny Andres Duran Renteria
* Materia: Sistemas Operativos
* Fecha: 04/11/2025
* Descripción:
*    Este programa demuestra la creación básica de hilos en C utilizando
*    la biblioteca pthread. Cada hilo ejecuta una función que imprime
*    un mensaje distinto recibido como argumento.
*
* Flujo:
*    - Se definen dos mensajes para los hilos.
*    - Se crean dos hilos independientes con pthread_create().
*    - Cada hilo imprime su mensaje mediante la función print_function().
*    - El programa principal espera la finalización de ambos hilos.
*    - Finalmente, se muestran los códigos de retorno de la creación.
* ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* 
 * Aquí se define la función que ejecutará cada hilo.
 * Recibe un puntero genérico como argumento, el cual se
 * convierte a tipo char* para mostrar el mensaje correspondiente.
 */
void *print_function(void *ptr) {
    char *mensaje = (char *) ptr;
    printf("Mensaje desde función: %s\n", mensaje);
    return NULL;
}

/*
 * Aquí se encuentra el proceso principal del programa.
 * Se crean dos hilos, cada uno con un mensaje diferente,
 * y luego se espera a que ambos terminen su ejecución.
 */
int main(int argc, char *argv[]) {

    // Declaración de los identificadores de los hilos
    pthread_t hilo1, hilo2;

    // Definición de los mensajes que se enviarán a cada hilo
    char *mensaje1 = "Soy el hilo 1 :)!!!";
    char *mensaje2 = "Soy el hilo 2 :)!!!";

    // Variables que almacenan los códigos de retorno de creación
    int men01, men02;

    // Aquí se crean los dos hilos mediante pthread_create()
    men01 = pthread_create(&hilo1, NULL, print_function, (void *) mensaje1);
    men02 = pthread_create(&hilo2, NULL, print_function, (void *) mensaje2);

    // Aquí el proceso principal espera la finalización de ambos hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Finalmente, se muestran los códigos de retorno de creación de cada hilo
    printf("Hilo 1: %d\n", men01);
    printf("Hilo 2: %d\n", men02);

    return 0;
}

