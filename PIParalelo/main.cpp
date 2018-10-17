#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc,char *argv[])
{
    int n, rank, size;
    double sum, h, pi, x, mypi;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        cout << "Introduce la precision del calculo (n > 0): ";
        cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank >= 0)
    {
        sum = 0.0;
        h = 1.0 / (double) n;
        x = 0.0;

        for(int i = rank + 1; i <= n; i+= size)
        {
            x = h * ((double)i - 0.5);
            sum += (4.0 / (1.0 + x*x));
        }

        mypi = sum * h;
    }

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        cout << "PI: " << pi << endl;
    }

    MPI_Finalize();

    return 0;
}
