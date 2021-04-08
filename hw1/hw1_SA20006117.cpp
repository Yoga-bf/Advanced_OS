#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctime>
#include <cstring>

using namespace std;

static int tag = 99;

int main (int argc, char **argv)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    unsigned long tt = (unsigned long)tv.tv_sec * 1000 + ((unsigned long)tv.tv_usec)/1000;
    unsigned long T0 = tt;
    unsigned long R = 1000;
    unsigned long sleep_time = R;
    int source;

    int myid, numprocs;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    struct timeval mytv;
    unsigned long my_time = 0;
    unsigned long long ave_time = 0;
    unsigned long time_all[numprocs] = {0};
    
    while(1) {

        sleep(sleep_time/1000);

        gettimeofday(&mytv, NULL);
        my_time = (unsigned long)mytv.tv_sec * 1000 + ((unsigned long)mytv.tv_usec)/1000;
        time_all[myid] = my_time;

        for (source = 0; source < numprocs; source++) {
            if (source == myid)
                continue;
            MPI_Send(&my_time, 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD);
        }

        ave_time = 0;
        for (source = 0; source < numprocs; source++) {
            if (source == myid){
                ave_time += time_all[source];
                continue;
            }  
            MPI_Recv(&time_all[source], 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD, &status);
            ave_time += time_all[source];
        }

        ave_time = (unsigned long)(ave_time/numprocs);
        sleep_time = R + ave_time - my_time;
        
        cout << myid << endl;
        for (int i = 0; i < numprocs; i++) {
            cout << "machine " << i << " time is " << time_all[i] << endl;
        }
        cout << "avetime is " << ave_time << endl;      
    }

    MPI_Finalize();
    
    return 0;
}