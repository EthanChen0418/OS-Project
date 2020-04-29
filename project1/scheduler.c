#define _GNU_SOURCE
#include "project1.h"

int FIFO_next(Process p[], int now, int FIFO_index, int N){
	if(now == -1){
		if(p[FIFO_index].status == READY)
			return FIFO_index;
		else
			return -1;
	}
	else{
		if(p[now].ex_time > 0)
			return now;
		else if(now + 1 < N && p[now + 1].status == READY)
			return now + 1;
		else
			return -1;
	}
}

int RR_next(Queue *q){
	if(is_empty(q))
		return -1;
	else
		return pop(q);
}

int SJF_next(Process p[], int N){
	int next = -1, found = 0, min_exec_time;

	for(int i = 0; i < N; i++)
		if(p[i].status != NOTAVAILABLE && (!found || p[i].ex_time < min_exec_time)){
			min_exec_time = p[i].ex_time;
			next = i;
			found = 1;
		}

	return next;
}