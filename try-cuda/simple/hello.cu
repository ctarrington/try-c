#include<stdio.h>
#include<stdlib.h>

__global__ void say_hello_gpu(void) {
	printf("hello from gpu %d, %d\n", threadIdx.x, blockIdx.x);
}

int main(void) {

	printf("hello from cpu\n");
	say_hello_gpu<<<2,2>>>();
	cudaDeviceSynchronize();
	return 0;
}
