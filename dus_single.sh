#!/bin/bash

./tcp_ser4 $1 $2 & 
./tcp_client4 127.0.0.1 $2 & 
wait -n 
pkill -P $$ 

