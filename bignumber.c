#include <openssl/bn.h>
#include <openssl/bio.h>
#include <stdio.h>

int main(void)
{
    BIGNUM *num = BN_new();
       
    char str[] = "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    BN_dec2bn(&num, str);
    char *hexval = BN_bn2hex(num);
    printf("%s\n", hexval);
    /*
    BIO *out = BIO_new_fp(stdout, BIO_NOCLOSE);
    BN_print(out, num);
   */
    BN_free(num);
    free(hexval);
}  
