#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    double L, S, I;
    int index;
    L = (double)count_letters(text) *100/ count_words(text);//if the result is not convered to the "double", it will make mistakes.
    S = (double)count_sentences(text) *100 / count_words(text);
    I = 0.0588 * L - 0.296 * S - 15.8;
    index = round(I);

    printf("%d %d %d\n",count_letters(text),count_words(text),count_sentences(text));
    printf("%f %f %f\n",L,S,I);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index >= 1 && index < 16)
    {
        printf("Grade %d\n", index);
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

}

int count_letters(string text)
{
    int n = strlen(text), counter=0;


    for (int i = 0; i < n; i++)
    {
      if (isalpha(text[i]))//if the return value is not 0
        {
             counter++;
        }
    }
    return counter;
}
int count_words(string text)
{
    int n = strlen(text), counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 32)
            counter++;
    }
    return counter + 1;
}

int count_sentences(string text)
{
    int n = strlen(text), counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
            counter++;
    }
    return counter;
}
