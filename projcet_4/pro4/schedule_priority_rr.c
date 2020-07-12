#include"schedulers.h"
#include<stdio.h>


void schedule(int *pri,int *bur,int count)
{
    int time=0,turn_time=0,wait_time=0,res_time=5*count*(count-1);
    float num=count/1.0;

    int i,j;
    int order[count];
    int max,max_num;

    int copy[count];
    for (i=0;i<count;i++)
        copy[i]=bur[i];
    for (i=0;i<count;i++){
        max=pri[0];
        max_num=0;
        for(j=0;j<count;j++){
            if (max<pri[j]){
                max=pri[j];
                max_num=j;
            }
        }
        order[i]=max_num;
        pri[max_num]=0;
    }

    int done=0;
    while(done!=count)
    {
        for (i=0;i<count;i++)
        {
            if(0<bur[order[i]] && bur[order[i]]<=10)
            {
                time+=bur[order[i]];
                printf("run T%d for %d units\n",order[i]+1,bur[order[i]]);
                done+=1;
                bur[order[i]]=0;
                turn_time+=time;
            }
            if(bur[order[i]]>10)
            {
                printf("run T%d for %d units\n",order[i]+1,10);
                bur[order[i]]-=10;
                time+=10;
            }
            
        }
    }
    wait_time=turn_time;
    for(i=0;i<count;i++)
        wait_time-=copy[i];

    printf("the average turnaround time is %f\nthe average waiting time is %f\nthe average respose time is %f\n",turn_time/num,wait_time/num,res_time/num);
}