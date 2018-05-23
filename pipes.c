// P/1726/2016
// AGIN ELVIS
// ASSIGNMENT 1 April 22, 2018
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
 
int main()
{
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child
 
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    int pid; //process ID assignment 
    int count = 10; //limit number of child processes to 10
   
 
    char fixed_str[] = " ,you are just the guy.";
    char input_str[100];
    pid_t p;
 
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe declaration failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe declaration failed" );
        return 1;
    }
 
    scanf("%s", input_str);
    p = fork(); //create a child process

    if (p < 0)
    {
        fprintf(stderr, "Process failed to fork." );
        return 1;
    }
 
    // Parent process
        else if (p > 0)
    {


        char concat_str[100];
     
            close(fd1[0]);  // Close reading end of first pipe
     
            // Write input string and close writing end of first
            // pipe.
            write(fd1[1], input_str, strlen(input_str)+1);
            close(fd1[1]);
     
            // Wait for child to send a string
            wait(NULL);
     
            close(fd2[1]); // Close writing end of second pipe
     
            
            // Read string from child, print it and close
            // reading end.
            read(fd2[0], concat_str, 100);
            printf("String combination is: %s\n", concat_str);
            close(fd2[0]);
    }
        


    // child process
    else
    {

        for (int pid = 0; pid < count; ++pid)
        {
            
            // p = fork(); //create a child process
            printf("Parent process ID: %i\n ", getppid());
            printf("Child Process ID: %i\n ", getpid());

            int selection;
            char name [100]; 

            printf("Enter your first name\n");
            scanf(" %s",name);
            printf("Choose a string to append to your text.\n \t 1. Happy Birthday\n \t 2. Happy Madaraka\n \t 3. Happy Jamhuri \n \t 4. Happy Sunday \n \t 5. Happy Halloween\n");
            scanf ("%i", &selection);
            if (selection < 1)
            {
                printf("Incorrect selection\n");
            }
            else if (selection == 1)
            {
                printf("Happy Birthday %s\n",name);
            }
            else if (selection == 2)
            {
                printf("Happy Madaraka %s\n",name);
            }
            else if (selection == 3)
            {
                printf("Happy Jamhuri %s\n",name);
            }
            else if (selection == 4)
            {
                printf("Happy Sunday %s\n",name);
            }
            else if (selection == 5)
            {
                printf("Happy Halloween %s\n",name);
            }
            else
            {
                printf("Wrong Selection\n" );
                return 0;
            }
           
            
        
        }




        close(fd1[1]);  // Close writing end of first pipe
 
        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);
 
        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
        for (i=0; i<strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];
 
        concat_str[k] = '\0';   // string ends with '\0'
 
        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);
 
        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str)+1);
        close(fd2[1]);
 
        exit(0);

        
    }
    
}