const int N = 2e6 + 9;
const int M1 = 1e9 + 7, M2 = 1e9 + 9, B1 = 137, B2 = 277;
pair<int, int> pw[N];

void init_hash() {
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i].first = 1LL * pw[i - 1].first * B1 % M1;
        pw[i].second = 1LL * pw[i - 1].second * B2 % M2;
    }
}
struct Hash {
    string s;
    vector<pair<int, int>> hs;
    Hash(const string& _s) : s(_s) {
        hs.assign(s.size() + 1, {0, 0});
        for (int i = 0; i < s.size(); i++) {
            hs[i + 1].first = (1LL * hs[i].first * B1 + s[i]) % M1;
            hs[i + 1].second = (1LL * hs[i].second * B2 + s[i]) % M2;
        }
    }
    pair<int, int> get(int l, int r) { 
        int h1 = (hs[r + 1].first - 1LL * hs[l].first * pw[r - l + 1].first % M1 + M1) % M1;
        int h2 = (hs[r + 1].second - 1LL * hs[l].second * pw[r - l + 1].second % M2 + M2) % M2;
        return {h1, h2};
    }
    int lcp(int i1, int j1, int i2, int j2) {
        int l = 1, r = min(j1 - i1 + 1, j2 - i2 + 1), ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (get(i1, i1 + mid - 1) == get(i2, i2 + mid - 1)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }
    int compare(int i1, int j1, int i2, int j2) {
        int l = lcp(i1, j1, i2, j2);
        int len1 = j1 - i1 + 1, len2 = j2 - i2 + 1;
        if (l == len1 && l == len2) return 0;
        if (l == len1) return -1;
        if (l == len2) return 1;
        return s[i1 + l] < s[i2 + l] ? -1 : 1;
    }
};