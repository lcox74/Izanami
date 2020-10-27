CC=gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -O2

SRCS=activations.c neuron.c layer.c
OBJS=activations.o neuron.o layer.o

all: $(OBJS)

activations.o: activations.c activations.h
	$(CC) $(CFLAGS) -c activations.c

neuron.o: neuron.c neuron.h activations.h
	$(CC) $(CFLAGS) -c neuron.c

layer.o: layer.c layer.h neuron.h
	$(CC) $(CFLAGS) -c layer.c





