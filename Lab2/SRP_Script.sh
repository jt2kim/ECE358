#!/bin/bash

for ((i=10; i<100; i+=10))
do
Window=15
echo $i
./simulator $i $Window
mv layer3.txt layer3_FER_$i.txt
mv layer3_FER_$i.txt Q3_Orig/W_15

done

exit 0
