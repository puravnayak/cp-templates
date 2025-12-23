#include <bits/stdc++.h>
using namespace std; 

#define int long long
#define endl '\n' 

int MOD=1e9+7;

int mod_expo(int base, int exp, int mod) {
    int res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int modInverse(int a, int m) {
    return mod_expo(a, m - 2, m);
}

vector<int> fact, inv_fact;

void precompute_factorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[n] = mod_expo(fact[n], MOD - 2, MOD); // Fermat's Little Theorem for modular inverse
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

// Function to compute nCr % MOD
int nCr(int n, int r) {
    if (r > n || r < 0)
        return 0;
    return (fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD) % MOD;
}
