/*Author: Dr. Neerja Mhaskar
* Course: CS 3SH3 - Operating Systems
* Traversing a directory to output the files/directory names in it.
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <dirent.h>

int dir_traverse(char * dirname){
	DIR *dir;
	struct dirent *ent;
	char * name;
	dir = opendir(dirname); //open directory
	
	if ( dir != NULL) {
	   printf("\n\nFiles/Directories in '%s'\n", dirname);
	   printf("-------------------------------------------------\n");	
	  
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		name = ent->d_name;
		if(strcmp(ent->d_name, ".") ==0 || strcmp(ent->d_name, "..") ==0){
		    //ignore
		}
		else {
		    printf ("\n%s\n", name);			    
		}
	  }
	  printf("\n");	
	  closedir(dir); //close directory
	} 
	else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
}

int main ( int argc, char * argv[])
{
	char * filen = argv[1];	
	if (argc != 2) {
		fprintf(stderr,"Usage: ./a.out <input file>\n");
		return -1;
    	}	
	
	return dir_traverse(filen);
}
