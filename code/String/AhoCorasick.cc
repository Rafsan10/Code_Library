struct AhoCorasick {
    struct Node {
        int nxt[26]{};
        int fail = 0, term = 0, cnt = 0, id = -1;
    };
    vector<Node> t;
    AhoCorasick() : t(1) {} // Root is at index 0
    void insert(const string& s, int idx) {
        int u = 0;
        for (char c : s) {
            int v = c - 'a';
            if (!t[u].nxt[v]) {
                t[u].nxt[v] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[v];
        }
        t[u].cnt++;
        t[u].id = idx;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (t[0].nxt[i]) q.push(t[0].nxt[i]);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            t[u].cnt += t[t[u].fail].cnt;
            t[u].term = (t[t[u].fail].id != -1) ? t[u].fail : t[t[u].fail].term;
            for (int i = 0; i < 26; i++) {
                if (t[u].nxt[i]) {
                    t[t[u].nxt[i]].fail = t[t[u].fail].nxt[i];
                    q.push(t[u].nxt[i]);
                } else {
                    t[u].nxt[i] = t[t[u].fail].nxt[i];
                }
            }
        }
    }
    long long matches(const string& txt) {
        long long matches = 0;
        int u = 0;
        for(int i = 0;i<txt.size();i++){
            u = t[u].nxt[txt[i] - 'a'];
            matches += t[u].cnt;
            int cur = u;
            if(t[cur].id==-1)cur = t[cur].term;
            while(cur>0){
                //exact match
                cur = t[cur].term;
            }
        }
        return matches;
    }
};