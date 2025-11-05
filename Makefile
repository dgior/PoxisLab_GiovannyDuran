#####################################
#     Pontificia Universidad Javeriana
# Autor: Giovanny Andres Duran Renteria
# Fecha: 30-10-2025
# Script para automatizar compilacion de
# programas para Posix
# Laboratorio 03.
######################################

GCC = gcc
FLAGS = -lpthread
MODULO =

PROGRAMAS = labHilo01 labHilo02 labHilo03 labHilo04 labHilo05 labHilo06 labHilo07 labHilo08

labHilo01:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo02:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo03:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo04:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo05:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo06:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo07:
	$(GCC) $@.c -o $@ $(FLAGS)

labHilo08:
	$(GCC) $@.c -o $@ $(FLAGS)

clean: 
	$(RM) $(PROGRAMAS)
