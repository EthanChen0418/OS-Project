#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>

asmlinkage int sys_process_time(int is_start, struct timespec *start_time, struct timespec *end_time, pid_t pid){
	if(is_start)
		getnstimeofday(start_time);
	else{
		getnstimeofday(end_time);
		printk("[Project1] %d %lu.%09lu %lu.%09lu\n", pid, start_time->tv_sec, start_time->tv_nsec, end_time->tv_sec, end_time->tv_nsec);
	}

	return 0;
}
