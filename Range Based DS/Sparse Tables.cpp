template<typename T>
struct SparseTable {
    int n, K;
    vector<vector<T>> st;
    vector<int> lg;
    T func(T a, T b) {
        return __gcd(a, b);       // change
    }

    SparseTable(const vector<T> &arr) {
        n = arr.size();
        if(n==0)
            return;
        K = __lg(n) + 1;
        st.assign(K, vector<T>(n));
        lg.resize(n + 1);

        for (int i = 0; i < n; i++)
            st[0][i] = arr[i];

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i/2] + 1;

        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = func(st[k-1][i], st[k-1][i + (1 << (k-1))]);
            }
        }
    }

    T query(int l, int r) {
        if(n==0)
            return 0;
        if(l>r)
            return 0;
        int k = lg[r - l + 1];
        return func(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
