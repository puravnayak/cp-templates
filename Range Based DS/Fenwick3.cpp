#include <bits/stdc++.h>
using namespace std; 

// Range Update + Range Sum Query

struct Fenwick {
    int n;
    vector<long long> B1, B2;

    Fenwick(int n) : n(n), B1(n+1,0), B2(n+1,0) {}

    void add(vector<long long>& B, int idx, long long val) {
        for (; idx <= n; idx += idx & -idx)
            B[idx] += val;
    }

    void update(int l, int r, long long val) {
        add(B1, l, val);
        add(B1, r+1, -val);
        add(B2, l, val*(l-1));
        add(B2, r+1, -val*r);
    }

    long long sum(vector<long long>& B, int idx) {
        long long res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += B[idx];
        return res;
    }

    long long prefix_sum(int idx) {
        return sum(B1, idx)*idx - sum(B2, idx);
    }

    long long query(int l, int r) {
        return prefix_sum(r) - prefix_sum(l-1);
    }
};
