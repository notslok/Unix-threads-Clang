#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* routine(){//sample routine for thread execution
    printf("Test from threads\n");
}

int main(int argc,char* argv[]){
    pthread_t t1; //a data-structure/variable to hold thread information
    pthread_t t2;

    if(pthread_create(&t1,NULL,&routine,NULL) != 0)//(reference to the thread data struct, attributes to be set for the threads, reference to the routine/function to be executed by that thread, attributes to be passed to the routine/function)
    {
        return 1;
    }
    if(pthread_create(&t2,NULL,&routine,NULL) != 0)
    {
        return 2;
    }

    //making process wait for the thread to finish execution
    if(pthread_join(t1,NULL) != 0)//2nd parameter is NULL bcz we are not expecting any return value from the "routine()" fn, that has to be caught 
    {
        return 3;
    }
    if(pthread_join(t2,NULL) != 0)
    {
        return 4;
    }
    return 0;
}