#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true); 
    isPrime[0] = isPrime[1] = false; 

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

bool isPrime(int n)
{
    if(n<=1)
        return 0;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}

vector<int>factors(int n)
{
    vector<int>f;
    for(int i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            f.push_back(i);
            if(i*i!=n)
                f.push_back(n/i);
        }
    }
    sort(f.begin(),f.end());
    return f;
}

const int MAXN=1e5;

vector<int> spf(MAXN);

// to compute smallest prime for each number
void sievec() {
    for (int i = 1; i < MAXN; i++)
        spf[i] = i;

    for (int i = 2; i * i < MAXN; i++) {
        if (spf[i] == i) { 
            for (int j = i * i; j < MAXN; j += i) {
                if (spf[j] == j) 
                    spf[j] = i;
            }
        }
    }
}

int countPrimeFactors(int n) {
    int count = 0;
    while (n != 1) {
        count++;
        n /= spf[n]; 
    }
    return count;
}
