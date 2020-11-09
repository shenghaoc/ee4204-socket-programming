#!/bin/bash

./tcp_ser4 $1 1000 & 
./tcp_client4 127.0.0.1 1000 & 
wait -n 
pkill -P $$ 
