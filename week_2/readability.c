// Calculate the approximate grade level needed to comprehend some text using Coleman-Liau index


#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = "";
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) < 1);

    float L = count_letters(text) * 100.0 / count_words(text);
    float s = count_sentences(text) * 100.0 / count_words(text);
    float index = 0.0588 * L - 0.296 * s - 15.8;
    index = round(index);
    
    if (index >= 1 && index < 16)
    {
        printf("Grade %.f\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}

// Get the number of letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Get the number of words
int count_words(string text)
{
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words;
}

// Get the number of sentences
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
            while (ispunct(text[i]))
            {
                i++;
            }
        }
    }
    return sentences;
}
