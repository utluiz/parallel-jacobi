#!/bin/sh

#chmod +x ./Debug/parallel-jacobi
#chmod +x ./Release/parallel-jacobi

# 5x serial
./execute-generated.sh 0 0
./execute-generated.sh 0 0
./execute-generated.sh 0 0
./execute-generated.sh 0 0
./execute-generated.sh 0 0

# 5x pthread 2 threads
./execute-generated.sh 2 1
./execute-generated.sh 2 1
./execute-generated.sh 2 1
./execute-generated.sh 2 1
./execute-generated.sh 2 1

# 5x pthread 3 threads
./execute-generated.sh 3 1
./execute-generated.sh 3 1
./execute-generated.sh 3 1
./execute-generated.sh 3 1
./execute-generated.sh 3 1

# 5x pthread 4 threads
./execute-generated.sh 4 1
./execute-generated.sh 4 1
./execute-generated.sh 4 1
./execute-generated.sh 4 1
./execute-generated.sh 4 1

# 5x pthread 5 threads
./execute-generated.sh 5 1
./execute-generated.sh 5 1
./execute-generated.sh 5 1
./execute-generated.sh 5 1
./execute-generated.sh 5 1


# 5x openmp 2 threads
./execute-generated.sh 2 2
./execute-generated.sh 2 2
./execute-generated.sh 2 2
./execute-generated.sh 2 2
./execute-generated.sh 2 2

# 5x openmp 3 threads
./execute-generated.sh 3 2
./execute-generated.sh 3 2
./execute-generated.sh 3 2
./execute-generated.sh 3 2
./execute-generated.sh 3 2

# 5x openmp 4 threads
./execute-generated.sh 4 2
./execute-generated.sh 4 2
./execute-generated.sh 4 2
./execute-generated.sh 4 2
./execute-generated.sh 4 2

# 5x openmp 5 threads
./execute-generated.sh 5 2
./execute-generated.sh 5 2
./execute-generated.sh 5 2
./execute-generated.sh 5 2
./execute-generated.sh 5 2


#read -p "Press [Enter] key to start backup..."