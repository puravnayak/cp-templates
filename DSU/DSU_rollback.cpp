
struct RollbackDSU {
    int n;
    vector<int> parent, sz;
    int components;

    vector<array<int,3>> history;

    RollbackDSU(int n) : n(n), parent(n+1), sz(n+1,1), components(n) {
        for(int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        while(parent[x] != x)
            x = parent[x];
        return x;
    }

    void persist() {
        history.push_back({2, -1, -1}); 
    }

    void rollback() {
        while(true) {
            auto cur = history.back();
            history.pop_back();

            if(cur[0] == 2) break; 

            if(cur[0] == 0) {
                parent[cur[1]] = cur[2];
                components++;
            } else {
                sz[cur[1]] = cur[2];
            }
        }
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b) return;

        if(sz[a] < sz[b]) swap(a, b);

        history.push_back({0, b, parent[b]});
        history.push_back({1, a, sz[a]});

        parent[b] = a;
        sz[a] += sz[b];
        components--;
    }
};