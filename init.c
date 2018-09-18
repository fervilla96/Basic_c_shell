#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//Maximo numero de hijos
int numOfChild = 0;

int main (int argv, char * argvs[]) {
	
	int pid;
	char ppid[10];
	int status, i = 0;		
		
	//Siempre estar corriendo 	
	while (1) {
		
		//Hacer hijo e incrementa el numero de hijos
		pid = fork();
		numOfChild ++;
		//Obtengo el pid del padre para mandarlo
		sprintf(ppid, "%d", getppid());
		//Si es un proceso hijo, crea ventana con xterm		
		if (pid == 0) {						
			//Mando el pid del padre como argumento para usarlo en el shutdown
			execl("/usr/bin/xterm","/usr/bin/xterm", "-e","./getty", ppid, (void*)NULL);									
			
		}		 
		//Si es padre, espera
		else {			
			if (numOfChild >= 6) {
				wait(&status);				
				//Si se cierra, espera y luego disminuye el numero de hijos
				//Para volver a entrar y crear el hijo que acaba de ser cerrado
				sleep(1);
				numOfChild --;					
			}							
		}		
	}		
	        
    return(0);
}
