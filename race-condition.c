#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int mails=0;

void* routine(){
    for(int i=0;i<100;i++){//increase the loop limit here to obsever the race condition
        mails++;//race cond. happens here bcz at assembly level there are multiple steps involved in this process...execute with "gcc -s" to see
        //Following things happen behind the scenes:
        //read mail val
        //increment mail val
        //write mail count val
    }
}
int main(int argc, char* argv[]){
    pthread_t t1,t2;
    if(pthread_create(&t1,NULL,&routine,NULL)!=0){
        return 1;
    }
    if(pthread_create(&t2,NULL,&routine,NULL)!=0){
        return 2;
    }

    if(pthread_join(t1,NULL)!=0){
        return 3;
    }

    if(pthread_join(t2,NULL)!=0){
        return 4;
    }

    
    printf("You have received %d mails\n",mails);
    
    return 0;
}