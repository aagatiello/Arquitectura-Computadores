#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int N = 10;
	int array[N], arrActualizado[N];

	/* Nodo 0 inicializa array asignando indices */
	if (rank == 0)
	{
		for (int i = 0; i < N; i++)
			array[i] = i;
	}

	if ((N % size) == 0)
	{
		/* Dividir array en partes */
		int divisiones = N / size;
		if (rank < (N % size))
			divisiones = divisiones + 1;
		int *arrDividido = malloc(divisiones * sizeof(int));

		MPI_Scatter(array, divisiones, MPI_INT, arrDividido, divisiones, MPI_INT, 0, MPI_COMM_WORLD);
		for (int i = 0; i < divisiones; i++)
		{
			/* Al recibir dato actualiza sumando su rank */
			arrDividido[i] = arrDividido[i] + rank;
			printf("Nodo %d ha recibido la porcion de datos: %d\n", rank, arrDividido[i]);
		}

		/* Cada proceso envía su porcion modificada a root */
		MPI_Gather(arrDividido, divisiones, MPI_INT, arrActualizado, divisiones, MPI_INT, 0, MPI_COMM_WORLD);
		if (rank == 0)
		{
			for (int i = 0; i < N; i++)
			{
				printf("Proceso %d ha modificado sus datos a: %d\n", i, arrActualizado[i]);
			}
		}
	}
	else
	{
		printf("El numero de datos total (%d) no es multiplo del numero de procesos introducidos.\n", N);
	}

	MPI_Finalize();
}