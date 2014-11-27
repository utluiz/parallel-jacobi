#!/bin/sh

cd ..

execute(){
	for i in `seq 1 20`; do
		./Release/parallel-jacobi "/home/luiz/git/distributed-jacobi/big/c-33.mtx" $1 $2 0
		./Release/parallel-jacobi "/home/luiz/git/distributed-jacobi/big/3D_51448_3D.mtx" $1 $2 0
		./Release/parallel-jacobi "/home/luiz/git/distributed-jacobi/big/powersim.mtx" $1 $2 0
	done
}

execute S 0

execute P 2
execute P 3
execute P 4
execute P 5

execute O 2
execute O 3
execute O 4
execute O 5

#read -p "Press [Enter] key to start backup..."
