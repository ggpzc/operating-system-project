#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int* array;
int* res;

struct size_{
    int low;
    int high;
};




void sort(int a, int b)
{
    int i,j;
    for(i = a; i < b; i++)
    {
        for(j = a+1; j < b + a - i + 1;j++)
        {
            if(array[j] < array[j-1])
            {
                int tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
        }
    }
}
void* sortThread(void *arg)
{
    struct size_* s = (struct size_ *) arg;
    sort(s->low,s->high);

}




void* merge(void *arg)
{
    int idx1 = 0;
    int idx2 = 20;
    int cnt = 0;
    while(idx1 <= 19 || idx2 <= 39)
    {
        if(idx1 <= 19 && idx2 <= 39)
        {
            if(array[idx1] > array[idx2])
            {
                res[cnt++] = array[idx2++];          
            }
            else
            {
                res[cnt++] = array[idx1++];
            }
        }
        else
        {
            if(idx1 <= 19)
            {
                while(cnt <= 39)
                {
                    res[cnt++] = array[idx1++];
                }
            }
            else
            {
                while(cnt <= 39)
                {
                    res[cnt++] = array[idx2++];
                }
            }
        }
        
    }
}







int main()
{
    array = malloc(40* sizeof(int));
    res = malloc(40* sizeof(int));
    int s;
    for(s = 0; s < 40; s++)
    {
        array[s] = rand()%100;
        //printf("%d ", array[i]);
    }

    pthread_t sortingThreads[2];
    
    struct size_ sizes[2]; 
    sizes[0].low = 0;
    sizes[0].high = 19;
    sizes[1].low =20;
    sizes[1].high = 39; 
    int k;
    for (k=0; k<2; k++)
    {
        pthread_create(&sortingThreads[k], NULL, sortThread, (void *)&sizes[k]);

    }
    
    /*
    pthread_create(&sortingThreads[0], NULL, sortThread1, NULL);
    pthread_create(&sortingThreads[1], NULL, sortThread2, NULL);
    */
    int j;
    for (j = 0; j < 2; j++) 
        pthread_join(sortingThreads[j], NULL); 
    
      

    pthread_t mergingThread;
    pthread_create(&mergingThread, NULL, merge, NULL);
    pthread_join(mergingThread, NULL);
    int i;
    for (i=0; i<40; i++) printf("%d ", res[i]);
  	  printf("\n"); 


    return 0;
}
