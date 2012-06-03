#!/bin/bash

for ((i=125; i<475; i+=25))
do
L=2000
C=1000
lambda=$i
echo $i
./a.out M/D/1/ 100 $lambda $L $C >> q4Out

done

exit 0
