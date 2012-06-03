#!/bin/bash


for ((i=300; i<750; i+=50))
do
L=2000
C=1
lambda=$i
K=5
echo $i
./a.out M/D/1/$K 100 $lambda $L $C >> q8_1Out

done

exit 0
