#include <cstdlib>
#include <iostream>
#include <vector>
#include "mpi.h"
using namespace std;

int main(int argc, char *argv[]) {
    int tam, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    tam = size * 100;

    vector<long> v1, v2, v1Local, v2Local;
    v1.resize(tam, 0);
    v2.resize(tam, 0);
    v1Local.resize(tam/size, 0);
    v2Local.resize(tam/size, 0);

    if (rank == 0) {
        for(long i = 0; i < tam; i++) {
            v1[i] = i + 1;
            v2[i] = (i+1) * 10;
        }
    }

    MPI_Scatter(&v1[0],
            tam / size,
            MPI_LONG,
            &v1Local[0],
            tam / size,
            MPI_LONG,
            0,
            MPI_COMM_WORLD);

    MPI_Scatter(&v2[0],
            tam / size,
            MPI_LONG,
            &v2Local[0],
            tam / size,
            MPI_LONG,
            0,
            MPI_COMM_WORLD);

    long producto = 0;
    for (long i = 0; i < tam / size; ++i) {
        producto += v1Local[i] * v2Local[i];
    }
    long total;

    MPI_Reduce(&producto,
            &total,
            1,
            MPI_LONG,
            MPI_SUM,
            0,
            MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Total -> " << total << endl;
    }

    MPI_Finalize();
    return 0;
}
