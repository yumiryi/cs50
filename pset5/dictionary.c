// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

int hash_index = 0;
int hash_index_check = 0;
int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 702;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // Find hash index
    hash_index_check = hash(word);
    // if hash index is empty, return false
    if (table[hash_index_check] == NULL)
    {
        return false;
    }
    // Goes to first node at index in hash table
    node *cursor = table[hash_index_check];
    // Iterates until end of linked list
    while (cursor != NULL)
    {
        // If word is found, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        // If word doesn't match, move to next node
        cursor = cursor->next;
    }
    // If word is not in hash table, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO

    int h = 0;
    // Hashes words without apostrophes in first two characters
    if (word[1] != 39)
    {
        h = (((tolower(word[0]) - 97) * 26) + (tolower(word[1]) - 97));
    }
    // Hashes words with apostrophes in first two characters
    else if (word[1] == 39)
    {
        h = ((tolower(word[0]) - 97) + 676);
    }

    if (h > N)
    {
        h = h % N;
    }
    else
    {
        return h;
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];

    // Opens dictionary file
    FILE *dictfile = fopen(dictionary, "r");
    if (dictfile == NULL)
    {
        printf("Cannot open dictionary file.\n");
        return false;
    }

    // Read entries from dictionary
    while (fscanf(dictfile, "%s", word) != EOF)
    {
        // Increase word count
        count++;

        // Allocate memory to node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory allocation failed.\n");
            return false;
        }
        // Copy dictionary entry into word field of node
        strcpy(n->word, word);

        // Use hash function to find hash table index
        hash_index = hash(word);

        // Insert word into empty hash table
        if (table[hash_index] == NULL)
        {
            table[hash_index] = n;
            n->next = NULL;
        }
        // Insert word into populated hash table
        else
        {
            n->next = table[hash_index];
            table[hash_index] = n;
        }
    }
    fclose(dictfile);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Returns word count
    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursorf = table[i];
        node *cursorb = cursorf;
        while (cursorf != NULL)
        {
            cursorf = cursorf->next;
            free(cursorb);
            cursorb = cursorf;
        }
    }
    return true;
}
