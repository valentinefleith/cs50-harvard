// Write a program that inplements a substitution cipher in a command-line argument
// ./ substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
// plaintext : hello, world
// ciphertext : jrssb, ybwsp


#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string encipher(string plain_text, string key);

int main(int argc, string argv[])
{
    // Check key length
    if (argc != 2)
    {
        printf("Usage : ./substitution KEY\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for non-alphabetic characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check for repetitions
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (toupper(argv[1][i]) == toupper(argv[1][j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string text = get_string("plaintext:  ");
    printf("ciphertext: %s\n", encipher(text, argv[1]));

}


string encipher(string text, string key)
{
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Eliminate non-alphabetic characters
        if (isalpha(text[i]) == 0)
        {
            continue;
        }
        else
        {
            // Find the index of the text letter in letters[]
            for (int j = 0, m = strlen(letters); j < m; j++)
            {
                if (islower(text[i]))
                {
                    if (text[i] == tolower(letters[j]))
                    {
                        // Replace with the new letter
                        text[i] = tolower(key[j]);
                        break;
                    }
                }
                else
                {
                    if (text[i] == toupper(letters[j]))
                    {
                        // Replace with the new letter
                        text[i] = toupper(key[j]);
                        break;
                    }
                }

            }
        }
    }
    return text;
}