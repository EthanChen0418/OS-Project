#!/bin/bash

dmesg --clear
./main < $1/TIME_MEASUREMENT.txt
dmesg -t | grep Project1

dmesg --clear
./main < $1/FIFO_1.txt
dmesg -t | grep Project1

dmesg --clear
./main < $1/PSJF_2.txt
dmesg -t | grep Project1

dmesg --clear
./main < $1/RR_3.txt
dmesg -t | grep Project1

dmesg --clear
./main < $1/SJF_4.txt
dmesg -t | grep Project1
