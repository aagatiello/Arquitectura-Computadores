#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int rank, size;
  int array[5], suma[5], producto[5];

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* Inicializamos el array */
  for (int i = 0; i < 5; i++)
  {
    array[i] = rank + 1;
  }

  MPI_Reduce(array, suma, 5, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(array, producto, 5, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {

    printf("Matriz despues de la suma: \n");
    for (int i = 0; i < size; i++)
    {
      printf("%d \n", suma[i]);
    }
    printf("Matriz despues del producto: \n");
    for (int i = 0; i < size; i++)
    {
      printf("%d \n", producto[i]);
    }
  }

  MPI_Finalize();
}
