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

  float arrayA[1000];
  float arrayB[1000];

  /* Inicializamos los datos */
  for (int i = 0; i < 1000; i++)
  {
    arrayA[i] = rank;
  }

  /* Calcular el rango de los vecinos */
  int derecha = (rank + 1) % count;
  int izquierda = (rank - 1 + count) % count;

  /* Enviamos y recibimos los datos */
  MPI_Send(arrayA, 1000, MPI_FLOAT, derecha, 0, MPI_COMM_WORLD);
  printf("Soy el proceso %d: he enviado %f al proceso %d\n", rank, arrayA[rand() % 1001], derecha);
  MPI_Recv(arrayB, 1000, MPI_FLOAT, izquierda, 0, MPI_COMM_WORLD, &status);
  printf("Soy el proceso %d: he recibido %f del proceso %d\n", rank, arrayB[rand() % 1001], izquierda);

  MPI_Finalize();
}
