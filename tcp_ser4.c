/**********************************
tcp_ser.c: the source file of the server in tcp transmission
***********************************/

#include "headsock.h"

#define BACKLOG 10

void str_ser(int, double, int); // transmitting and receiving function

int main(int argc, char *argv[])
{
    int sockfd, con_fd, ret;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;

    double error_p; // error probability, supports non-integers
    int data_len;   // allow variable data length

    pid_t pid;

    if (argc != 3)
    {
        // Error probability: 1st arg
        // Data length: 2nd arg
        printf("parameters not match");
    }

    error_p = atof(argv[1]);
    data_len = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket
    if (sockfd < 0)
    {
        printf("error in socket!");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYTCP_PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr("172.0.0.1");
    bzero(&(my_addr.sin_zero), 8);
    ret = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)); //bind socket
    if (ret < 0)
    {
        printf("error in binding");
        exit(1);
    }

    ret = listen(sockfd, BACKLOG); // listen
    if (ret < 0)
    {
        printf("error in listening");
        exit(1);
    }

    while (1)
    {
        /*
        printf("waiting for data\n");
        */
        sin_size = sizeof(struct sockaddr_in);
        con_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); // accept the packet
        if (con_fd < 0)
        {
            printf("error in accept\n");
            exit(1);
        }

        if ((pid = fork()) == 0) // creat acception process
        {
            close(sockfd);
            str_ser(con_fd, error_p, data_len); // receive packet and response
            close(con_fd);
            exit(0);
        }
        else
        {
            close(con_fd); // parent process
        }
    }
    close(sockfd);
    exit(0);
}

void str_ser(int sockfd, double error_p, int data_len)
{
    char buf[BUFSIZE];
    FILE *fp;
    char recvs[data_len];
    struct ack_so ack;
    int end;
    int n = 0;
    long lseek = 0;
    end = 0;

    int seq_num = 0; // keep track of current frame
    int has_err = 0; // used to simulate errors

    // RNG using sys/time.h instead of time.h for seeding
    struct timeval seedt;
    gettimeofday(&seedt, NULL);
    srand(seedt.tv_usec * seedt.tv_sec);

    /*
    printf("receiving data!\n");
    */

    while (!end)
    {
        // Get a random number between 0 and 100
        has_err = error_p > (double)rand() / RAND_MAX * 100;

        if ((n = recv(sockfd, &recvs, data_len, 0)) == -1) // receive the packet
        {
            printf("error when receiving\n");
            exit(1);
        }
        else
        {
            // Code for simulation of errors
            if (!has_err)
            {
                seq_num++;                // no error, increment to next frame
                if (recvs[n - 1] == '\0') // if it is the end of the file
                {
                    end = 1;
                    n--;
                }
                memcpy((buf + lseek), recvs, n);
                lseek += n;
            }

            // No error -> ACK: next frame
            // Error -> NACK: current frame
            ack.num = seq_num;
            ack.len = 0;
            if ((n = send(sockfd, &ack, 2, 0)) == -1)
            {
                printf("send error!"); // send the ack
                exit(1);
            }
        }
    }

    if ((fp = fopen("myTCPreceive.txt", "wt")) == NULL)
    {
        printf("File doesn't exist\n");
        exit(0);
    }
    fwrite(buf, 1, lseek, fp); //write data into file
    fclose(fp);
    /*
    printf("a file has been successfully received!\nthe total data received is %d bytes\n", (int)lseek);
    */
}
