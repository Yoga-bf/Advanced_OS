#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctime>
#include <cstring>

using namespace std;
static int N = 20;
static int tag = 99;
int main (int argc, char **argv)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    unsigned long tt = (unsigned long)tv.tv_sec * 1000 + ((unsigned long)tv.tv_usec)/1000;
    unsigned long T0 = tt;
    unsigned long R = 1000;
    int source;

    int myid, numprocs;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    struct timeval mytv;
    unsigned long my_time = 0;
    unsigned long time_all[numprocs] = {0};
    

    int flag = 0;

    //while(1) {
        if (flag > 0) 
            sleep((R/1010));
        else
            sleep((R/1000));
        gettimeofday(&mytv, NULL);
        my_time = (unsigned long)mytv.tv_sec * 1000 + ((unsigned long)mytv.tv_usec)/1000;
        time_all[myid] = my_time;
        for (source = 0; source < numprocs; source++) {
            if (source == myid)
                continue;
            MPI_Send(&my_time, 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD);
        }
        for (source = 0; source < numprocs; source++) {
            if (source == myid)
                continue;
            MPI_Recv(&time_all[source], 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD, &status);
        }

        cout << myid << endl;
        for (int i = 0; i < numprocs; i++) {
            cout << time_all[i] << endl;
        }
    //}
    
    
    MPI_Finalize();
    
    return 0;
}

void test() {
    // unsigned long *my_time = (unsigned long *)malloc(sizeof(unsigned long));
    // //unsigned long time_all[N] = {0};
    // int flag = 0;
    // int *displs = (int *)malloc(sizeof(int)*numprocs);
    // int *recv_count = (int *)malloc(sizeof(int)*numprocs);
    // unsigned long *time_all = (unsigned long *)malloc(sizeof(unsigned long) * numprocs);
    // //memset(time_all, 0, sizeof(unsigned long *)*numprocs);
    // while(1) {

    //     if (flag > 0) 
    //         sleep((R/1010));
    //     else
    //         sleep((R/1000));

    //     gettimeofday(&mytv, NULL);
    //     if (myid != 0) {
    //         unsigned long *my_time = (unsigned long *)malloc(sizeof(unsigned long));
    //         int *displs = (int *)malloc(sizeof(int)*numprocs);
    //         int *recv_count = (int *)malloc(sizeof(int)*numprocs);
    //         unsigned long *time_all = (unsigned long *)malloc(sizeof(unsigned long) * numprocs);
    //     }
    //     *my_time = (unsigned long)mytv.tv_sec * 1000 + ((unsigned long)mytv.tv_usec)/1000;
    //     time_all[myid] = *my_time;
        
    //     MPI_Gatherv(my_time, 1, MPI_UNSIGNED_LONG, time_all, recv_count, displs, MPI_UNSIGNED_LONG, myid, MPI_COMM_WORLD);
    //     //MPI_Gather(my_time, 1, MPI_UNSIGNED_LONG, time_all, 1, MPI_UNSIGNED_LONG, myid, MPI_COMM_WORLD);

    //     cout << myid << endl;
    //     for (int i = 0; i < numprocs; i++) {
    //         cout << time_all[i] << endl;
    //     }
    //     cout << endl;
    
    // }
}