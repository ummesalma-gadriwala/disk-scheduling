// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
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
	for (i = 0; i < 20; i++) {
		printf("%d,", requests[i]);
	}
	printf("\n");

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
		count++;
	}
	printf("%d\n", copy[0]);
	totalHeadMovements += abs(currentPosition - copy[0]);
	printf("SSTF - Total head movements = %d\n", totalHeadMovements);
}

void scan(int requests[], int headPosition, char* headDirection) {
	printf("SCAN DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	int rightIndex = -5;
	int leftIndex = -5;
	int i;

/*	
	if (headPosition < requests[0]) {
		//YOUR CODE
//head moves from 8 to 0, then from 0 to 293 printing all the requests i the way
		return;
	}
	
	if (headPosition >= requests[TOTAL_REQUESTS-1]) {
		//YOUR CODE
		return;
	}
*/
	
	for (i = 0; i < TOTAL_REQUESTS-1; i++) {
		//printf("%d ", i);
		if (requests[i] <= headPosition && headPosition <= requests[i+1]) {
			leftIndex = i;
			rightIndex = i+1;
			break;
		}
	}
	if (leftIndex == -5 || rightIndex == -5){
		if (headPosition <= requests[0]){
			leftIndex = 0;
			rightIndex = 0;
		}
		if (headPosition >= requests[TOTAL_REQUESTS-1]){
			leftIndex = requests[TOTAL_REQUESTS-1];
			rightIndex = requests[TOTAL_REQUESTS-1];
		}
	}
	//printf("\nl %d, r %d\n", leftIndex, rightIndex);
	if (strcmp(headDirection, "LEFT") == 0) {
		totalHeadMovements = abs(headPosition - 0) + abs(0 - requests[TOTAL_REQUESTS-1]);
		// grant the request I'm at first!
		if (requests[rightIndex] == headPosition) {
			leftIndex += 1;
			rightIndex += 1;
		}
		for (i = leftIndex; i >= 0; i--)
			printf("%d, ", requests[i]);
		for (i = rightIndex; i < TOTAL_REQUESTS-1; i++) 
			printf("%d, ", requests[i]);
		printf("%d\n", requests[TOTAL_REQUESTS-1]);
	} else {
		totalHeadMovements = abs(299 - headPosition) + abs(299 - requests[0]);
		for (i = rightIndex; i < TOTAL_REQUESTS; i++)
			printf("%d, ", requests[i]);
		for (i = leftIndex; i > 0; i--)
			printf("%d, ", requests[i]);
		printf("%d\n", requests[0]);
		
	}
	printf("SCAN - Total head movements = %d\n", totalHeadMovements);
}

void cscan(int requests[], int headPosition, char* headDirection) {
	printf("C-SCAN DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	int rightIndex;
	int leftIndex;
	int i;
	
	if (headPosition <= requests[0]) {
		//YOUR CODE
		return;
	}
	
	if (headPosition >= requests[TOTAL_REQUESTS-1]) {
		//YOUR CODE
		return;
	}
	
	for (i = 1; i < TOTAL_REQUESTS; i++) {
		if (requests[i] <= headPosition && headPosition <= requests[i+1]) {
			leftIndex = i;
			rightIndex = i+1;
			break;
		}
	}

	if (strcmp(headDirection, "LEFT") == 0) {
		// grant the request I'm at first!
		if (requests[rightIndex] == headPosition) {
			leftIndex += 1;
			rightIndex += 1;
		}
		totalHeadMovements = abs(headPosition-0) + 299 + abs(299-requests[rightIndex]);
		for (i = leftIndex; i >= 0; i--)
			printf("%d, ", requests[i]);
		for (i = TOTAL_REQUESTS-1; i > rightIndex; i--) 
			printf("%d, ", requests[i]);
		printf("%d\n", requests[rightIndex]);
	} else {
		totalHeadMovements = abs(headPosition-299) + 299 + abs(0-requests[leftIndex]);
		for (i = rightIndex; i < TOTAL_REQUESTS; i++)
			printf("%d, ", requests[i]);
		for (i = 0; i < leftIndex; i++)
			printf("%d, ", requests[i]);
		printf("%d\n", requests[leftIndex]);
	}
	
	printf("C-SCAN - Total head movements = %d\n", totalHeadMovements);
}

void look(int requests[], int headPosition, char* headDirection) {
	printf("LOOK DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	int rightIndex;
	int leftIndex;
	int i;
	
	if (headPosition <= requests[0]) {
		//YOUR CODE
		return;
	}
	
	if (headPosition >= requests[TOTAL_REQUESTS-1]) {
		//YOUR CODE
		return;
	}
	
	for (i = 1; i < TOTAL_REQUESTS; i++) {
		if (requests[i] <= headPosition && headPosition <= requests[i+1]) {
			leftIndex = i;
			rightIndex = i+1;
			break;
		}
	}
	
	if (strcmp(headDirection, "LEFT") == 0) {
		totalHeadMovements = abs(headPosition - requests[0]) + abs(requests[0] - requests[TOTAL_REQUESTS-1]);
		// grant the request I'm at first!
		if (requests[rightIndex] == headPosition) {
			leftIndex += 1;
			rightIndex += 1;
		}
		for (i = leftIndex; i >= 0; i--)
			printf("%d, ", requests[i]);
		for (i = rightIndex; i < TOTAL_REQUESTS-1; i++) 
			printf("%d, ", requests[i]);
		printf("%d\n", requests[TOTAL_REQUESTS-1]);
	} else { // RIGHT
		totalHeadMovements = abs(requests[TOTAL_REQUESTS-1] - headPosition) + abs(requests[TOTAL_REQUESTS-1] - requests[0]);
		for (i = rightIndex; i < TOTAL_REQUESTS; i++)
			printf("%d, ", requests[i]);
		for (i = leftIndex; i > 0; i--)
			printf("%d, ", requests[i]);
		printf("%d\n", requests[0]);
		
	}
	
	printf("LOOK - Total head movements = %d\n", totalHeadMovements);
}

void clook(int requests[], int headPosition, char* headDirection) {
	printf("C-LOOK DISK SCHEDULING ALGORITHM:\n");
	
	int totalHeadMovements = 0;
	int rightIndex;
	int leftIndex;
	int i;
	
	if (headPosition <= requests[0]) {
		//YOUR CODE
		return;
	}
	
	if (headPosition >= requests[TOTAL_REQUESTS-1]) {
		//YOUR CODE
		return;
	}
	
	for (i = 1; i < TOTAL_REQUESTS; i++) {
		if (requests[i] <= headPosition && headPosition <= requests[i+1]) {
			leftIndex = i;
			rightIndex = i+1;
			break;
		}
	}
	
	if (strcmp(headDirection, "LEFT") == 0) {
		// grant the request I'm at first!
		if (requests[rightIndex] == headPosition) {
			leftIndex += 1;
			rightIndex += 1;
		}
		totalHeadMovements = abs(headPosition - requests[0]) + 
							 abs(requests[0]-requests[TOTAL_REQUESTS-1]) + 
							 abs(requests[rightIndex] - requests[TOTAL_REQUESTS-1]);
		
		for (i = leftIndex; i >= 0; i--)
			printf("%d, ", requests[i]);
		for (i = TOTAL_REQUESTS-1; i > rightIndex; i--) 
			printf("%d, ", requests[i]);
		printf("%d\n", requests[rightIndex]);
	} else { //RIGHT
		totalHeadMovements = abs(requests[TOTAL_REQUESTS-1] - headPosition) + 
							 abs(requests[TOTAL_REQUESTS-1] - requests[0]) + 
							 abs(requests[0] - requests[leftIndex]);
		for (i = rightIndex; i < TOTAL_REQUESTS; i++)
			printf("%d, ", requests[i]);
		for (i = 0; i < leftIndex; i++)
			printf("%d, ", requests[i]);
		printf("%d\n", requests[leftIndex]);
	}
	
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
	
	//fcfs(requests, headPosition);
	//sstf(requests, headPosition);
	scan(sortedRequests, headPosition, headDirection);
	//cscan(sortedRequests, headPosition, headDirection);
	//look(sortedRequests, headPosition, headDirection);
	//clook(sortedRequests, headPosition, headDirection);

	munmap(mmapfptr, MEMORY_SIZE);
	return 0;
}
