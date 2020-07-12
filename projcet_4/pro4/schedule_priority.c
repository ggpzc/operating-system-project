#include"schedulers.h"
#include<stdio.h>


void schedule(int *pri,int *bur,int count)
{
    int time=0,turn_time=0,wait_time=0,res_time=0;
    float num=count/1.0;
   
    int i,j;
    int order[count];
    int max,max_num;
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

    for (i=0;i<count;i++){
        printf("run T%d for %d units\n",order[i]+1,bur[order[i]]);
        wait_time+=time;
        res_time+=time;
        time+=bur[order[i]];
        turn_time+=time;
    }

    printf("the average turnaround time is %f\nthe average waiting time is %f\nthe average respose time is %f\n",turn_time/num,wait_time/num,res_time/num);

}
