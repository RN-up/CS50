include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
         n = get_int("Height: ");
    } while (n < 1 || n > 8);
    for (int i = 1; i <= n; i++) // i is the number of "row"
    {
        for (int j = 1; j <= n - i; j++) // j is the number of "space"
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++) // k is the number of "#"
        {
            printf("#");
        }
        printf("  ");
        for (int k2 = 1; k2 <= i; k2++) // k2 is the number of "#" on the right
        {
            printf("#");
        }
        printf("\n");
    }
}
