struct AhoCorasick {
    static const int K = 26;
    static const char BASE = 'a';
    
    struct Node {
        int nxt[K]{}; // Auto-initializes to 0
        int fail = 0, cnt = 0;
    };
    vector<Node> t;
    AhoCorasick() : t(1) {} // Root is at index 0
    
    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int v = c - BASE;
            if (!t[u].nxt[v]) {
                t[u].nxt[v] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[v];
        }
        t[u].cnt++; // Or store pattern ID here if needed 
    }
    
    void build() {
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (t[0].nxt[i]) q.push(t[0].nxt[i]);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            
            // Accumulate matches from proper suffixes (fail links)
            t[u].cnt += t[t[u].fail].cnt; 
            
            for (int i = 0; i < K; i++) {
                if (t[u].nxt[i]) {
                    t[t[u].nxt[i]].fail = t[t[u].fail].nxt[i];
                    q.push(t[u].nxt[i]);
                } else {
                    // Virtual DFA edges for O(1) transitions
                    t[u].nxt[i] = t[t[u].fail].nxt[i];
                }
            }
        }
    }
    
    long long count_matches(const string& text) {
        long long matches = 0;
        int u = 0;
        for (char c : text) {
            u = t[u].nxt[c - BASE];
            matches += t[u].cnt;
        }
        return matches;
    }
};