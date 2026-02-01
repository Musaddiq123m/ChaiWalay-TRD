#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

int fact[N], invFact[N];

int binExp(int base, int exp, int mod = MOD) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (1LL * result * base) % mod;
        base = (1LL * base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int modInverse(int a, int mod = MOD) {
    return binExp(a, mod - 2, mod);
}

void precomputeFactorials(int mod = MOD) {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = (1LL * fact[i - 1] * i) % mod;

    invFact[N - 1] = modInverse(fact[N - 1], mod);
    for (int i = N - 2; i >= 0; i--)
        invFact[i] = (1LL * invFact[i + 1] * (i + 1)) % mod;
}

int nCr(int n, int r, int mod = MOD) {
    if (r > n || r < 0) return 0;
    return (1LL * fact[n] * invFact[r] % mod * invFact[n - r]) % mod;
}

int nPr(int n, int r, int mod = MOD) {
    if (r > n || r < 0) return 0;
    return (1LL * fact[n] * invFact[n - r]) % mod;
}
