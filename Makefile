CC=gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -O2

LIBS= -lm

SRCS= $(shell find . -name "*.c")
OBJS = $(notdir $(SRCS:.c=.o))

all: lazy_build
	$(CC) $(CFLAGS) $(OBJS) $(LIBS)

lazy_build: $(SRCS)
	$(CC) -c $(SRCS) $(CFLAGS)

clean:
	rm $(OBJS)

