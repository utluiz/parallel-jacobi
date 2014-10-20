#!/bin/sh

num_threads=$1
algorithm=$2
verbose=0

base_path=/c/Users/losa/git/parallel-jacobi/results

for (( i=2; i<=128; i+=2 )) do
	filename=$base_path/generated/m$i-1.txt
	echo $filename
	if [ -f $filename ];
	then
	    echo found one
	else
	    echo NONE
	fi
#    ./Release/parallel-jacobi generated/m$i-1.txt $num_threads $algorithm $verbose
done

