struct Trie {
    struct Node {
        int child[26];
        int end = 0;      
        int pref = 0;     
        Node() {
            memset(child, -1, sizeof child);
        }
    };

    vector<Node> t = {Node()}; 

    // Insert a word
    void insert(const string &s) {
        int cur = 0;
        for (char c : s) {
            int x = c - 'a';
            if (t[cur].child[x] == -1) {
                t[cur].child[x] = t.size();
                t.push_back(Node());
            }
            cur = t[cur].child[x];
            t[cur].pref++;            
        }
        t[cur].end++;
    }

    bool search(const string &s) {
        int cur = 0;
        for (char c : s) {
            int x = c - 'a';
            if (t[cur].child[x] == -1) return false;
            cur = t[cur].child[x];
        }
        return t[cur].end > 0;
    }

    int prefixCount(const string &s) {
        int cur = 0;
        for (char c : s) {
            int x = c - 'a';
            if (t[cur].child[x] == -1) return 0;
            cur = t[cur].child[x];
        }
        return t[cur].pref;
    }

    void erase(const string &s) {
        if (!search(s)) return;       
        int cur = 0;
        for (char c : s) {
            int x = c - 'a';
            cur = t[cur].child[x];
            t[cur].pref--;
        }
        t[cur].end--;
    }
};
