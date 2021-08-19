#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
BYTE buffer[512];
FILE *output;
int imgcount = 0;
char filename[8];

int main(int argc, char *argv[])
{
    // Ensures correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Reads raw file
    FILE *raw = fopen(argv[1], "r");

    // Ensures raw file can be read
    if (raw == NULL)
    {
        printf("%s cannot be opened for reading.\n", argv[1]);
        return 1;
    }

    // Iterate over entire raw file in chunks of 512 bytes
    while (fread(buffer, 512, 1, raw))
    {
        // If jpg identifier is found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If image is already open, close it
            if (imgcount > 0)
            {
                fclose(output);
            }

            // Name new jpg
            sprintf(filename, "%03i.jpg", imgcount);
            output = fopen(filename, "w");

            // Increase jpg count
            imgcount++;
        }
        // If jpg identifier is not found
        else
        {
            // If first jpg hasn't been found, skip jpg creation
            if (imgcount == 0)
            {
                continue;
            }
        }

        // Create new jpg
        fwrite(buffer, 512, 1, output);
    }

    // Cleanup
    fclose(raw);
    fclose(output);
}
