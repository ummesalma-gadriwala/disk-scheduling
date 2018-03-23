// Tasnim Noshin
// Umme Salma Gadriwala

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 4
#define NUMBER_OF_REQUESTS 300

int main(int argc, char *argv[]) {

	// input argument count check
	if (argc != 3) {
		fprintf(stderr, "usage: assignment3 <headPosition int> <headDirection string> \n");
		return -1;
	}
	
	int headPosition = atoi(argv[1]);
	char* headDirection = argv[2];
	printf("%d, %s\n", headPosition, headDirection);
	
	// read requests from requests.bin and store in integer array
	int requests[NUMBER_OF_REQUESTS];
	int i = 0;
	char buff[BUFFER_SIZE]; // for reading from file
	
	FILE *fptr = fopen("request.bin", "rb");
	while (1) {
		if (fread(buff, sizeof(int), 1, fptr) < 1) {
			break;
		}
		printf("%d\n",buff);
		requests[i] = atoi(buff);
		printf("here %d %d\n", atoi(buff),i);
		i++;
	}
	fclose(fptr);

	
	return 0;
}
