#!/bin/bash
Ks=( 5 10 20 50 )
for K in ${Ks[@]} 
do
    echo $K
    for ((i=300; i<750; i+=50))
    do
    L=2000
    C=1
    lambda=$i

    echo $i
    ./a.out M/D/1/$K 5500 $lambda $L $C >> q8_1Out.csv

    done
done
exit 0
