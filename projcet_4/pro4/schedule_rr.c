#include"schedulers.h"
#include<stdio.h>

void schedule(int *pri,int *bur,int count)
{
    int time=0,turn_time=0,wait_time=0,res_time=5*count*(count-1);
    float num=count/1.0;
    
    int done=0,i;

    int copy[count];
    for (i=0;i<count;i++)
        copy[i]=bur[i];
    while(done!=count)
    {
        for (i=0;i<count;i++)
        {
            if(0<bur[i] && bur[i]<=10)
            {
                printf("run T%d for %d units\n",i+1,bur[i]);
                done+=1;
                bur[i]=0;
                time+=bur[i];
                turn_time+=time;
            }
            if(bur[i]>10)
            {
                printf("run T%d for %d units\n",i+1,10);
                bur[i]-=10;
                time+=10;
            }
            
        }
    }
    wait_time=turn_time;
    for(i=0;i<count;i++)
        wait_time-=copy[i];
    printf("the average turnaround time is %f\nthe average waiting time is %f\nthe average respose time is %f\n",turn_time/num,wait_time/num,res_time/num);
}