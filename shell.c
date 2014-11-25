#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#define COLOR_BLUE	"\x1b[34m"
#define COLOR_RESET	"\x1b[0m" 

int main(int argc, char* argv[], char* envp[])
{

	printf(COLOR_BLUE"\n //----\\   ||       ||   ||  ||=====     //======  ||    ||  ||====  ||      ||\n");
	printf(" ||    ||  ||       ||   ||  ||          ||        ||    ||  ||      ||      ||\n");
	printf(" ||----    ||       ||   ||  ||=====     \\\\----\\\\  ||====||  ||====  ||      ||\n");
	printf(" ||    ||  ||       ||   ||  ||                ||  ||    ||  ||      ||      ||\n");
	printf(" ||____/   ||=====  \\\\---//  ||=====     ======//  ||    ||  ||====  ||====  ||====\n\n");
	printf(COLOR_RESET);
	bool isPiping = false, isRedirecting = false;
	char *pipeSearch, *redirectionSearch;
	int  pipingPosition[256], redirectionPosition[256];
	char c[256] = "\0";
	char* parameters[256];
	char *cptr;
	int parameterCount = 0;
	char piping = '|', redirection = '>';
    while(1)
	{
		int z;
 		char* path = "/bin/";
		char* envList[] = {"HOME=/root", "PATH=/bin:/sbin", NULL};
		//Loop that resets arrays to null
		for (z=0; z<=256; z++)
		{
			c[z] = '\0';
			parameters[z] = NULL;
		}
		
		//Display the prompt message
		parameterCount = 0;
		printf(COLOR_BLUE"[BLUE_SHELL  ]:- "COLOR_RESET);
		int l;
		 //Loop that reads in input
        	for (l = 0; l <= 256; l++)
		{		
			c[l] = getchar();
			if(c[l] == '\n')
			{
			 	c[l] = '\0';
				break;
			}
		}
        	//Store every word as an array of strings to parse later
		cptr = strtok(c, " ");
		while (cptr != NULL)
		{
			parameters[parameterCount] = cptr;
			parameterCount++;
			cptr = strtok(NULL, " ");	
	 	}
		int i, j = 0, k = 0;
		for (i = 0; i < parameterCount; i++)
		{
			pipeSearch = strchr(parameters[i],piping);
			if (pipeSearch!= NULL)
			{
				pipingPosition[j] = i;
				printf("| in position %d\n", pipingPosition[j]);
				isPiping = true;
				j++;
			}
			redirectionSearch = strchr(parameters[i],redirection);
			if (redirectionSearch!= NULL)
			{
				redirectionPosition[k] = i;
				printf("> in position %d\n", redirectionPosition[k]);
				isRedirecting = true;
				k++;
			}
		}
		//Exiting out of the shell		
		int ret;
		ret = strcmp(parameters[0],"exit");
		if(ret == 0)
		exit(0);

		//Fork
		int rc = fork();
		//if Fork fails
		if(rc < 0)
		{
			printf("Oops! Something went wrong!");
			exit(0);
		}

		//Child Code
		else if(rc == 0) 
		{
			//printf("Child Runs\n");
			//This will be the final path to the program that we will pass to execv
                        char prog[512];
                        //First we copy a /bin/ to prog
                        strcpy(prog, path);
                        //Then we concancate the program name to /bin/
                        //If the program name is ls, then it'll be /bin/ls
                        strcat(prog, parameters[0]);
			if (isPiping == true)
			{
				//Piping code
			}
			if (isRedirecting == true)
			{
				//Redirection code
			}
			//Then execute the damn progra
			int retc = execve(prog,parameters,envList);
			if (retc == -1)
			{
				strcpy(prog,"");
				strcat(prog,parameters[0]);
				retc = execve(prog,parameters,envList);
				if(retc == -1)
				printf("The process %s could not be recognized.\n",c);
				return 0;
			}
		
			return 0;
		}

		//Parent Code
		else if(rc > 0)	
		{
			wait(NULL);	
		}
		
	}
}