#define _GNU_SOURCE
#include <sys/types.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "project1.h"

void move_process(pid_t pid, cpu_set_t *cpu){
	if(sched_setaffinity(pid, sizeof(cpu_set_t), cpu) == -1){
		perror("sched_setaffinity: ");
		exit(-1);
	}

	return;
}

void set_priority(pid_t pid, SP *sched_param){
	if(sched_setscheduler(pid, SCHED_FIFO, sched_param) == -1){
		perror("sched_setscheduler: ");
		exit(-1);
	}

	return;
}


void schedule_process(pid_t pid, cpu_set_t *cpu, SP *sched_param){
	set_priority(pid, sched_param);
	move_process(pid, cpu);
	return;
}

void run_process(pid_t pid, cpu_set_t *exec_cpu, SP *max_param){
	move_process(pid, exec_cpu);
	set_priority(pid, max_param);
	return;
}

void halt_process(pid_t pid, cpu_set_t *sched_cpu, SP *min_param){
	set_priority(pid, min_param);
	move_process(pid, sched_cpu);
	return;
}

void process_execution(Process p){
	struct timespec start, end;
	int sysresult;

	if((sysresult = syscall(SYSCALLNUM, START, &start, &end, getpid())) == -1){
		perror("syscall: ");
		exit(-1);
	}

	while(p.ex_time > 0){
		TIMEUNIT;
		p.ex_time--;
	}

	if((sysresult = syscall(SYSCALLNUM, END, &start, &end, getpid())) == -1){
		perror("syscall: ");
		exit(-1);
	}

	printf("%s %d\n", p.name, getpid());
	return;
}

pid_t process_ready(Process p, SP *min_shced, int max_priority){
	pid_t pid;

	if((pid = fork()) == -1){
		perror("fork: ");
		exit(-1);
	}
	else if(pid == 0){
		while(sched_getcpu() != EXECCPU);

		while(1){
			SP sched_param;

			if(sched_getparam(getpid(), &sched_param) == -1){
				perror("sched_getparam: ");
				exit(-1);
			}

			if(sched_param.sched_priority == max_priority)
				break;
		}

		process_execution(p);
		exit(0);
	}
	else
		set_priority(pid, min_shced);

	return pid;
}