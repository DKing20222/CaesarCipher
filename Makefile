CC=gcc
CFLAGS= -std=c11 -Wall -Wextra -pedantic
APP_FILES=caesar.c
KEY=1
SIDE=1

run:
	$(CC) $(CFLAGS) $(APP_FILES) -o caesar
	./caesar $(SIDE) $(KEY)