struct KMP {
     string s;//must declare s before n
    int n; vector<int> pi;
    KMP(const string& _s) : s(_s), n(s.size()), pi(n, 0) {
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
    }
    vector<vector<int>> build_nxt(int A = 26, char base = 'a') {
        vector<vector<int>> nxt(n + 1, vector<int>(A, 0));
        for (int i = 0; i <= n; i++) for (int c = 0; c < A; c++)
            if (i < n && s[i] - base == c) nxt[i][c] = i + 1;
            else if (i > 0) nxt[i][c] = nxt[pi[i - 1]][c];
        return nxt;
    }
};
// MATCH: KMP k(pat + "#" + txt); int m = pat.size();
// for(int i = m+1; i < k.n; i++) if(k.pi[i] == m) { /* Match starts at txt[i - 2*m] */ }
// STR DP: auto nxt = KMP(pat).build_nxt(); // states: 0 to m. (st == m means fully matched)
// dp[idx+1][nxt[st][c]] += dp[idx][st]; // If avoiding pat: ensure nxt[st][c] != m