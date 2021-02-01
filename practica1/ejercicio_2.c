#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int nproc, myrank, value;

    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0)
    {
        printf("Introduzca un numero: ");
        scanf("%d", &value);
        MPI_Send(&value, 1, MPI_INT, (myrank + 1), 0, MPI_COMM_WORLD);
        printf("Proceso %d ha enviado %d\n", myrank, value);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, (myrank - 1), 0, MPI_COMM_WORLD, &status);
        printf("Proceso %d ha recibido %d\n", myrank, value);
        if (myrank < nproc - 1) /* El ultimo solo envia, no recibe */
        {
            MPI_Send(&value, 1, MPI_INT, (myrank + 1), 0, MPI_COMM_WORLD);
            printf("Proceso %d ha enviado %d\n", myrank, value);
        }
    }

    MPI_Finalize();
}