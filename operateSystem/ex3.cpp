#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
int ctrl_cNum;
int status;
void ctrl_c(int sig){
	(void) signal(SIGINT,ctrl_c);
	++ctrl_cNum;
}
void getSig1(int sig){
    printf("\nchild process 1 is killed by parent\n");
}
void getSig2(int sig){
    printf("\nchild process 2 is killed by parent\n");
}
void getSigM(int){
}
int main(){
    signal(SIGINT,getSigM);
    pid_t p=fork();
    if (p>0){
        pid_t p2=fork();
        if (p2>0){
            printf("主进程等待信号:\n");
            sleep(50);
            kill(getpid()+1,SIGUSR1);
            kill(getpid()+2,SIGUSR2);
            wait(0);
            printf("\nparent process is killed\n");
        }
        else if (p2==0){
            printf("我是子进程2 %d.\n",getpid());
            signal(SIGUSR2,getSig2);
            sleep(10);
        }
    }
    else if(p==0){
        printf("我是子进程1 %d.\n",getpid());
        signal(SIGUSR1,getSig1);
        sleep(10);
    }
}
