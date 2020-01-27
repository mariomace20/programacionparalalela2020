#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
  
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  float u_i = rank*rank;
  float v_i = log(rank+1.0);

  float tmp = u_i * v_i;

  float result;
  MPI_Reduce(&tmp, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "El valor es: "<<result<<endl;
  }
  
  MPI_Finalize();
  
  return 0;
}
