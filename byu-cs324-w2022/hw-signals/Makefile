CC = gcc
CFLAGS = -g

all: signals killer

killer: killer.c
	$(CC) $(CFLAGS) -o killer killer.c

signals: signals.c
	$(CC) $(CFLAGS) -o signals signals.c

test:
	./signals ./killer 0
	./signals ./killer 1
	./signals ./killer 2
	./signals ./killer 3
	./signals ./killer 4
	./signals ./killer 5
	./signals ./killer 6
	./signals ./killer 7
	./signals ./killer 8
	./signals ./killer 9
