#include <bits/stdc++.h>
using namespace std; 

// Range Update + Point Query

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // add val to range [l..r]
    void update(int l, int r, long long val) {
        for (; l <= n; l += l & -l)
            bit[l] += val;
        r++;
        for (; r <= n; r += r & -r)
            bit[r] -= val;
    }

    // point query at i
    long long query(int i) {
        long long res = 0;
        for (; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }
};
