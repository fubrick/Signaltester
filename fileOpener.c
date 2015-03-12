#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXBUFFERSIZE 128
#define MAXFILENAME 30

void pauseProg(char const *str) {
	printf("%s\nPress enter to continue...\n", str);
	getchar();
}

int main(int argc, char const *argv[])
{
	int file_desc, i, ret;
	int size = 0;
	char fileName[MAXFILENAME];
	char input[MAXBUFFERSIZE];
	char test;


	if (argc > 1)
	{
		strcpy(fileName, argv[1]);
		printf("Opening file %s\n", fileName);
		file_desc = open(fileName, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR  | S_IRGRP | S_IROTH);
		//printf("fides: %d\n", file_desc);
		if (file_desc < 0)
		{
			printf("Error:%d could not create file\n", file_desc);
			exit(file_desc);
		}
		pauseProg("varify that file has opened");
		ret = lseek(file_desc, 0, SEEK_CUR);
		printf("%d\n", ret);

		if (argc > 2)
		{
			strcpy(input, argv[2]);
			strcat(input, " ");
			for (i = 3; i < argc; i++)
			{
				strcat(input, argv[i]);
				strcat(input, " ");
			}
			strcat(input, "\n");
			size = strlen(input);

			if (write(file_desc, input, size) != size )
			{
				printf("Error! Could not write to file. \n");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		printf("Usage: ./fileOpener <FILENAME> <INPUT STRING>\n");
		return 0;
	}

	return 0;
}