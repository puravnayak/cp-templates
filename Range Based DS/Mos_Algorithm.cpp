#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Query {
    int l, r, idx;
};

int n, q;
vector<int> a;
int BLOCK;

void add(int idx) {
}

void remove_(int idx) {
}

bool cmp(const Query &A, const Query &B) {
    if (A.l / BLOCK != B.l / BLOCK)
        return A.l < B.l;
    return (A.l / BLOCK) & 1 ? A.r > B.r : A.r < B.r;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].idx = i;
    }

    BLOCK = sqrt(n);
    sort(queries.begin(), queries.end(), cmp);

    vector<int> ans(q);
    int L = 0, R = -1;

    for (auto &qr : queries) {
        while (L > qr.l) add(--L);
        while (R < qr.r) add(++R);
        while (L < qr.l) remove_(L++);
        while (R > qr.r) remove_(R--);
        ans[qr.idx] = 0;
    }

    for (int x : ans)
        cout << x << '\n';

    return 0;
}
