#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]){
    
    int result = 0;
    int root_rank = 0;
 	int size = 0;
    int my_rank;
    
 	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Reduce(&my_rank, &result, 1, MPI_INT, MPI_MAXLOC, root_rank, MPI_COMM_WORLD);
 
    if(my_rank == root_rank){
        cout<<"El valor max local es: "<<result;
    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;
}
