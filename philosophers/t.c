#include <stdio.h>
int main()
{
    int num = 123;
    int mod = 0,s=0;
    int T[8]= {0,2,4,8,16,32,64,128};
    int i = 0;
    char arr[8];
    while (i < 8)
    {
        mod = num % 2;
        arr[i] = mod;
        num = num / 2;
        i++;
    }
    while (--i >= 0)
    {
        if(arr[i] == 1){
            s+=T[i];
        }
        printf("%d",arr[i]);
    }
    printf("\n%d\n",s);
}