#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int rank, count;

  MPI_Status status;
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &count);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  float arrayA[10000];
  float arrayB[10000];

  if (count == 2)
  {
    for (int i = 0; i < 10000; i++)
    { /* Inicializamos los datos */
      arrayA[i] = rank;
    }

    /* Envio y recepcion de datos */
    if (rank == 0)
    { // Task 0
      MPI_Send(arrayA, 10000, MPI_FLOAT, 1, 100, MPI_COMM_WORLD);
      MPI_Recv(arrayB, 10000, MPI_FLOAT, 1, 100, MPI_COMM_WORLD, &status);
      printf("Soy el proceso %d: Valor cualquiera de mi array B %f\n", rank, arrayB[rand() % 10001]);
    }
    else
    { // Task 1
      MPI_Recv(arrayB, 10000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD, &status);
      MPI_Send(arrayA, 10000, MPI_FLOAT, 0, 100, MPI_COMM_WORLD);
      printf("Soy el proceso %d: Valor cualquiera de mi array B %f\n", rank, arrayB[rand() % 10001]);
    }
  }

  MPI_Finalize();
}
