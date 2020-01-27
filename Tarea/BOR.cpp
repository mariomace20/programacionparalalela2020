#include <bits/stdc++.h>
#include <mpi.h>
#include <unistd.h>
using namespace std;

int main (int argc, char* argv[]) {
    int size, rank, n=200, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *arraySend = new int[n];
    int *arrayRecv = new int[n];
    for(i=0; i<n; i++) arr_send[i] = 0;
    for(i=rank; i<n; i+=size) arr_send[i] = 1;

    MPI_Allreduce(arraySend, arrayRecv, n, MPI_INT, MPI_BOR, MPI_COMM_WORLD);

    if(taskid == 0){
        for(i=0; i<n; i++) 
			cout<<arrayRecv[i];
        cout<<endl;
    }

    MPI_Finalize();
    return 0;
}
