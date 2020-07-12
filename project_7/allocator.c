#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NUMBER_OF_PROCESSES 10

int main(int argc, char *args[])
{
    struct{
    int empty;
    int pos;
    int length;
    char name[5];
    } process[NUMBER_OF_PROCESSES];

    int i,j,s;
    int memory=atoi(args[1]);
    for(i=0;i<NUMBER_OF_PROCESSES;i++){
        process[i].empty=0;
        process[i].pos=0;
        process[i].length=0;
    }

    int cnt=1;
    int unuse[NUMBER_OF_PROCESSES+1][2];
    unuse[0][0]=0;
    unuse[0][1]=memory-1;

    int flag,st1,st2;
    char order[10];
    while(1){
        printf("allocator>");

        scanf("%s",order);

        if(!strcmp("RQ",order)){
            for(i=0;i<NUMBER_OF_PROCESSES;i++){
                if(!process[i].empty){
                    flag=i;
                    break;
                }
            }
            scanf("%s",process[flag].name);
            scanf("%d",&process[flag].length);

            scanf("%s",order);
            if(!strcmp(order,"F")){
                for(i=0;i<cnt;i++){
                    if(unuse[i][1]-unuse[i][0]+1>=process[flag].length && process[flag].empty==0){
                        process[flag].pos=unuse[i][0];
                        unuse[i][0]+=process[flag].length;
                        process[flag].empty=1;
                    
                        if(unuse[i][1]+1==unuse[i][0]){
                            for(j=i;j<NUMBER_OF_PROCESSES;j++){
                                unuse[j][0]=unuse[j+1][0];
                                unuse[j][1]=unuse[j+1][1];
                            }
                            cnt--;
                        }
                        break;
                    }
                }
            }

            if(!strcmp(order,"B")){
                st1=0;
                st2=memory;
                for(i=0;i<cnt;i++){
                    if(unuse[i][1]-unuse[i][0]+1>=process[flag].length){
                        if(unuse[i][1]-unuse[i][0]<=st2){
                            st1=i;
                            st2=unuse[i][1]-unuse[i][0];
                        }
                    }
                }

                process[flag].pos=unuse[st1][0];
                process[flag].empty=1;
                unuse[st1][0]+=process[flag].length;
                if(unuse[st1][1]+1==unuse[st1][0]){
                    for(j=st1;j<NUMBER_OF_PROCESSES;j++){
                        unuse[j][0]=unuse[j+1][0];
                        unuse[j][1]=unuse[j+1][1];
                    }
                    cnt--;
                }
            }

            if(!strcmp(order,"W")){
                st1=0;
                st2=unuse[0][1]-unuse[0][0];
                for(i=0;i<cnt;i++){
                    if(unuse[i][1]-unuse[i][0]+1>=process[flag].length){
                        if(unuse[i][1]-unuse[i][0]>=st2){
                            st1=i;
                            st2=unuse[i][1]-unuse[i][0];
                        }
                    }
                }

                process[flag].pos=unuse[st1][0];
                process[flag].empty=1;
                unuse[st1][0]+=process[flag].length;
                if(unuse[st1][1]+1==unuse[st1][0]){
                    for(j=st1;j<NUMBER_OF_PROCESSES;j++){
                        unuse[j][0]=unuse[j+1][0];
                        unuse[j][1]=unuse[j+1][1];
                    }
                    cnt--;
                }
            }
        }

        if(!strcmp(order,"RL")){
            scanf("%s",order);
            flag=1;
            for(i=0;i<NUMBER_OF_PROCESSES;i++){
                if(process[i].empty){
                    if(!strcmp(process[i].name,order)){
                        process[i].empty=0;
                        for(j=0;j<cnt-1;j++){
                            if(unuse[j][1]+1==process[i].pos && unuse[j+1][0]-1==process[i].pos+process[i].length){
                                unuse[j][1]=unuse[j+1][1];
                                for(s=j+1;s<NUMBER_OF_PROCESSES+1;s++){
                                    unuse[s][0]=unuse[s+1][0];
                                    unuse[s][1]=unuse[s+1][1];
                                }
                                cnt--;
                                flag=0;
                            }
                            if(unuse[j][1]+1==process[i].pos && unuse[j+1][0]-1!=process[i].pos+process[i].length){
                                unuse[j][1]+=process[i].length;
                                flag=0;
                            }
                            if(unuse[j][1]+1!=process[i].pos && unuse[j+1][0]-1==process[i].pos+process[i].length){
                                unuse[j+1][0]-=process[i].length;
                                flag=0;
                            }
                        }
                        if(flag){
                            if(unuse[0][0]>process[i].pos){
                                if(unuse[0][0]==process[i].pos+process[i].length){
                                    unuse[0][0]=process[i].pos;
                                }
                                else{
                                    for(j=cnt;j>0;j--){
                                        unuse[j][0]=unuse[j-1][0];
                                        unuse[j][1]=unuse[j-1][1];
                                    }
                                    unuse[0][0]=process[i].pos;
                                    unuse[0][1]=process[i].pos+process[i].length-1;
                                    cnt++;
                                }
                            }
                            else if(unuse[cnt][0]<process[i].pos){
                                    if(unuse[cnt][1]==process[i].pos-1){
                                        unuse[cnt][1]=process[i].pos+process[i].length-1;
                                    }
                                    else{
                                        unuse[cnt+1][0]=process[i].pos;
                                        unuse[cnt+1][1]=process[i].pos+process[i].length-1;
                                        cnt++;
                                    }
                                }
                            else if(unuse[0][0]<process[i].pos && process[i].pos<unuse[cnt][0]){
                                    for(j=0;j<cnt-1;j++){
                                        if(unuse[j][0]<process[i].pos && unuse[j+1][0]>process[i].pos){
                                            for(s=j+1;s<NUMBER_OF_PROCESSES;s++){
                                                unuse[s][0]=unuse[s+1][0];
                                                unuse[s][1]=unuse[s+1][1];
                                            }

                                        }   
                                    }
                                    cnt++;
                                }
                            }
                    }
                }
            }
        }

        if(!strcmp("C",order)){
            st1=0;
            for(i=0;i<NUMBER_OF_PROCESSES;i++){
                if(process[i].empty){
                    process[i].pos=st1;
                    st1+=process[i].length;
                }
            }
            unuse[0][0]=st1;
            unuse[0][1]=memory-1;
            cnt=1;
        }
        if(!strcmp("STAT",order)){
            for(i=0;i<NUMBER_OF_PROCESSES;i++){
                if(process[i].empty){
                    printf("Addresses [%d,%d] Process %s\n",process[i].pos,process[i].pos+process[i].length-1,process[i].name);
                }
            }
            for(i=0;i<cnt;i++)
                printf("Addresses [%d,%d] Unused\n",unuse[i][0],unuse[i][1]);
        }

        if(!strcmp(order,"X")){
            break;
        }
    }


    return 0;
}