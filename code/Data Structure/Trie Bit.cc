struct BitTrie {
    static const int BT = 62; // Use 30 for numbers <= 10^9
    struct Node {
        int nxt[2]{}; // {} zero-initializes the array
        int cnt = 0;
    };
    vector<Node> t;
    BitTrie() : t(1) {} // Initializes with root at index 0

    //d = 1 for insert, d = -1 for remove
    void insert(long long x, int d = 1) { 
        int u = 0;
        t[u].cnt += d; // Track total elements at root
        for (int i = BT - 1; i >= 0; i--) {
            int v = (x >> i) & 1;
            if (!t[u].nxt[v]) {
                t[u].nxt[v] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[v];
            t[u].cnt += d;
        }
    }
    
    long long query(long long x) {
        if (!t[0].cnt) return 0;
        int u = 0;
        long long mx = 0;
        for (int i = BT - 1; i >= 0; i--) {
            int r = (x >> i) & 1;
            if (t[u].nxt[r ^ 1] && t[t[u].nxt[r ^ 1]].cnt > 0) {
                mx |= (1LL << i);
                u = t[u].nxt[r ^ 1];
            } else {
                u = t[u].nxt[r];
            }
        }
        return mx;
    }
};