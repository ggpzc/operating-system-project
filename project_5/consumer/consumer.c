#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include"buffer.h"
#define THREADS 10

void *producer(void *param)
{
    buffer_item item;

    while (1){
        item=rand()%3;
        sleep(item);

        if (insert_item(item))
            fprintf(stderr,"report error condition 1\n");
        else
        {
            printf("producer produced %d\n",item);
        }
        
            

    }
}

void *consumer(void *param)
{
    buffer_item item;

    while(1){
        sleep(rand()%3);


        if (remove_item(&item))
            fprintf(stderr,"report error condition 2\n");

        else
        {
            printf("consumer consumed %d\n",item);
        }
        
            

    }
}

int main(int argc,char *argv[])
{
    int time =atoi(argv[1]),pro_num=atoi(argv[2]),cus_num=atoi(argv[3]);
    pthread_t pro_arg[THREADS],cus_arg[THREADS];

    init();

    int i,j;
    for(i=0;i<pro_num;i++)
        pthread_create(&pro_arg[i],NULL,producer,NULL);
    for(j=0;j<cus_num;j++)
        pthread_create(&cus_arg[j],NULL,consumer,NULL);

    sleep(time);

    for(i=0;i<pro_num;i++){
        pthread_cancel(pro_arg[i]);
        pthread_join(pro_arg[i],NULL);
    }
    for(j=0;j<cus_num;j++){
        pthread_cancel(cus_arg[j]);
        pthread_join(cus_arg[j],NULL);
    }

    return 0;
}

