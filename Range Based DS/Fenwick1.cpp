#include <bits/stdc++.h>
using namespace std; 

// Point Update + Prefix Sum Query

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // add val to index i
    void update(int i, long long val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    // prefix sum [1..i]
    long long query(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

    // sum on [l..r]
    long long query(int l, int r) {
        return query(r) - query(l-1);
    }
};
