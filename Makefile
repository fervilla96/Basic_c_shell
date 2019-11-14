all:
	gcc -o sh includes/sh.c && gcc -o getty includes/getty.c && gcc -o init includes/init.c
