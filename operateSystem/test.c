#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int num=0;
void getSig(int sig){
    printf("收到死亡信号\n");
}
void get(int s){
    printf("主进程收到信号:\n");
    num++;
}
int main(){
    pid_t p;
    if (p=fork()){
        signal(SIGINT,get);
        for(;;){
            if (num)
                break;
        }
        kill(getpid()+1,SIGUSR1);
    }
    else{
        signal(SIGUSR1,getSig);
        for(;;);
    }
}
