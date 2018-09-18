#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main (int argv, char* argvs[]) {
	
	//printf("%s",argvs[1]);
	
	FILE *fp;	
	char inputUser[20], inputPas[20],pasw[40],filePas[40];
	int length, pid, flag = 0, status;
	
	while (flag == 0) {
	
		//Pedir usuario y contraseña
		printf("User:");
		scanf("%s",inputUser);
	
		printf("Password:");
		scanf("%s",inputPas);			
		
		//Juntar contraseña con el usuario	
		strcat(pasw,inputUser);
		strcat(pasw,":");
		strcat(pasw,inputPas);
		//Conocer tamaño de los datos introducidos por el usuario
		length = strlen(pasw);
		fflush(stdout);
								
		//Abrir el archivo en busca de opciones	
		fp = fopen("passwd.txt" , "r");
	       
	   	while(fgets (filePas, 40, fp) != NULL) {      	   		   		   		
	   		//Comparar cadenas	   		   		   		   		
	   		if(strncmp(filePas,pasw,length) == 0) {
	   			//Cierro el archivo
	   			fclose(fp);	
	   			//Creo proceso hijo para que corra el shell 		
				pid = fork();
				if (pid == 0) {
					//Ejecuto el programa del shell y mando de igual manera
					//El pid del padre
					execlp("./sh", "sh",argvs[1], NULL);
					
				} else {
					wait(&status);					
					
					//execlp("./sh", "sh", NULL);
				}	   			   			
	   		}   			   			   			   	
	   	}		
		//Usuario no encontrado
		printf("Error, usuario y/o contraseña no valido\n");	     
    }
        
    return(0);
}
