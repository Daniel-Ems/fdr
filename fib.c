#include<stdio.h>
#include<openssl/bn.h>
int main()
{
    
    BIGNUM *first = BN_new(); 
    BIGNUM *second = BN_new(); 
    int c = 0;
    
    BN_dec2bn(&first, "0");
    BN_dec2bn(&second, "1");
    int n = 300;
    
    for (c = 0 ; c <= n ; c++)
    {
        if ( c <= 1)
        {
            if(c == 1)
            {
                BN_dec2bn(&first, "1");
            }
            else
            {
                BN_dec2bn(&first, "0");
            }
        }
        else
        {
            BN_add(first, first, second);
            BN_swap(first, second);
        }
    }
        char *buffer = BN_bn2dec(first);  
        printf("%s\n", buffer);

    BN_free(first);
    BN_free(second);
    free(buffer);
}
