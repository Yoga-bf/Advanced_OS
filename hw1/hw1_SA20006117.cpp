#include <iostream>
#include <mpi.h>

using namespace std;

int main (int argc, char **argv)
{
    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    cout << "Hello" << myid << endl;
    MPI_Finalize();
    //there are something wrong
    //test
    return 0;
}