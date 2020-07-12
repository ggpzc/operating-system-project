/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

void show_his(char **args,int count)
{ 
	int i;
        for (i=0;i<count;i++)
		printf("%d:%s\n",i,args[i]);

}

int file_read(char **args,int count,char *file)
{
	FILE* fd;
	char *com;
	com = (char*)malloc(sizeof(char)*MAX_LINE);
	fd=fopen(file,"r");
	while (fscanf(fd, "%s", com) != EOF){

 
	args[count-1]=com;
	com = (char*)malloc(sizeof(char)*MAX_LINE);

        count++;
	}

	args[count-1]=NULL;
	
	fclose(fd);
	return count;
}

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    	char *history[MAX_LINE/2 + 1];		/* only recent 1000 cammands will be stored */
	int should_run = 1;
	int count;			/* the number of the commands */
	int his_count=0;			/* the number of the history */
	
    	while (should_run){
		args[0]=NULL;
		count = 1;   
        	printf("osh>");
        	fflush(stdout);

		int mode=1;		/* flags to see what should be done */
		int concur=1;
		int pipe=0;
		int ifwrite=0;
		char *file_name=NULL;		
		char end;
			
		do{
			char *command;
        	        command = (char*)malloc(sizeof(char)*MAX_LINE);         /* get commands */
		
			scanf("%s",command);
			
			if (strcmp(command,"&")==0){
				concur=0;
				continue;
			}
			if (strcmp(command,"exit")==0){
				mode=0;
				should_run=0;
			}
			if (strcmp(command,"!!")==0)
				mode=2;

			if (strcmp(command,">")==0){
				ifwrite=1;
				file_name = (char*)malloc(sizeof(char)*MAX_LINE);
				scanf("%s",file_name);
				args[count-1]=NULL;
				break;
			}

			if (strcmp(command,"<")==0){
				file_name = (char*)malloc(sizeof(char)*MAX_LINE);
				scanf("%s",file_name);
				count=file_read(args,count,file_name);
				
				break;
			}
			if (strcmp(command,"|")==0){
				file_name = (char*)malloc(sizeof(char)*MAX_LINE);
				file_name = "pipe.txt";
				pipe=count;
				ifwrite=0;
				args[count-1]=NULL;
				count++;
				break;
			}

			args[count-1]=command;	
			count+=1;
			end=getchar();
			if (end=='\n' || end==EOF){
				args[count-1]=NULL;					
				break;
			}
		}while(1);

		fflush(stdin);	
	
				
		if (count>=MAX_LINE/2)
			should_run = 0;
		
		if (should_run==0)
			break;


		if (mode){
			pid_t pid;
			pid=fork();
			
			if (mode==1){
				int j;
                                for (j=0;j<count;j++)
 	                               history[j]=args[j];
				his_count=count;

			}

			if (pid==0){
				if (mode==1){

					if (ifwrite){		/* check whether write in a file */
						int oldfd,fd;
                        			oldfd=open(file_name,O_CREAT | O_APPEND | O_RDWR);
						fd=dup2(oldfd,STDOUT_FILENO);
                        			execvp(args[0],args);
						close(fd); 
						
						if (pipe>0){
							
							args[0]=args[pipe];
							count=file_read(args,2,"pipe.txt");
							int i;
							for (i=0;i<count-1;i++)
								printf("%s\n",args[i]);
							execvp(args[0],args);
						}
						
						should_run=0;            
					}
					else{
						execvp(args[0],args);
						should_run=0;
					}

					
				}

				if (mode==2){
					if (his_count==0)
						printf("No commands in history\n");
					else
						execvp(history[0],history);
					should_run=0;
				}
			}
			if (concur)
				wait(NULL);
		}


	

        	/**
         	 * After reading user input, the steps are:
         	 * (1) fork a child process
         	 * (2) the child process will invoke execvp()
         	 * (3) if command includes &, parent and child will run concurrently
         	 */
    	}
    
	return 0;
}
