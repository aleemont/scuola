#include<stdio.h>

unsigned int sequence(void){
	FILE *file;
	unsigned int n;
	file = fopen("number.txt", "r+");
	if(file == NULL)
		return 0;
	if(fscanf(file, "%u", &n) != 1){
		fclose(file);
		return 0;
	}
	++n;
	fseek(file, 0, SEEK_SET);
	fprintf(file,"%u",n);
	fclose(file);

	return n;
}
