#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <math.h>

#define MAX_STR_LEN 1024

/*��ȫ������1�����������*/
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

/*��ȫ������1���ж�һ�����Ƿ�Ϊ����*/
int is_prime(int n)
{
    if(n <= 1)
        return 0;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
            return 0;
    return 1;
}

/*��ȫ��������չŷ������㷨*/
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

/*��ȫ������2.2������ģ������Ԫ*/
int mod_reverse(int a, int n)
{
    int x, y;
    int r = exgcd(a, n, &x, &y);
    if(r == 1)
        return (x % n + n) % n;
    return -1;
}

/*��ȫ������2������RSA��Կ��˽Կ�������Ц�(N)��L����
2.1��n=p*q
2.2����d������e*d mod L = 1
*/
void gen_rsa_keys(int p, int q, int e, int *n, int *d)
{
    *n = p * q;
    int L = (p - 1) * (q - 1);
    *d = mod_reverse(e, L);
}

/*��ȫ������RSA�ӽ���*/
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

/*��ȫ������3��RSA����*/
void rsa_encrypt(int m, int n, int e, int *c)
{
    *c = rsa(m, e, n);
}

/*��ȫ������4��RSA����*/
void rsa_decrypt(int c, int d, int n, int *m)
{
    *m = rsa(c, d, n);
}

/*��ȫ������6��RSAǩ��*/
int rsa_sign(int m, int d, int n) // m is hash, d is private key, n is public key
{
    return rsa(m, d, n);
}

/*��ȫ������7��RSA��ǩ*/
int rsa_verify(int m, int s, int e, int n)
{
    return m == rsa(s, e, n);
}

/*��ȫmain()����������p��q��e��������Ϣ�������˽Կ,�ӽ��ܽ��,����hash,ǩ������Լ���ǩ���
1���ж�e��p��q�Ƿ�Ϊ������e�Ƿ������루p-1��*��q-1������
2�����ɹ�˽Կ
3��RSA����
4��RSA����
5��������Ϣ�Ĺ�ϣֵ
6��RSAǩ��
7��RSA��ǩ
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
