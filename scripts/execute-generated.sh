#!/bin/sh

#chmod +x ./Debug/parallel-jacobi
#chmod +x ./Release/parallel-jacobi

cd ..

execute(){
	for i in `seq 2 2 128`; do
		filename=./generated/m$i-1.txt
		for j in `seq 1 5`; do
			echo $i, $j
			./Release/parallel-jacobi $filename $1 $2 0
		done
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