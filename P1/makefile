# Óscar Pinto y Luis Cárabe. Pareja 2, grupo 1401

obj_libs = palabra.o alfabeto.o estado.o afnd.o
CC = gcc
CCFLAGS = -pedantic -Wall -g

all: prueba_afnd

prueba_afnd: prueba_afnd.o $(obj_libs)
	$(CC) $(CCFLAGS) $^ -o $@

prueba_afnd.o: prueba_afnd.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f *.o  prueba_afnd
