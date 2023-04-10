#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get number
    long number = get_long("Number: ");

    // Calculate checksum :
    long variable = number / 10;
    long sum = 0;

    // Multiply every other digit by 2
    while (variable > 0)
    {
        if ((variable % 10) * 2 < 10)
        {
            sum += (variable % 10) * 2;
        }
        else
        {
            sum += ((variable % 10) * 2) % 10;
            sum += ((variable % 10) * 2) / 10;
        }
        // Diviser par 100 car on va de deux en deux
        variable /= 100;
    }

    // Make the sum with the remaining digits
    long variable_2 = number;
    while (variable_2 > 0)
    {
        sum += variable_2 % 10;
        variable_2 /= 100;
    }

    // Find the other characteristics

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Find the digit number
        long variable_3 = number;
        int digit_number;
        for (digit_number = 1; variable_3 > 10; variable_3 /= 10)
        {
            digit_number += 1;
        }

        // Find the first digit
        long variable_4 = number;
        for (int j = 0; j < digit_number - 1; j++)
        {
            variable_4 /= 10;
        }


        // Find the first two digits
        long variable_5 = number;
        while (variable_5 >= 100)
        {
            variable_5 /= 10;
        }

        // Check the conditions for each card and print the result

        if ((digit_number == 15) && (variable_5 == 34 || variable_5 == 37))
        {
            printf("AMEX\n");
        }
        else if ((variable_4 == 4) && (digit_number == 13 || digit_number == 16))
        {
            printf("VISA\n");
        }
        else if ((digit_number = 16) && (variable_5 == 51 || variable_5 == 52 || variable_5 == 53 || variable_5 == 54 || variable_5 == 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }

}