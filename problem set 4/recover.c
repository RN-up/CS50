#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // ensure valid input
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // open the file and ensure it is valid
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // searching the beginning of JPEGs
    BYTE buffer[BLOCK_SIZE];
    char JPEG_name[8];
    int counter = 0;
    FILE *img = NULL;
    while (fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //when counter!=0, start a new file
            if(counter > 0)
            {
                fclose(img);
            }
            sprintf(JPEG_name, "%03i.jpg", counter);
            img = fopen(JPEG_name, "w");
            fwrite(&buffer, BLOCK_SIZE, 1, img);
            counter++;
        }
        // to continue write the img before finding next JPEG
        else if(counter > 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }
    // finally, close all the file
    fclose(file);
    fclose(img);
    return 0;
}
