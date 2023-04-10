// Generate all prime numbers in a range specified by the user

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // always print 2
    if (number == 2)
    {
        return true;
    }
    else
    {
        for (int j = 2; j < number; j++)
        {
            // if not prime number
            if (number % j == 0)
            {
                return false;
            }
            // if not not prime number but still not prime number for sure
            else if (j < number - 1)
            {
                continue;
            }
            // if prime number
            else
            {
                return true;
            }
        }
    }
    return false;
}
