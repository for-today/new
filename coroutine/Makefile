.PHONY: clean main

CC=gcc
OBJS=coroutine.o  main.o
TARGET=svr cli

all : $(TARGET)

svr : $(OBJS)
	$(CC) $^ -o $@

cli:
	gcc client.c -o cli

clean :
	rm -rf $(OBJS) main
