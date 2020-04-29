ifdef CALLNUM
flags := -DSYSCALLNUM=$(CALLNUM)
endif

flags += -c

.PHONY: all clean

all: main

main: main.o scheduler.o queue.o functions.o project1.h
	gcc main.o scheduler.o queue.o functions.o -o main

main.o: main.c project1.h
	gcc $(flags) main.c -o main.o

scheduler.o: scheduler.c project1.h
	gcc $(flags) scheduler.c -o scheduler.o

queue.o: queue.c project1.h
	gcc $(flags) queue.c -o queue.o

functions.o: functions.c project1.h
	gcc $(flags) functions.c -o functions.o

clean:
	rm -rf main main.o scheduler.o queue.o functions.o
