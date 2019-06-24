#include<stdio.h>
#include<unistd.h>
int main(){
    pid_t p;
    p=fork();
    if (p==0){
        for (int i=0;i<3;i++)
            printf("我是子进程1，我的pid是%d\n",getpid());
    }
    else if (p>0){
        pid_t p2=fork();
        if (p2>0)
            for (int i=0;i<3;i++)
                printf("我是主进程，我的pid是%d\n",getpid());
        else if (p2==0)
            for (int i=0;i<3;i++)
                printf("我是子进程2，我的pid是%d\n",getpid());
        else
            printf("子进程2创建失败\n");

    }
    else
        printf("子进程1创建失败\n");
    return 0;
}
