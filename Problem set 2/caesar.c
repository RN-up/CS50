#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int only_digit(int argc, string argv);
string encipher(string plain, int k);

int main(int argc, string argv[])
{
    if (argc == 2 && only_digit(argc, argv[1]) == 1)
    {
        string plain = get_string("plaintext:  ");
        int k = atoi(argv[1]), n = strlen(plain), index_p, index_c;
        char cipher[n];
        for (int i = 0; i < n; i++)
        {
            if (isalpha(plain[i]))
            {
                if (isupper(plain[i]))
                {
                    index_p = plain[i] - 65;
                    index_c = (index_p + k) % 26;
                    cipher[i] = index_c + 65;
                }
                else
                {
                    index_p = plain[i] - 97;
                    index_c = (index_p + k) % 26;
                    cipher[i] = index_c + 97;
                }
            }
            else
                cipher[i] = plain[i];
        }
        printf("ciphertext: %s\n", cipher);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
int only_digit(int argc, string s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i]<'0'|| s[i]>'9')
        {
            break;
        }
    }
    if (i == strlen(s))
    {
        return 1;
    }
    else
        return 0;
}
