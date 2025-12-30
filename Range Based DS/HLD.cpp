#include <bits/stdc++.h>
using namespace std;

static const int N = 2e5 + 5;
static const int LG = 18;


struct Node {
    long long mx;
    Node() : mx(-1e9) {}
    Node(long long v) : mx(v) {}

    void merge(const Node &l, const Node &r) {
        mx = max(l.mx, r.mx);
    }
};

struct Update {
    long long add;
    Update() : add(0) {}
    Update(long long v) : add(v) {}

    void apply(Node &node, int l, int r) const {
        node.mx += add;
    }

    void combine(const Update &other, int l, int r) {
        add += other.add;
    }
};

template <typename Node, typename Update>
struct LazySGT {
    int n;
    vector<Node> tree;
    vector<Update> lazy;
    vector<bool> has_lazy;

    LazySGT(int n) : n(n) {
        tree.assign(4 * n, Node());
        lazy.assign(4 * n, Update());
        has_lazy.assign(4 * n, false);
    }

    void apply(int idx, int l, int r, const Update &u) {
        u.apply(tree[idx], l, r);
        if (l != r) {
            if (has_lazy[idx]) lazy[idx].combine(u, l, r);
            else lazy[idx] = u, has_lazy[idx] = true;
        }
    }

    void push(int idx, int l, int r) {
        if (!has_lazy[idx]) return;
        int mid = (l + r) >> 1;
        apply(idx << 1, l, mid, lazy[idx]);
        apply(idx << 1 | 1, mid + 1, r, lazy[idx]);
        lazy[idx] = Update();
        has_lazy[idx] = false;
    }

    void pull(int idx) {
        tree[idx].merge(tree[idx << 1], tree[idx << 1 | 1]);
    }

    void update(int idx, int l, int r, int ql, int qr, const Update &u) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(idx, l, r, u);
            return;
        }
        push(idx, l, r);
        int mid = (l + r) >> 1;
        update(idx << 1, l, mid, ql, qr, u);
        update(idx << 1 | 1, mid + 1, r, ql, qr, u);
        pull(idx);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node();
        if (ql <= l && r <= qr) return tree[idx];
        push(idx, l, r);
        int mid = (l + r) >> 1;
        Node L = query(idx << 1, l, mid, ql, qr);
        Node R = query(idx << 1 | 1, mid + 1, r, ql, qr);
        Node res;
        res.merge(L, R);
        return res;
    }

    void range_add(int l, int r, long long v) {
        update(1, 1, n, l, r, Update(v));
    }

    long long range_max(int l, int r) {
        return query(1, 1, n, l, r).mx;
    }
};

vector<int> g[N];
int parent[N][LG + 1], depth[N], sz[N];
int head[N], st[N], en[N];
int timer = 0;
int n;

void dfs(int u, int p) {
    parent[u][0] = p;
    depth[u] = depth[p] + 1;
    sz[u] = 1;

    for (int i = 1; i <= LG; i++)
        parent[u][i] = parent[parent[u][i - 1]][i - 1];

    int heavy = -1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (heavy == -1 || sz[v] > sz[heavy])
            heavy = v;
    }

    if (heavy != -1) {
        auto it = find(g[u].begin(), g[u].end(), heavy);
        swap(g[u][0], *it);
    }
}

void dfs_hld(int u, int p) {
    st[u] = ++timer;
    for (int v : g[u]) {
        if (v == p) continue;
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v, u);
    }
    en[u] = timer;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int k = LG; k >= 0; k--)
        if (depth[parent[u][k]] >= depth[v])
            u = parent[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) {
        if (parent[u][k] != parent[v][k]) {
            u = parent[u][k];
            v = parent[v][k];
        }
    }
    return parent[u][0];
}

LazySGT<Node, Update> *seg;

long long query_vertex(int u) {
    return seg->range_max(st[u], st[u]);
}

void update_vertex(int u, long long val) {
    seg->range_add(st[u], st[u], val);
}

long long query_subtree(int u) {
    return seg->range_max(st[u], en[u]);
}

void update_subtree(int u, long long val) {
    seg->range_add(st[u], en[u], val);
}

long long query_up(int u, int v) {
    long long ans = LLONG_MIN;
    while (head[u] != head[v]) {
        ans = max(ans, seg->range_max(st[head[u]], st[u]));
        u = parent[head[u]][0];
    }
    ans = max(ans, seg->range_max(st[v], st[u]));
    return ans;
}

long long query_path(int u, int v) {
    int L = lca(u, v);
    return max(query_up(u, L), query_up(v, L));
}

void update_path(int u, int v, long long val) {
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        seg->range_add(st[head[u]], st[u], val);
        u = parent[head[u]][0];
    }
    if (depth[u] > depth[v]) swap(u, v);
    seg->range_add(st[u], st[v], val);
}

void init()
{
    timer=0;
    dfs(1, 0);
    head[1] = 1;
    dfs_hld(1, 0);
    seg = new LazySGT<Node, Update>(n);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    init();   

    for(int i=1;i<=n;i++)
        update_vertex(i,1e9);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        if (s == "add") {
            int t1, val;
            cin >> t1 >> val;
            update_subtree(t1, val);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query_path(a, b) << '\n';
        }
    }
    return 0;
}

