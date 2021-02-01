#include <mpi.h> /* Fichero cabecera con definiciones y tipos */
#include <stdio.h>

int main(int argc, char **argv)
{
	int x, y;

	MPI_Init(&argc, &argv); /* Inicializa la aplicación paralela MPI */
	MPI_Comm_size(MPI_COMM_WORLD, &y);
	MPI_Comm_rank(MPI_COMM_WORLD, &x);
	
	printf("Hola mundo, soy el proceso %d de un total de %d. \n", x, y);

	MPI_Finalize();
}
