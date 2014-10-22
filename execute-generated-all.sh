#!/bin/sh

#chmod +x ./Debug/parallel-jacobi
#chmod +x ./Release/parallel-jacobi

# 5x serial
./execute-generated.sh S 0
./execute-generated.sh S 0
./execute-generated.sh S 0
./execute-generated.sh S 0
./execute-generated.sh S 0

# 5x pthread 2 threads
./execute-generated.sh P 2
./execute-generated.sh P 2
./execute-generated.sh P 2
./execute-generated.sh P 2
./execute-generated.sh P 2

# 5x pthread 3 threads
./execute-generated.sh P 3
./execute-generated.sh P 3
./execute-generated.sh P 3
./execute-generated.sh P 3
./execute-generated.sh P 3

# 5x pthread 4 threads
./execute-generated.sh P 4
./execute-generated.sh P 4
./execute-generated.sh P 4
./execute-generated.sh P 4
./execute-generated.sh P 4

# 5x pthread 5 threads
./execute-generated.sh P 5
./execute-generated.sh P 5
./execute-generated.sh P 5
./execute-generated.sh P 5
./execute-generated.sh P 5


# 5x openmp 2 threads
./execute-generated.sh O 2
./execute-generated.sh O 2
./execute-generated.sh O 2
./execute-generated.sh O 2
./execute-generated.sh O 2

# 5x openmp 3 threads
./execute-generated.sh O 3
./execute-generated.sh O 3
./execute-generated.sh O 3
./execute-generated.sh O 3
./execute-generated.sh O 3

# 5x openmp 4 threads
./execute-generated.sh O 4
./execute-generated.sh O 4
./execute-generated.sh O 4
./execute-generated.sh O 4
./execute-generated.sh O 4

# 5x openmp 5 threads
./execute-generated.sh O 5
./execute-generated.sh O 5
./execute-generated.sh O 5
./execute-generated.sh O 5
./execute-generated.sh O 5


#read -p "Press [Enter] key to start backup..."