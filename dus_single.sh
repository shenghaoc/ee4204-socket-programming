#!/bin/bash

./tcp_ser4 0 $1 & 
./tcp_client4 127.0.0.1 $1 & 
wait -n 
pkill -P $$ 

