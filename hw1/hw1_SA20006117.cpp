#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctime>

using namespace std;
static int N = 20;

int main (int argc, char **argv)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    unsigned long tt = (unsigned long)tv.tv_sec * 1000 + ((unsigned long)tv.tv_usec)/1000;
    unsigned long T0 = tt;
    unsigned long R = 1000;
    
    int myid, numprocs;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    struct timeval mytv;
    unsigned long time_now = 0;
    unsigned long time_all[N] = {0};
    int flag = 0;

    //while(1) {

        if (flag > 0) 
            sleep((R/1010));
        else
            sleep((R/1000));

        gettimeofday(&mytv, NULL);
        time_all[myid] = (unsigned long)mytv.tv_sec * 1000 + ((unsigned long)mytv.tv_usec)/1000;

        MPI_Bcast(&time_all[myid], 1, MPI_UNSIGNED_LONG, myid, MPI_COMM_WORLD);
        cout << myid << endl;
        for (int i = 0; i < numprocs; i++) {
            cout << time_all[i] << endl;
        }
        cout << endl;
        //MPI_Send(time_now);
    
    //}
    
    
    MPI_Finalize();
    
    return 0;
}