#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
using namespace std;
int main(){
	pid_t p=fork();
	if (p==0)
        putchar('b');
    else if (p>0){
        pid_t p2=fork();
        if (p2==0)
            putchar('c');
        else if (p2>0)
            putchar('a');
        else
            printf("子进程2创建失败\n");
    }
    else
        printf("子进程1创建失败\n");
	return 0;
}
