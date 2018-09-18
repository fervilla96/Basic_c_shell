#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

#define space " "
#define stringSize 50

const char * getVariable (char string[] ) {
	char variable[strlen(string)];
	char *var;
	for (int i = 1; i < strlen(string); i ++) {
		variable[i - 1] = string[i];
	}
	var = variable;
	//printf("%s",var); 
	//printf("%s",variable); 
	return var;
}

int main (int argv, char* argvs[]) {
	char string[stringSize];
	char variable[stringSize]; 	
	char argumentos[stringSize];
	char comando[stringSize];		
	int i, pid;
	char *token;
	const char *rest;
	
	putenv("PATH=/bin");
	
	while (1) {
	
		//Imprimir el sh del shell
		printf("sh > ");	
		//Obtener la cadena ingresada por el usuario 	
		fgets(string,stringSize,stdin);	
		//fgets guarda la cadena con un salto de linea
		//Por lo que le borro ese salto de linea
		string[strlen(string) - 1]  = '\0';
				
		//Obtenemos el comando introducido por el usuario								
		token = strtok(string, space);				
		
		if(strncmp("echo",string,strlen(string)) == 0) {						

			//Mientras existan tokens por procesar, seguira iterando				
			while (token != NULL)  {
				
				//Obtengo la parte siguiente que toca de argumentos
				token = strtok(NULL, space);			
				if (token != NULL) {
					//Copio ese pedaso del token al string
					strncpy(argumentos, token, stringSize);												
					//Checo si el primer caracter es un $ para saber si es
					//una variable o no
					if (argumentos[0] == '$') {								
						//Si es, uso la funcion para quitar el signo de $
						rest = getVariable(argumentos);												
						printf("%s = %s\n",token,getenv(rest));				
					} else {				
						//Si no es, imprimo el token
						printf("%s\n",token);				
					}			
				}
			}
			//token = strtok(NULL, "$");			
			//printf("%s\n",getenv(token));		
							
		} else if(strncmp("exit",string,strlen(string)) == 0) {								
			//Para salir, inicio el programa getty 
			execl("./getty","getty", NULL);	
						
		} else if(strncmp("shutdown",string,strlen(string)) == 0) {
			//Mato todos los procesos con el pid del padre que fui pasando
			//A traves de los argvs de los programas, al multiplicarlo por 
			// -1 me aseguro de matar a todo su grupo de hijos		    
		    kill((atoi(argvs[1]) * (-1) ), SIGTERM);
		    			
		} else if (strncmp("export",string,strlen(string)) == 0) {									
			//Parto lo ultimo del string para conseguir lo que guardare
			token = strtok(NULL,space);			
			strncpy(variable, token, stringSize);						
			//Lo guardo con putenv
			putenv(variable);
								
		} else {
			strncpy(argumentos, token, stringSize);			
			if (argumentos[0] == '.' || argumentos[0] == '/') {
				pid = fork();
				if (pid == 0) {
					execl(argumentos,argumentos, NULL);
				}													
			} else {
				//Obtengo el PATH actual
				rest = getenv("PATH");
				//Concateno el path con el comando introducido
				strncpy(comando, rest, stringSize);				
				strcat(comando,"/");
				strcat(comando,argumentos);				
				//Creo proceso hijo para ejecutar el comando 
				pid = fork();
				if (pid == 0) {
					execl(comando,comando, NULL);
				}				
				
			}
			
		}
	}        
	        
    return(0);
}
