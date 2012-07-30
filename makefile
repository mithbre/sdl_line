CC=gcc
CFLAGS= -lmingw32 -lSDLmain -lSDL

default:
	$(CC) -o line line.c $(CFLAGS)
