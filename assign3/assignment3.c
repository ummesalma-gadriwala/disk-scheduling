// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h> /*for mmap() function*/
#include <string.h> /*for memcpy function*/
#include <fcntl.h> /*for file descriptors*/

#define INT_SIZE 4
#define NUMBER_OF_REQUESTS 20
#define MEMORY_SIZE NUMBER_OF_REQUESTS*INT_SIZE

// insertion sort, returns sorted array
void sort(int requests[]) {
	int i, j, k;
	for (i = 1; i < NUMBER_OF_REQUESTS; i++) {
		j = i-1;
		k = requests[i];
		while (k < requests[j] && j >= 0) {
			requests[j+1] = requests[j];
			j = j - 1;
		}
		requests[j+1] = k;
	}
}

int main(int argc, char *argv[]) {

	// input argument count check
	if (argc != 3) {
		fprintf(stderr, "usage: assignment3 <headPosition int> <headDirection string> \n");
		return -1;
	}
	
	int headPosition = atoi(argv[1]);
	char* headDirection = argv[2];
	
	// read requests from requests.bin and store in integer array
	int requests[NUMBER_OF_REQUESTS];
	int i; // loop counter
	int mmapfile_fd = open("request.bin", O_RDONLY);
	signed char *mmapfptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);
	for(i = 0; i < NUMBER_OF_REQUESTS; i++){
		memcpy(requests + i, mmapfptr + 4*i, INT_SIZE);
	}
	close(mmapfile_fd);
	
	// sort requests
	int sortedRequests[NUMBER_OF_REQUESTS];
	// copy requests to sortedRequests
	for (i = 0; i < NUMBER_OF_REQUESTS; i++) {
		sortedRequests[i] = requests[i];
	}
	sort(sortedRequests);
	for (i = 0; i < NUMBER_OF_REQUESTS; i++)
		printf("r: %d, s: %d\n", requests[i], sortedRequests[i]);

	munmap(mmapfptr, MEMORY_SIZE);
	return 0;
}
