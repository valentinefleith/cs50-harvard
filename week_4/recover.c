#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Errors checking

    if (argc != 2)
    {
        printf("Improper usage.\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("No such file found.\n");
        return 1;
    }

    // Recover JPEGS

    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int jpg_count = 0;
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_count == 0)
            {
                sprintf(filename, "%03i.jpg", jpg_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                jpg_count++;
            }

            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                jpg_count++;
            }
        }

        else if (jpg_count > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }

    }
    fclose(img);
    fclose(card);

}
