#!/bin/bash
Ws=( 5 15 )
for W in ${Ws[@]} 
do
    echo window size $W
    for ((i=10; i<100; i+=10))
    do
    Window=5
    echo $i
    #./simulator $i $W
    mv layer2.txt layer2_$i.txt
    mv layer2_$i.txt 5_2
    mv layer3.txt layer3_$i.txt
    mv layer3_$i.txt 5_3

    done
done
exit 0
