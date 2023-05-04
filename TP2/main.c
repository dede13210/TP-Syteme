#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void processChain(int n){
    

    printf("Parent process id: %d\n", getpid());

    pid_t pid;

    for (int i = 0; i < n; i++) {
        pid = fork();

        if (pid == 0) {  // processus enfant
            printf("Child process %d id: %d\n", i+1, getpid());
        } else if (pid > 0) {  // processus parent
            wait(NULL);  // attent que le processus se termine
            break;
        } else {  // erreur fork 
            printf("Fork failed.\n");
        }
    }
}

void processTree(int n, int maxn){
    if(n==0){
    printf("Parent process id: %d\n", getpid());}
    pid_t pid1,pid2;
    if(n<maxn){
        pid1=fork();
        if(pid1==0){
            printf("Child process %d id: %d\n", n, getpid());
            pid2=fork();
            }
            else if(pid1>0){
                exit(pid1);
                }
                else{
                    printf("Fork failed.\n");
                    }
        if(pid2==0){
            printf("Child process %d id: %d\n", n, getpid());
            }
            else if(pid2>0){
                wait(NULL);
                wait(NULL);
        }else{
            printf("Fork failed.\n");
        }
        processTree(n+1,maxn);

    }
}

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);  // récupere l'argument n en int
    //processChain(n);
    processTree(0,n);
    sleep(20);
    return 0;
}
