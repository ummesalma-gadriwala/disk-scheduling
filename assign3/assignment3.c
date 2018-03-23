// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h> /*for mmap() function*/
#include <string.h> /*for memcpy function*/
#include <fcntl.h> /*for file descriptors*/

#define INT_SIZE 4
#define TOTAL_REQUESTS 20
#define MEMORY_SIZE TOTAL_REQUESTS*INT_SIZE

// insertion sort
void sort(int requests[]) {
	int i, j, k;
	for (i = 1; i < TOTAL_REQUESTS; i++) {
		j = i-1;
		k = requests[i];
		while (k < requests[j] && j >= 0) {
			requests[j+1] = requests[j];
			j = j - 1;
		}
		requests[j+1] = k;
	}
}

// fcfs algorithm, prints order of requests and total head movements
void fcfs(int requests[], int headPosition) {
	printf("FCFS DISK SCHEDULING ALGORITHM:\n");
	int i;
	int totalHeadMovements = 0;
	int currentPosition = headPosition;
	for (i = 0; i < TOTAL_REQUESTS - 1; i++) {
		printf("%d, ", requests[i]);
		totalHeadMovements += abs(requests[i] - currentPosition);
		currentPosition = requests[i];
	}
	printf("%d\n", requests[TOTAL_REQUESTS-1]);
	totalHeadMovements += abs(requests[i] - currentPosition);
	printf("FCFS - Total head movements = %d\n", totalHeadMovements);
}

void sstf(int requests[], int headPosition) {
	printf("SSTF DISK SCHEDULING ALGORITHM:\n");
	int i;
	int totalHeadMovements = 0;
	int copy[TOTAL_REQUESTS];
	// copy requests
	for (i = 0; i < TOTAL_REQUESTS; i++) {
		copy[i] = requests[i];
	}
	int currentPosition = headPosition;
	int count = 0;
	int closestRequest, requestIndex;
	while (count < TOTAL_REQUESTS-1) {
		closestRequest = copy[0];
		requestIndex = 0;
		for (i = 0; i < TOTAL_REQUESTS-count; i++) {
			if (abs(currentPosition - closestRequest) > abs(currentPosition - copy[i])) {
				closestRequest = copy[i];
				requestIndex = i;
			}
		}
		totalHeadMovements += abs(currentPosition - closestRequest);
		currentPosition = closestRequest;
		copy[requestIndex] = copy[TOTAL_REQUESTS-count-1];
		copy[TOTAL_REQUESTS-count-1] = closestRequest;
		printf("%d, ", currentPosition);
		//for (i = 0; i < 20; i++)
			//printf("%d,", copy[i]);
		count++;
	}
	printf("%d\n", copy[0]);
	totalHeadMovements += abs(currentPosition - copy[0]);
	printf("SSTF - Total head movements = %d\n", totalHeadMovements);
}

void scan(int requests[]) {
	printf("SCAN DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	
	printf("SCAN - Total head movements = %d\n", totalHeadMovements);
}

void cscan(int requests[]) {
	printf("C-SCAN DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	
	printf("C-SCAN - Total head movements = %d\n", totalHeadMovements);
}

void look(int requests[]) {
	printf("LOOK DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	
	printf("LOOK - Total head movements = %d\n", totalHeadMovements);
}

void clook(int requests[]) {
	printf("C-LOOK DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	
	printf("C-LOOK - Total head movements = %d\n", totalHeadMovements);
}

int main(int argc, char *argv[]) {

	// input argument count check
	if (argc != 3) {
		fprintf(stderr, "usage: assignment3 <headPosition int> <headDirection string> \n");
		return -1;
	}
	
	int totalRequests = 0;
	int headPosition = atoi(argv[1]);
	char* headDirection = argv[2];
	
	// read requests from requests.bin and store in integer array
	int requests[TOTAL_REQUESTS];
	int i; // loop counter
	int mmapfile_fd = open("request.bin", O_RDONLY);
	signed char *mmapfptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);
	for(i = 0; i < TOTAL_REQUESTS; i++){
		memcpy(requests + i, mmapfptr + 4*i, INT_SIZE);
	}
	close(mmapfile_fd);
	
	// sort requests
	int sortedRequests[TOTAL_REQUESTS];
	// copy requests to sortedRequests
	for (i = 0; i < TOTAL_REQUESTS; i++) {
		sortedRequests[i] = requests[i];
	}
	sort(sortedRequests);
	
	printf("Total requests = %d\n", TOTAL_REQUESTS);
	printf("Initial Head Position: %d\n", headPosition);
	printf("Direction of Head: %s\n", headDirection);
	
	fcfs(requests, headPosition);
	sstf(requests, headPosition);
	scan(sortedRequests);
	cscan(sortedRequests);
	look(sortedRequests);
	clook(sortedRequests);

	munmap(mmapfptr, MEMORY_SIZE);
	return 0;
}
