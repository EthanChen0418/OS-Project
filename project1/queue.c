#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "project1.h"

void init_queue(Queue *q){
	q->current_n = 0;
	q->current_index = 0;
	return;
}

int is_empty(Queue *q){
	return q->current_n == 0? 1: 0;
}

int is_full(Queue *q){
	return q->current_n == MAXPROCESSNUM? 1: 0;
}

int pop(Queue *q){
	int result;

	if(is_empty(q)){
		fputs("Error: Try to get from empty queue.  Terminatig.\n", stderr);
		exit(-1);
	}
	else{
		result = q->data[q->current_index];
		q->current_index = (q->current_index + 1) % MAXPROCESSNUM;
		q->current_n--;
	}

	return result;
}

void push(Queue *q, int n){
	if(is_full(q)){
		fputs("Error: Queue already full.  Terminating.\n", stderr);
		exit(-1);
	}
	else{
		q->data[(q->current_index + q->current_n) % MAXPROCESSNUM] = n;
		q->current_n++;
	}

	return;
}