#!/bin/bash

for ((i=50; i<190; i+=10))
do
L=5000
C=1000000
lambda=$i
echo $i
./a.out M/D/1 5500 $lambda $L $C >> q5Out

done

exit 0
