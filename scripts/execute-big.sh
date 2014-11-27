#!/bin/sh

cd ..

execute(){
	for i in `seq 1 5`; do
		./Release/parallel-jacobi "./big/c-33/c-33.mtx" $1 $2 0
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
