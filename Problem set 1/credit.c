#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n;
    int x, counter = 0, sum1 = 0, sum2 = 0,sum,jud,flag=0;//x 为获取余数，counter计算一共多少位数，sum1 和 sum2 代表偶数位和奇数位和，sum总和
    int digit[100];//为了判断信用卡前两位数，用了个数组
    n = get_long("Number: ");
    do
    {
        x = n % 10;
        digit[counter]=x;
        counter++;
        if (counter % 2 == 0)//根据奇偶位数进行不同的加减
        {
            if (x < 5)
            {
                sum1 += x * 2;
            }
            else
                sum1 += (x * 2) % 10 + 1;//因为乘出来是两位数的话要逐位加，十位上不会超过1
        }
        else
            sum2 += x;
        n /= 10;
    } while (n > 0);
    sum = sum1 + sum2;
    jud=digit[counter-1]*10+digit[counter-2];//这一步有点多余，可以在数组里直接访问前两位数，为了让后面的条件看起来简洁
    if (sum % 10 == 0)
    {
        if (counter == 15)
        {
            if(jud==34 ||jud==37)
            {
                 printf("AMEX\n");
                 flag=1;
            }
        }
        if (x == 4)
        {
            if(counter==13||counter==16)
            {
                 printf("VISA\n");
                 flag=1;
            }
        }
        if (counter == 16 && digit[counter - 2] <= 5 && x==5)
        {
            printf("MASTERCARD\n");
            flag=1;
        }
        if(flag == 0)
        {
            printf("INVALID\n");
        }
    }
    else
        printf("INVALID\n");
}
