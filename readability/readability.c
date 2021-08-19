#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float letters = 0;
float words = 0;
float sentences = 0;
float L;
float S;
int index;

void count_letters(char x);
void count_words(char x);
void count_sentences(char x);

int main(void)
{
    // Prompts user for text
    string text = get_string("Text: ");

    // Counts letters, words, and sentences in text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        count_letters(text[i]);

        count_words(text[i]);

        count_sentences(text[i]);
    }

    // Calculates average number of letters per 100 words
    L = (letters * 100) / (words + 1);

    // Calculates average number of sentences per 100 words
    S = (sentences * 100) / (words + 1);

    // Calculates Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8);

    // Prints grade level of text
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counts number of letters
void count_letters(char x)
{
    if (isalpha(x))
    {
        letters++;
    }
}

// Counts number of words
void count_words(char x)
{
    if (x == 32)
    {
        words++;
    }
}

// Counts number of sentences
void count_sentences(char x)
{
    if (x == 33 || x == 46 || x == 63)
    {
        sentences++;
    }
}