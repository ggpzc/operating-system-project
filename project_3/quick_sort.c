#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_LINE 100
int num[MAX_LINE];

void *quicksort(void *left_right);

int main(void)
{	
	int count=0,i;
	char input;
	while(1){
		input=getchar();
		if (input=='\n')
			break;
		num[count]=input-'0';
		count++;
	}
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int left_right[2] = {0, count};
    pthread_create(&tid, &attr, quicksort, left_right);
    pthread_join(tid, NULL);

    for (i = 0; i < count - 1; ++i)
        printf("%d ", num[i]);
    printf("%d\n", num[count - 1]);

    return 0;
}

void *quicksort(void *left_right)
{
    int left = ((int *)left_right)[0], right = ((int *)left_right)[1];
    if (left + 1 >= right)
        return NULL;
    if (left + 2 == right) {
        if (num[left] > num[left + 1]) {
            int temp = num[left];
            num[left] = num[left + 1];
            num[left + 1] = temp;
        }
        return NULL;
    }

    int size = right - left, p = left + random() % size;
    int temp = num[p], pivot = temp;
    num[p] = num[right - 1];
    int j;
    for (p = j = left; j < right - 1; ++j)
        if (num[j] < pivot) {
            temp = num[j];
            num[j] = num[p];
            num[p++] = temp;
        }
    num[right - 1] = num[p];
    num[p] = pivot;

    pthread_t tid[2];
    pthread_attr_t attr[2];
    int params[4] = {left, p, p + 1, right};
    pthread_attr_init(attr);
    pthread_create(tid, attr, quicksort, params);
    pthread_attr_init(attr);
    pthread_create(tid + 1, attr + 1, quicksort, params + 2);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return NULL;
}
