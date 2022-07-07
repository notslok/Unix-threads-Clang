#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int mail = 0;
pthread_mutex_t lock;//defining the mutex lock

//----traditional way - but not working
// int lock=0;
// void* routine(){
//     for(int i=0;i<100000;i++){
//         if(lock == 1){
//             while(lock==1){}
//         }
//         lock=1;
//         mail++;
//         lock=0;
//     }
// }

void* routine(){
    for(int i=0;i<100000;i++){
        pthread_mutex_lock(&lock);//locking the section for corresponding thread(s)
        
        mail++;
        
        pthread_mutex_unlock(&lock);//unlocking the section for corresponding thread(s)
    }
}

int main(int argc, char* argv[]){
    pthread_t t1,t2;
    
    //initializing the mutex lock
    if(pthread_mutex_init(&lock,NULL)!=0){
        printf("failed to create the mutex lock!\n");
    }
    
        if(pthread_create(&t1,NULL,&routine,NULL) != 0){
            return 1;
        }
        if(pthread_create(&t2,NULL,&routine,NULL) != 0){
            return 2;
        }

        if(pthread_join(t1,NULL) != 0){
            return 3;
        }
        if(pthread_join(t2,NULL) != 0){
            return 4;
        }
    //destroyint the mutex lock   
    pthread_mutex_destroy(&lock);

    printf("Number of mails received is: %d\n",mail);

    return 0;
}