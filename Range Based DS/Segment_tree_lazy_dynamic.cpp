struct Node {
    long long val;
    Node *left, *right;
    Node(long long v = 0) : val(v), left(nullptr), right(nullptr) {}
};

struct DynamicSegTree {
    long long L, R;   // range [L, R]
    Node* root;

    DynamicSegTree(long long l, long long r) : L(l), R(r) {
        root = new Node();
    }

    void update(Node* &node, long long l, long long r, long long pos, long long value) {
        if(!node) node = new Node();
        if(l == r) {
            node->val += value;   // or = value
            return;
        }
        long long mid = (l + r) >> 1;
        if(pos <= mid)
            update(node->left, l, mid, pos, value);
        else
            update(node->right, mid + 1, r, pos, value);

        long long lv = node->left ? node->left->val : 0;
        long long rv = node->right ? node->right->val : 0;
        node->val = lv + rv;
    }

    long long query(Node* node, long long l, long long r, long long ql, long long qr) {
        if(!node || ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return node->val;
        long long mid = (l + r) >> 1;
        return query(node->left, l, mid, ql, qr)
             + query(node->right, mid + 1, r, ql, qr);
    }

    // public wrappers
    void update(long long pos, long long value) {
        update(root, L, R, pos, value);
    }

    long long query(long long l, long long r) {
        return query(root, L, R, l, r);
    }
};
