#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "project1.h"

int main(int argc, char *argv[]){
	char S[MAXPOLICYNAME];
	int N;
	scanf("%s %d", S, &N);
	char policy = S[0];

	Process p[MAXPROCESSNUM];

	for(int i = 0; i < N; i++){
		scanf("%s %d %d", p[i].name, &p[i].ready_time, &p[i].ex_time);
		p[i].status = NOTAVAILABLE;
	}

	cpu_set_t cpu[2];

	for(int i = 0; i < 2; i++){
		CPU_ZERO(&cpu[i]);
		CPU_SET(i, &cpu[i]);
	}

	int max_priority, min_priority;

	if((max_priority = sched_get_priority_max(SCHED_FIFO)) == -1){
		perror("sched_get_priority_max: ");
		return -1;
	}

	if((min_priority = sched_get_priority_min(SCHED_FIFO)) == -1){
		perror("sched_get_priority_min: ");
		return -1;
	}

	SP min_sched, max_sched;
	min_sched.sched_priority = min_priority;
	max_sched.sched_priority = max_priority;

	schedule_process(getpid(), &cpu[SCHEDULERCPU], &max_sched);

	int completed_processes = 0, running = -1, timer = p[0].ready_time, wait_ready_index = 0, FIFO_index = 0, time_quantum = MAXTIMEQUANTUM;
	Queue q;

	if(policy == RR)
		init_queue(&q);

	while(1){
		if(running != -1 && p[running].ex_time == 0){
			waitpid(p[running].pid, NULL, 0);
			p[running].status = NOTAVAILABLE;
			running = -1;
			completed_processes++;

			if(completed_processes >= N)
				break;

			if(policy == FIFO)
				FIFO_index += 1;
		}

		while(wait_ready_index < N && p[wait_ready_index].ready_time == timer){
			p[wait_ready_index].status = READY;
			p[wait_ready_index].pid = process_ready(p[wait_ready_index], &min_sched, max_priority);

			if(policy == RR)
				push(&q, wait_ready_index);

			wait_ready_index++;
		}

		int next_process;

		switch(policy){
			case FIFO:
				next_process = FIFO_next(p, running, FIFO_index, N);
				break;

			case RR:
				if(time_quantum == 0 || running == -1)
					time_quantum = MAXTIMEQUANTUM;

				next_process = (running == -1 || time_quantum == MAXTIMEQUANTUM)? RR_next(&q): running;
				time_quantum--;
				break;

			case SJF:
				next_process = running == -1? SJF_next(p, N): running;
				break;

			case PSJF:
				next_process = PSJF_next(p, N);
				break;

			default:
				fputs("No such scheduling type.\n", stderr);
				return -1;
		}

		if(next_process != -1 && next_process != running){
			if(running != -1){
				p[running].status = READY;
				halt_process(p[running].pid, &cpu[SCHEDULERCPU], &min_sched);

				if(policy == RR)
					push(&q, running);
			}

			p[next_process].status = RUNNING;
			run_process(p[next_process].pid, &cpu[EXECCPU], &max_sched);
			running = next_process;
		}

		TIMEUNIT;
		timer++;

		if(running != -1)
			p[running].ex_time--;
	}

	return 0;
}