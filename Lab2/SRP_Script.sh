#!/bin/bash
Ws=( 5 15 )

for ((i=10; i<100; i+=10))
do
Window=5
echo $i
./simulator $i $Window
mv layer2.txt layer2_$i.txt
mv layer2_$i.txt 5_2
mv layer3.txt layer3_$i.txt
mv layer3_$i.txt 5_3

done

exit 0
