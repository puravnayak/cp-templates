#include <bits/stdc++.h>
using namespace std; 

struct Node1 {
    long long val;

    Node1(long long v = 0) : val(v) {}

    inline static Node1 merge(const Node1 &a, const Node1 &b) {
        return Node1(a.val + b.val);  // sum
    }
};

struct PSTNode {
    PSTNode *l, *r;
    Node1 data;
    PSTNode(Node1 v = Node1(), PSTNode *L = nullptr, PSTNode *R = nullptr)
        : data(v), l(L), r(R) {}
};

struct Update1 {
    long long val;
    Update1(long long v = 0){
        val=v;
    }
    inline void apply(Node1 &a){
        a.val = val;
    }
};

PSTNode* build(int start, int end, const vector<long long> &arr){
    if(start == end)
        return new PSTNode(Node1(arr[start]));

    int mid = (start + end) / 2;
    PSTNode *left = build(start, mid, arr);
    PSTNode *right = build(mid + 1, end, arr);

    Node1 v = Node1::merge(left->data, right->data);
    return new PSTNode(v, left, right);
}

PSTNode* update(PSTNode *root, int start, int end, int idx, Update1 &u){
    if(start == end){
        Node1 v = root->data;
        u.apply(v);
        return new PSTNode(v);
    }

    int mid = (start + end) / 2;

    PSTNode *newLeft = root->l;
    PSTNode *newRight = root->r;

    if(idx <= mid)
        newLeft = update(root->l, start, mid, idx, u);
    else
        newRight = update(root->r, mid+1, end, idx, u);

    Node1 v = Node1::merge(newLeft->data, newRight->data);
    return new PSTNode(v, newLeft, newRight);
}

Node1 query(PSTNode *root, int start, int end, int l, int r){
    if(start > r || end < l)
        return Node1(0);

    if(start >= l && end <= r)
        return root->data;

    int mid = (start + end) / 2;
    Node1 left = query(root->l, start, mid, l, r);
    Node1 right = query(root->r, mid+1, end, l, r);
    return Node1::merge(left, right);
}

struct PersistentSegTree {
    int n;
    vector<PSTNode*> version;
    
    PersistentSegTree(int n, vector<long long> &arr){
        this->n = n;
        version.push_back(build(0, n-1, arr));
    }

    void make_update(int ver, int idx, long long value){
        Update1 u(value);
        version.push_back(update(version[ver], 0, n-1, idx, u));
    }

    Node1 make_query(int ver, int l, int r){
        return query(version[ver], 0, n-1, l, r);
    }
};
