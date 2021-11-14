#!/bin/bash

rm ep.txt
x=0
while [ $x -lt 100 ]
do echo -n $x >> ep.txt
    bash ep_single.sh $x >> ep.txt
    sleep 0.01
    (( x++ )) 
done
