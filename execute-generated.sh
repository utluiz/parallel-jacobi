#!/bin/sh

algorithm=$1
num_threads=$2
verbose=0

#base_path=/c/Users/losa/git/parallel-jacobi/results
base_path=.

#for (( i=2; i<=128; i+=2 )) do
for i in `seq 2 2 128`; do
	filename=$base_path/generated/m$i-1.txt
	#echo $filename
	#if [ -f $filename ];
	#then
	#    echo found one
	#else
	#    echo NONE
	#fi
    ./Debug/parallel-jacobi $filename $algorithm $num_threads $verbose
done

