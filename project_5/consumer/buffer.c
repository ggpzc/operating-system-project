#include"buffer.h"
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t lock;
sem_t empty,full;
int num;

void init()
{
    pthread_mutex_init(&lock,NULL);
    sem_init(&empty,0,0);
    sem_init(&full,0,BUFFER_SIZE);
    num=0;
}

int insert_item(buffer_item item)
{
    sem_wait(&empty);
    pthread_mutex_lock(&lock);

    int flag=0;
    if (num==BUFFER_SIZE)
        flag=-1;
    else
    {
        buffer[num]=item;
        num++;
    }
    
    pthread_mutex_unlock(&lock);
    sem_post(&full);
    return flag;
}


int remove_item(buffer_item *item)
{
    sem_wait(&full);
    pthread_mutex_lock(&lock);

    int flag=0;
    if(num==0)
        flag=-1;
    else
    {
        (*item)=buffer[num-1];
        num--;
    }
    
    pthread_mutex_unlock(&lock);
    sem_post(&empty);
    return flag;
}