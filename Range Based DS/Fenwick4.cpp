#include <bits/stdc++.h>
using namespace std; 

// Fenwick for order statistics (k-th smallest)

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n+1, 0) {}

    void update(int i, int val) {
        for (; i <= n; i += i & -i)
            bit[i] += val;
    }

    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // find smallest idx such that prefix sum >= k
    int kth(int k) {
        int idx = 0;
        int mask = 1 << (31 - __builtin_clz(n)); // largest power-of-two <= n

        for (; mask > 0; mask >>= 1) {
            int next = idx + mask;
            if (next <= n && bit[next] < k) {
                k -= bit[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};
