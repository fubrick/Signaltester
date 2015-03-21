#include <fcntl.h>
#include <unistd.h>
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
    int file_desc, i;
    int size = 0;
    char fileName[MAXFILENAME];
    char input[MAXBUFFERSIZE];
    mode_t mode = S_IRUSR | S_IWUSR  | S_IRGRP | S_IROTH;

    if (argc > 1)
    {
        strcpy(fileName, argv[1]);
        printf("Opening file %s\n", fileName);
        file_desc = open(fileName, O_RDWR | O_CREAT | O_APPEND, mode);
        
        if (file_desc < 0)
        {
            printf("Error:%d could not create file\n", file_desc);
            exit(file_desc);
        }
        pauseProg("varify that file has opened");

        if (argc > 2)
        {
            if (strlen(argv[2]) < (MAXBUFFERSIZE + 1)) {
                strcpy(input, argv[2]);
                strcat(input, " ");
            }
            for (i = 3; i < argc; i++) // loop through arguments and add to input string
            {
                if ((strlen(argv[i]) + size + 1) < MAXBUFFERSIZE) //argument fits in buffer
                {
                    strcat(input, argv[i]);
                    strcat(input, " ");
                    size = strlen(input);
                }
                else // input exceeds buffer size, wrtie input to file and continue with next line
                {
                    size = strlen(input);
                    printf("reached max buffersize %d %s\n", size,argv[i]);
                    strcat(input, "\n");
                    if (write(file_desc, input, size) != size) 
                    {
                        printf("Error! Could not write to file.\n");
                        exit(EXIT_FAILURE);
                    }
                    strcpy(input, argv[i]); //start new input string
                    strcat(input, " ");
                    size = strlen(input); //reset size
                }
            }
            strcat(input, "\n");
            size = strlen(input);
            
            // write remaining input to file
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
