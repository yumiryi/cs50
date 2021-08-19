#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int digits = 0;
string plaintext;
int key;

int main(int argc, string argv[])
{
    // Verifies that there is only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // Verifies that command-line argument is numeric
            if (isdigit(argv[1][i]))
            {
                digits++;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // Converts key from string to int
        key = atoi(argv[1]);

        // Prompts user for plaintext
        if (digits == strlen(argv[1]))
        {
            plaintext = get_string("plaintext:  ");
        }
    }

    // Prints ciphertext
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Encrypts uppercase characters
            if (isupper(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 65) + key) % 26) + 65);
            }
            // Encrypts lowercase characters
            else if (islower(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 97) + key) % 26) + 97);
            }
        }
        // Prints non-alpha characters
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
}