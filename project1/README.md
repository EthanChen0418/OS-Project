# OS Project 1
## Compiling
```
make
```
The default system call number is 333.  If a new one is assigned after compiling the kernel, use
```
make CALLNUM=$1
```
where $1 is the new system call number.

## Running 
```
sudo ./main
```
If you want to reproduce the output provided, use
```
sudo bash run.sh $1 $2
```
after compiling, where $1 is the input directory and $2 is the output directory.
If you want to reproduce the demo, use
```
sudo bash demo.sh $1
```
after compiling, where $1 is the input directory.