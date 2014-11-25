#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

    int main(int argc, char *argv[])
    {                                                                                     
       int rd[2];                                                                    
       pid_t cpid;                                                                       
       char buf;                                                                         
                                                                                         
       if (argc != 2) {                                                                  
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);                                
        exit(EXIT_FAILURE);                                                              
       }                                                                                 
                                                                                         
      if (pipe(rd) == -1) {                                                         
             perror("pipe");                                                               
          exit(EXIT_FAILURE);                                                           
       }                                                                                 
                                                                                         
       cpid = fork();                                                                    
       if (cpid == -1) {                                                                 
              perror("fork");                                                               
           exit(EXIT_FAILURE);                                                           
       }                                                                                 
                                                                                         
       if (cpid == 0) {    /* Child reads from pipe */                                   
           close(rd[1]);          /* Close unused write end */                       
                                                                                         
           while (read(rd[0], &buf, 1) > 0) {
               write(STDOUT_FILENO, &buf, 1); 
           }
           write(STDOUT_FILENO, "\n", 1);                                                
           close(rd[0]);                                                             
           _exit(EXIT_SUCCESS);    
       } else {            /* Parent writes argv[1] to pipe */                           
           close(rd[0]);          /* Close unused read end */                        
           write(rd[1], argv[1], strlen(argv[1]));                                   
           close(rd[1]);          /* Reader will see EOF */                          
           wait(NULL);                /* Wait for child */                               
           exit(EXIT_SUCCESS);                                                           
       }                                                                                 
    }       