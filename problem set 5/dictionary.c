// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// the number of words
int counter = 0, indexN;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for (node *cursor = table[hash(word)]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    indexN = (int)toupper(word[0]);
    indexN -= 65;
    return indexN;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char *dic_words = malloc(LENGTH);
    if (dic_words == NULL)
    {
        return false;
    }
    FILE *text = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
    }

    // scan the file
    while (fscanf(text, "%s", dic_words) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, dic_words);

        // insert the new node at the beginning of the hashtable
        hash(dic_words);
        n->next = table[indexN];
        table[indexN] = n;

        // update the counter
        counter++;
    }

    // free the memory
    free(dic_words);
    fclose(text);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp;
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
