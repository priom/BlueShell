#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define COLOR_BLUE	"\x1b[34m"
#define COLOR_RESET	"\x1b[0m" 

int main(int argc, char* argv[], char* envp[])
{
	char c[256] = "\0";
	char* parameters[256];
	char *cptr;
	int parameterCount = 0;
	printf(COLOR_BLUE"\n //----\\   ||       ||   ||  ||=====     //======  ||    ||  ||====  ||      ||\n");
	printf(" ||    ||  ||       ||   ||  ||          ||        ||    ||  ||      ||      ||\n");
	printf(" ||----    ||       ||   ||  ||=====     \\\\----\\\\  ||====||  ||====  ||      ||\n");
	printf(" ||    ||  ||       ||   ||  ||                ||  ||    ||  ||      ||      ||\n");
	printf(" ||____/   ||=====  \\\\---//  ||=====     ======//  ||    ||  ||====  ||====  ||====\n\n");
	printf(COLOR_RESET);
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
		printf("[BLUE_SHELL  ]:- ");
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

		else if(rc == 0) //Code for child to run
		{
			//printf("Child Runs\n");
			//This will be the final path to the program that we will pass to execv
                        char prog[512];
                        //First we copy a /bin/ to prog
                        strcpy(prog, path);
                        //Then we concancate the program name to /bin/
                        //If the program name is ls, then it'll be /bin/ls
                        strcat(prog, parameters[0]);
			//Then execute the damn program
			int retc = execv(prog,parameters);
			if (retc == -1)
			{
				strcpy(prog,"");
				strcat(prog,parameters[0]);
				execve(prog,parameters,envList);
				return 0;
			}
			return(0);
		}
		else if(rc > 0)	//Parent waits for child to finish running then restars while loop
		{
			//printf("Parent starts waiting\n");
			wait(NULL);
			//printf("Parent is finished waiting\n");	
		}
		//printf("\n");
	}
}