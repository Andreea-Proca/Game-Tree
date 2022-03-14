all: build

build: tema2.c
	gcc -o minimax tema2.c -g -Wall -lm -std=c11 -ggdb3

.PHONY: clean
clean: 
	rm -f minimax