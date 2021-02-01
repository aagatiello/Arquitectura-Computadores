#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int rank, count;
    char msg[20];
    int limit = rand() % 11;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i != limit; i++)
    {
        if (rank == 0)
        {
            printf("I am master. Sending the message %d\n", i);
            strcpy(msg, "Hello World!");
            MPI_Send(msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
            if (i != 0)
            {
                MPI_Recv(msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD, &status);
                printf("I am master. Receiving the message %d: %s\n", i, msg);
            }
        }
        else
        {
            MPI_Recv(msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);
            printf("I am the slave. Receiving the message %d: %s\n", i, msg);

            printf("I am the slave. Sending the message %d\n", i);
            strcpy(msg, "Hello World!");
            MPI_Send(msg, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}