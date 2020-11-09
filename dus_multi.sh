#!/bin/bash

x=235; while [ $x -le 50000 ]; do echo $x; bash dus_single.sh $x >> dus.txt; (( x = x + 500 )) ;  done

