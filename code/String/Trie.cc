struct Trie {
    static const int K = 26;
    static const char BASE = 'a'; 
    struct Node {
        int nxt[K]{};  // {} zero-initializes the array
        int eow = 0, cnt = 0;
    };
    vector<Node> t;
    Trie() : t(1) {} // Initializes with root at index 0 

    //d = 1 for insert, d = -1 for erase
    void insert(const string& s, int d = 1) { 
        int u = 0;
        t[u].cnt += d;
        for (char c : s) {
            int v = c - BASE;
            if (!t[u].nxt[v]) {
                t[u].nxt[v] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[v];
            t[u].cnt += d;
        }
        t[u].eow += d;
    }
    
    int search(const string& s) { 
        int u = 0;
        for (char c : s) {
            int v = c - BASE;
            if (!t[u].nxt[v]) return 0;
            u = t[u].nxt[v];
        }
        return t[u].eow; 
    }
    
    int count_prefix(const string& s) {
        int u = 0;
        for (char c : s) {
            int v = c - BASE;
            if (!t[u].nxt[v]) return 0;
            u = t[u].nxt[v];
        }
        return t[u].cnt; 
    }
};