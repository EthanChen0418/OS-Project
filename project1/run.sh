#!/bin/bash

dmesg --clear
./main < $1/TIME_MEASUREMENT.txt > $2/TIME_MEASUREMENT_stdout.txt
dmesg -t | grep Project1 > $2/TIME_MEASUREMENT_dmesg.txt

for policy in FIFO RR SJF PSJF; do
	for i in 1 2 3 4 5; do
		dmesg --clear;
		./main < $1/${policy}_${i}.txt > $2/${policy}_${i}_stdout.txt;
		dmesg -t | grep Project1 > $2/${policy}_${i}_dmesg.txt;
	done;
done;
	
