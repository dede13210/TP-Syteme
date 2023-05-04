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
        }else if(pid<0) {  // erreur fork 
            printf("Fork failed.\n");
        }
    }
    sleep(10);
}

void processTree(int n, int maxn){
    if(n==0){
        printf("Parent process id: %d\n", getpid());
        
    }
    pid_t pid1,pid2;
    if(n<maxn){
        pid1=fork();
        
        if(pid1==0){
            printf("Child process %d id: %d\n", n, getpid());
            processTree(n+1,maxn);
            
            }
        else if(pid1>0){
            pid2=fork();

        }else if(pid1<0) {  // erreur fork 
            printf("Fork failed.\n");
        }
        if(pid2==0){
            printf("Child process %d id: %d\n", n, getpid());
            processTree(n+1,maxn);
            
        }
            else if(pid2>0){//on attend le fils droit et le fils gauche
                wait(NULL);
                wait(NULL);
        }else if(pid2<0) {  // erreur fork 
            printf("Fork failed.\n");
        }

    }
    if(n == maxn-1){
        if(pid1==0){
            sleep(10);
        }
        if(pid2==0){
            sleep(10);
        }
        }
        
    
}

void createZombie(){
    pid_t pid;
    printf("parent process id: %d\n", getppid());
    pid=fork();
    if(pid==0){
        exit(0);
    }
    if(pid > 0){
        sleep(10);
        wait(NULL);
    }
    if(pid <0){
        printf("Fork failed.\n");
        
    }
}
int returnvalue(){
    pid_t pid;
    pid=fork();
    if(pid==0){
        int value = 42;
        exit(value);
    }
    if(pid > 0){
        wait(&pid);
        return(WEXITSTATUS(pid));
    }
    if(pid <0){
        printf("Fork failed.\n");
        
    }
}

int main(int argc, char *argv[]){
    //int n = atoi(argv[1]);  // récupere l'argument n en int
    //processChain(n);
    //processTree(0,n);
    //createZombie();
    int v = returnvalue();
    printf("%d\n",v);
    return 0;
}
