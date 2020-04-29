#ifndef PROJECT1_H
#define PROJECT1_H

#include <sys/types.h>
#include <sched.h>

#define MAXPROCESSNUM 20
#define MAXPOLICYNAME 5
#define MAXPROCESSNAME 32
#define SCHEDULERCPU 0
#define EXECCPU 1
#define FIFO 'F'
#define SJF 'S'
#define PSJF 'P'
#define RR 'R'
#define MAXTIMEQUANTUM 500
#define START 1
#define END 0

#ifndef SYSCALLNUM
#define SYSCALLNUM 333
#endif

#define TIMEUNIT {volatile unsigned long t; for(t = 0; t < 1000000UL; t++);}
#define PSJF_next(q, N) SJF_next(q, N)

typedef struct sched_param SP;

typedef enum status{
	NOTAVAILABLE,
	READY,
	RUNNING 
} Status;

typedef struct process{
	char name[MAXPROCESSNAME];
	int ready_time;
	int ex_time;
	Status status;
	pid_t pid;
} Process;

typedef struct queque{
	int current_n;
	int current_index;
	int data[MAXPROCESSNUM];
} Queue;

void init_queue(Queue *q);
int is_empty(Queue *q);
int is_full(Queue *q);
int pop(Queue *q);
void push(Queue *q, int n);

int FIFO_next(Process p[], int now, int ready_index, int N);
int RR_next(Queue *q);
int SJF_next(Process p[], int N);

void move_process(pid_t pid, cpu_set_t *cpu);
void set_priority(pid_t pid, SP *sched_param);
void schedule_process(pid_t pid, cpu_set_t *cpu, SP *sched_param);
void run_process(pid_t pid, cpu_set_t *exec_cpu, SP *max_param);
void halt_process(pid_t pid, cpu_set_t *sched_cpu, SP *min_param);
void porcess_execution(Process p);
pid_t process_ready(Process p, SP *min_shced, int max_priority);


#endif