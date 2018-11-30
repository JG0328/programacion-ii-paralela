#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, contador;
    MPI_Status estado;

    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de hebras
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    if(rank == 0)
    {
        for(int i = 2; i < size; i++)
        {
            if(i % 2 == 0)
            {
                MPI_Send(&rank //referencia al vector de elementos a enviar
                         ,1 // tamaño del vector a enviar
                         ,MPI_INT // Tipo de dato que envias
                         ,i // pid del proceso destino
                         ,0 //etiqueta
                         ,MPI_COMM_WORLD); //Comunicador por el que se manda
            }
        }
    }
    else if(rank == 1)
    {
        for(int i = 2; i < size; i++)
        {
            if(i % 2 == 1)
            {
                MPI_Send(&rank //referencia al vector de elementos a enviar
                         ,1 // tamaño del vector a enviar
                         ,MPI_INT // Tipo de dato que envias
                         ,i // pid del proceso destino
                         ,0 //etiqueta
                         ,MPI_COMM_WORLD); //Comunicador por el que se manda
            }
        }
    }

    if(rank > 1 && rank % 2 == 0)
    {
        MPI_Recv(&contador // Referencia al vector donde se almacenara lo recibido
                 ,1 // tamaño del vector a recibir
                 ,MPI_INT // Tipo de dato que recibe
                 ,0 // pid del proceso origen de la que se recibe
                 ,0 // etiqueta
                 ,MPI_COMM_WORLD // Comunicador por el que se recibe
                 ,&estado); // estructura informativa del estado
    }
    else if(rank > 1 && rank % 2 == 1)
    {
        MPI_Recv(&contador // Referencia al vector donde se almacenara lo recibido
                 ,1 // tamaño del vector a recibir
                 ,MPI_INT // Tipo de dato que recibe
                 ,1 // pid del proceso origen de la que se recibe
                 ,0 // etiqueta
                 ,MPI_COMM_WORLD // Comunicador por el que se recibe
                 ,&estado); // estructura informativa del estado
    }

    if(rank > 1)
    {
        cout<< "Soy el proceso "<<rank<<" y he recibido "<<contador<<endl;
    }

    // Terminamos la ejecucion de las hebras, despues de esto solo existira
    // la hebra 0
    // ¡Ojo! Esto no significa que las demas hebras no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    return 0;
}
