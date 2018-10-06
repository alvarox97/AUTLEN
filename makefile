obj_libs = palabra.o alfabeto.o estado.o
CC = gcc
CCFLAGS = -pedantic -Wall -g

# Makefile for testing libs with testlibs

prueba_estados: prueba_estados.o $(obj_libs)
	$(CC) $(CCFLAGS) $^ -o $@

prueba_estados.o: prueba_estados.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f *.o prueba_estados