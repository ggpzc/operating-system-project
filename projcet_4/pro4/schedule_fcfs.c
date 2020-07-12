#include"schedulers.h"
#include<stdio.h>


void schedule(int *pri,int *bur,int count)
{
    int time =0;
    int turn_time=0,wait_time=0,res_time=0;
    int i;

    float num=count/1.0;
    for (i=0;i<count;i++){
        printf("run T%d for %d units\n",i+1,bur[i]);
        wait_time+=time;
        res_time+=time;
        time+=bur[i];
        turn_time+=time;
    
    }

    printf("the average turnaround time is %f\nthe average waiting time is %f\nthe average respose time is %f\n",turn_time/num,wait_time/num,res_time/num);
}
