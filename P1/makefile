obj_libs = palabra.o alfabeto.o estado.o afnd.o
CC = gcc
CCFLAGS = -pedantic -Wall -g

# Makefile for testing libs with testlibs

all: prueba_estados prueba_alfabeto prueba_palabra prueba_afnd

prueba_afnd: prueba_afnd.o $(obj_libs)
	$(CC) $(CCFLAGS) $^ -o $@

prueba_afnd.o: prueba_afnd.c
	$(CC) $(CCFLAGS) -c $< -o $@

prueba_estados: prueba_estados.o estado.o
	$(CC) $(CCFLAGS) $^ -o $@

prueba_estados.o: prueba_estados.c
	$(CC) $(CCFLAGS) -c $< -o $@

prueba_alfabeto: prueba_alfabeto.o alfabeto.o palabra.o
	$(CC) $(CCFLAGS) $^ -o $@

prueba_alfabeto.o: prueba_alfabeto.c
	$(CC) $(CCFLAGS) -c $< -o $@

prueba_palabra: prueba_palabra.o palabra.o
	$(CC) $(CCFLAGS) $^ -o $@

prueba_palabra.o: prueba_palabra.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f *.o prueba_estados prueba_alfabeto prueba_palabra prueba_afnd
