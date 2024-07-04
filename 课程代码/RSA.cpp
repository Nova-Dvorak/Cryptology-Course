#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <math.h>

#define MAX_STR_LEN 1024

/*补全函数：1、求最大公因数*/
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

/*补全函数：1、判断一个数是否为质数*/
int is_prime(int n)
{
    if(n <= 1)
        return 0;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
            return 0;
    return 1;
}

/*补全函数：扩展欧几里得算法*/
int exgcd(int a, int b, int *x, int *y)
{
    if(b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    int r = exgcd(b, a % b, y, x);
    *y -= a / b * (*x);
    return r;
}

/*补全函数：2.2、计算模数的逆元*/
int mod_reverse(int a, int n)
{
    int x, y;
    int r = exgcd(a, n, &x, &y);
    if(r == 1)
        return (x % n + n) % n;
    return -1;
}

/*补全函数：2、生成RSA公钥和私钥，代码中φ(N)用L代替
2.1、n=p*q
2.2、求d，满足e*d mod L = 1
*/
void gen_rsa_keys(int p, int q, int e, int *n, int *d)
{
    *n = p * q;
    int L = (p - 1) * (q - 1);
    *d = mod_reverse(e, L);
}

/*补全函数：RSA加解密*/
int rsa(int x, int key, int n)
{
    int res = 1;
    while(key)
    {
        if(key & 1)
            res = (res * x) % n;
        x = (x * x) % n;
        key >>= 1;
    }
    return res;
}

/*补全函数：3、RSA加密*/
void rsa_encrypt(int m, int n, int e, int *c)
{
    *c = rsa(m, e, n);
}

/*补全函数：4、RSA解密*/
void rsa_decrypt(int c, int d, int n, int *m)
{
    *m = rsa(c, d, n);
}

/*补全函数：6、RSA签名*/
int rsa_sign(int m, int d, int n) // m is hash, d is private key, n is public key
{
    return rsa(m, d, n);
}

/*补全函数：7、RSA验签*/
int rsa_verify(int m, int s, int e, int n)
{
    return m == rsa(s, e, n);
}

/*补全main()函数：输入p、q、e及明文消息，输出公私钥,加解密结果,明文hash,签名结果以及验签结果
1、判断e、p、q是否为质数且e是否满足与（p-1）*（q-1）互质
2、生成公私钥
3、RSA加密
4、RSA解密
5、计算消息的哈希值
6、RSA签名
7、RSA验签
*/
int main()
{
    int p, q, e, n, d, c, s;
    unsigned char m[MAX_STR_LEN];
    int encrypted[MAX_STR_LEN], decrypted[MAX_STR_LEN];
    printf("Input p, q, e and message: ");
    scanf("%d%d%d", &p, &q, &e);
    scanf("%s", m);
    if(!is_prime(p) || !is_prime(q) || gcd(e, (p - 1) * (q - 1)) != 1)
    {
        printf("Invalid input\n");
        return 0;
    }
    gen_rsa_keys(p, q, e, &n, &d);
    for(int i = 0; m[i]; i++)
        rsa_encrypt(m[i], n, e, &encrypted[i]);
    for(int i = 0; m[i]; i++)
        rsa_decrypt(encrypted[i], d, n, &decrypted[i]);
    int hash = 0;
    for(int i = 0; m[i]; i++)
        hash = (hash * 131 + m[i]) % n;
    s = rsa_sign(hash, d, n);
    int verify = rsa_verify(hash, s, e, n);
    printf("Public key: (%d, %d)\n", n, e);
    printf("Private key: %d\n", d);
    printf("Encrypted message: ");
    for(int i = 0; m[i]; i++)
        printf("%d ", encrypted[i]);
    printf("\nDecrypted message: ");
    for(int i = 0; m[i]; i++)
        printf("%c", (char)decrypted[i]);
    printf("\nHash: %d\n", hash);
    printf("Signature: %d\n", s);
    printf(verify ? "verify succeed" : "verify failed");
    return 0;
}
