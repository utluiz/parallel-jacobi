#!/bin/sh


./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 5 0

./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 5 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 5 0


echo Serial
./Debug/parallel-jacobi "big/c-33/c-33.mtx" S 0 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" S 0 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" S 0 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" S 0 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" S 0 0

echo Pthread
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 2 0

./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 3 0

./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" P 4 0

echo OpenMP
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 2 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 2 0

./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 3 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 3 0

./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 4 0
./Debug/parallel-jacobi "big/c-33/c-33.mtx" O 4 0

#read -p "Press [Enter] key to start backup..."