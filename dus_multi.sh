#!/bin/bash

rm dus.txt
x=235
while [ $x -le 50000 ]
do echo $x
    bash dus_single.sh $1 $x >> dus.txt
    sleep 0.01
    (( x = x + 500 )) 
done

