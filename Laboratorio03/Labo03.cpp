#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#include <time.h>

using namespace std;

int[] getArrRandomNumbers(int size);
int[] getArrPartitionOfRanks(int[] arr, int initial, int end);
int[] sumArrays(int[] arr1, int[] arr2, int size);

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size%100!=0){
    	cout<<"El numero de procesos es diferente de multiplo de 100."<<endl;
    	return EXIT_SUCCESS;
	}

    int root_rank = 0;
    int arr1[100],arr2[100], arrAux1[100/size], arrAux2[100/size], arrResul[100];
	
	int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 	
 	if(my_rank==root_rank){
 		arr1 = getArrRandomNumbers(100);
 		arr2 = getArrRandomNumbers(100);
 		arrAux1 = getArrRandomNumbers(arrAux1);
 		arrAux2 = getArrRandomNumbers(arrAux2);
 		MPI_Send(&arrAux1, 100/size, MPI_INT, 1, 0, MPI_COMM_WORLD);
 		MPI_Send(&arrAux2, 100/size, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}else{
		MPI_Recv(&arrAux1, 100/size, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
		MPI_Recv(&arrAux2, 100/size, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
        arrResul = sumArrays(arrAux1,arrAux2,100/size);
        printArray(arrResul,100/size);
	}
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}

int[] getArrRandomNumbers(int size){
	int num, i;
	int array[size]
    for(i = 0; i < size; i++){
    	num = 1 + rand() % (11 - 1);
        array[i] = num;
    }
    return array;
}

int[] getArrPartitionOfRanks(int[] arr, int initial, int end) {
	int i, array[end-initial];
	for(i = initial; i < end; i++){
    	array[i] = arr[i];
    }
    return array;
}

int[] sumArrays(int[] arr1, int[] arr2, int size) {
	int i, arrResul[size];
	for(i = 0; i < size; i++){
    	arrResul[i] = arr1[i] + arr2[i];
    }
    return arrResul;
}

void printArray(int[] arr, int size){
	int i;
	cout<<"Escribiendo vector...";
	for(i = 0; i < size; i++){
    	cout<<arr[i]<<" - ";
    }
    cout<<endl;
}
