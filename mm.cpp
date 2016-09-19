#include <iostream>
#include <stdlib.h>

#define MAX_VAL 10

int *matrixgenerate(int dimension){
	int* matrix = new int[dimension*dimension];
	for(int i=0; i<dimension * dimension; i++){
		matrix[i] = rand()%MAX_VAL;
	}
	return matrix;
}

void matrixdisplay(int *matrix, int dimension){
	for(int i=0; i<dimension*dimension; i++){
		std::cout<<matrix[i]<<"	";
		if(((i+1)%dimension)==0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

int* matrixInit(int dimension){
	int *matrix = new int[dimension*dimension];
	for(int i=0;i<dimension*dimension;i++)
		matrix[i] = 0;
	return matrix;
}

int main(){

	// generate two matrix
	int matrix_size;
	std::cout<<"Input the size of matrix!"<<std::endl;
	std::cin>>matrix_size;

	int *m1 = matrixgenerate(matrix_size);
	int *m2 = matrixgenerate(matrix_size);
	int *m = matrixInit(matrix_size);


	std::cout<<"***** Matrix Display for m1 *****"<<std::endl;
	matrixdisplay(m1,matrix_size);

	std::cout<<"***** Matrix Display for m2 *****"<<std::endl;
	matrixdisplay(m2,matrix_size);

	for(int i=0; i<matrix_size; i++){
		for(int j=i+1; j<matrix_size; j++){
			std::swap(m2[i*matrix_size+j], m2[j*matrix_size+i]);
		}
	}

	std::cout<<"***** Matrix Display for transposed m2 *****"<<std::endl;
	matrixdisplay(m2, matrix_size);


	std::cout<<"***** Matrix Display for m *****"<<std::endl;
	matrixdisplay(m, matrix_size);

	int thread_cnt;
	std::cout<<"Input the number of threads:"<<std::endl;
	std::cin>>thread_cnt;
	std::cout<<"The number of threads "<<thread_cnt<<std::endl;

	int size = matrix_size/thread_cnt;
	int reminder = matrix_size%thread_cnt;
	if(reminder != 0){
		std::cout<<"Wrong input, run again!"<<std::endl;
		exit(0);
	}

	#pragma omp parallel for num_threads(thread_cnt)
	for(int i=0; i<matrix_size;i++){
		for(int j=0; j<matrix_size;j++){
			for(int k=0;k<matrix_size;k++)
				m[i*matrix_size+j] += m1[i*matrix_size+k]*m2[j*matrix_size+k];
		}
	}

	matrixdisplay(m, matrix_size);
	return 0;
}
