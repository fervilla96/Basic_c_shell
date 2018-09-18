all:
	gcc -o sh sh.c && gcc -o getty getty.c && gcc -o init init.c;
