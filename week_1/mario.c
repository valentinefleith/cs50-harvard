#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt for input
    int height ;
    do
    {
        height = get_int("Height : ");
    }
    while (height < 1 || height > 8);

    // print pyramid
    // for each row : print spaces, print hashes, print gap, print right hashes
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= (height - i); j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }


}