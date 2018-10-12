#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc,char *argv[])
{
    int rank, size,contador;
    MPI_Status estado;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0)
    {
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&contador,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&estado);
        cout << "Soy el procesador "<<rank<<" y he recibido "<<contador<< endl;
        contador++;
        if(rank!=size-1)
        {
            MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}
