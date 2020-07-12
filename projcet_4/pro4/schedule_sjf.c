#include"schedulers.h"
#include<stdio.h>


void schedule(int *pri,int *bur,int count)
{
    int time=0,turn_time=0,wait_time=0,res_time=10*(count-1);
    float num=count/1.0;

    int i,j;
    int order[count];
    int min,min_num;

    int copy[count];
    for (i=0;i<count;i++)
        copy[i]=bur[i];

    for (i=0;i<count;i++){
        min=bur[0];
        min_num=0;
        for(j=0;j<count;j++){
            if (min>bur[j]){
                min=bur[j];
                min_num=j;
            }
        }
        order[i]=min_num;
        bur[min_num]=1000;
    }

    for (i=0;i<count;i++){
        printf("run T%d for %d units\n",order[i]+1,copy[order[i]]);
        wait_time+=time;
        res_time+=time;
        time+=copy[order[i]];
        turn_time+=time;
    }

    printf("the average turnaround time is %f\nthe average waiting time is %f\nthe average respose time is %f\n",turn_time/num,wait_time/num,res_time/num);

}
