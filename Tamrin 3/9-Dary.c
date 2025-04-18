// 403100043
#include <stdio.h>
#include <math.h>
int main()
{
    long long m, p, lock[27];
    int q ,n;
    scanf("%d %d %lld %lld", &n, &q, &p, &m);
    for (int i = 0; i < 26; i++)
    {
        scanf("%lld ", &lock[i]);
    }
    char s[1000];
    for (int i = 0; i < n; i++){
        scanf("%c ", &s[i]);
        }

    int l, r;
    long long hash_input, hash,pow;
    for (int t = 0; t < q; t++)
    {
        pow = 1;
        hash = 0;
        scanf("%d %d %lld", &l, &r, &hash_input);
        l--;r--;
        int lc = l;
        if (l > r) {
            for(int i = 0; i <= lc-r ;i++ ){
                hash = (hash + ((lock[s[l--]-97]*pow) % m)) % m;
                pow = (pow * p) % m;
            }
        }else {
            for(int i = 0; i <= r-lc ;i++) {
                hash = (hash + ((lock[s[l++]-97]*pow) % m)) % m;
                pow = (pow * p)%m;

            }
        }
        if(hash == hash_input)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
