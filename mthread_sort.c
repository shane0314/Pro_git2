/*
#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>


#define NTHR    8
#define NUMNUM  80
#define TNUM    (NUMNUM/NTHR)

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

#define heapsort    qsort

//比较函数
int complong(const void *arg1, const void *arg2)
{
    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;
    
    if (l1 == l2)
        return 0;
	else if (l1 < l2)
		return -1;
	else
		return 1;   
}

//分段排序
void * thr_fn(void *arg)
{
	long idx = (long)arg; //ATTENTION
	
	heapsort(&nums[idx], TNUM, sizeof(long), complong);

	pthread_barrier_wait(&b);
	
	return ((void *)0);
}

//合并
void merge()
{
	long idx[NTHR];
	long i, minidx, sidx, num;
	
	for (i = 0; i < NTHR; i++)
		idx[i] = i * TNUM;
	
	for (sidx = 0; sidx < NUMNUM; sidx++)
	{
		num = LONG_MAX;
		for (i=0; i < NTHR; i++)
		{
			if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num))
			{
				num = nums[idx[i]];
				minidx = i;
			}
		}
		snums[sidx] = nums[idx[minidx]];
		idx[minidx]++;
	}
}

int main()
{
	unsigned long i;
	int err;
	pthread_t tid;
	
	srandom(1);
	for (i=0; i<NUMNUM; i++)
	{
		nums[i] = random();
	}
	
	//multi threads	
	pthread_barrier_init(&b, NULL, NTHR+1);
	
	for (i=0; i<NTHR; i++)
	{	
		err = pthread_create(&tid, NULL, thr_fn, (void *)(i*TNUM));
		if (err != 0)
			perror("can't create thread");
	}
	
	pthread_barrier_wait(&b);
	
	//合并
	merge();
	
	for (i = 0; i < NUMNUM; i++)
	{
		printf("%ld\n",snums[i]);
	}
	
	return 0;
}

