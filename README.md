# EE4204 Socket Programming Lab

For AY2020/2021 Semester 2, the client-server socket program was required to be TCP-based and implement ARQ with stop-and-wait.

`compile.sh` is a bash script that runs the commands to compile both client and server programs.

For `tcp_client4`, the arguments are the server address and data length.

For `tcp_ser4`, the arguments are error probability and data length.

In branch `data-unit-size`, run `dus_multi.sh` with error probability as the argument to obtain 100 data points against data unit size. Comment/Uncomment the last two print statements in `main` of `tcp_client4.c` to choose transfer time or throughput.

In branch `error-probability`, run `ep_multi.sh` without arguments to obtain 100 data points against error probability. Comment/Uncomment the last two print statements in `main` of `tcp_client4.c` to choose transfer time or throughput.

NOTE: I mixed up SEQ and ACK
