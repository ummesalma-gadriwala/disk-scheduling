#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h> /*Contains the stat structure definition*/
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: lab10b11a11b <filename string> \n");
		return -1;
	}
	
	char* fileName = argv[1];
	struct stat fileAttributes; // variable of type stat
	if (stat(fileName, &fileAttributes) < 0)
		return -1;
		
	printf("Printing %s attributes:\n", fileName);
	printf(" Inode: %d\n", fileAttributes.st_ino);
	printf(" Size(in bytes): %d\n", fileAttributes.st_size);
	printf(" Blocks: %d\n", fileAttributes.st_blocks);
	printf(" File Permissions: %d\n", fileAttributes.st_mode);
	printf(" File Permissions: \t");
    printf( (S_ISDIR(fileAttributes.st_mode)) ? "d" : "-");
    printf( (fileAttributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileAttributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileAttributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileAttributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileAttributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileAttributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileAttributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileAttributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileAttributes.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
	printf(" Uid: %d\n", fileAttributes.st_uid);
	printf(" Time of last access: %d\n", fileAttributes.st_atime);
	printf(" Time of last data modification: %d\n", fileAttributes.st_mtime);
	printf(" Last Status Change time: %d\n", fileAttributes.st_ctime);
	
	return 0;
}
