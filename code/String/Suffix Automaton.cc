// Big alphabet: `int nxt[26]` -> `map<int, int> nxt`
// & `!t[p].nxt[c]` -> `!t[p].nxt.count(c)` everywhere!
struct SAM {
  struct Node {
    int nxt[26]{}, lnk = -1, len = 0, focc = -1;
    long long cnt = 0, dp = -1;
  };
  vector<Node> t; int lst = 0; vector<int> ord;
  SAM(int n = 0) {
    t.clear(); ord.clear();
    t.reserve(2 * n + 1); t.emplace_back(); lst = 0;
  }
  void add(char ch, int idx = -1) {
    int c = ch - 'a', p = lst;
    if (t[p].nxt[c]) {
      int q = t[p].nxt[c];
      if (t[p].len + 1 == t[q].len) lst = q;
      else {
        int clone = t.size(); t.push_back(t[q]);
        t[clone].len = t[p].len + 1; t[clone].cnt = 0;
        while (p != -1 && t[p].nxt[c] == q) {
          t[p].nxt[c] = clone; p = t[p].lnk;
        }
        t[q].lnk = clone; lst = clone;
      }
      t[lst].cnt++; return;
    }
    int cur = t.size(); t.emplace_back();
    t[cur].len = t[p].len + 1; t[cur].focc = idx;
    // ONLY pure prefix nodes get a 1!
    // (Set 0 if only unique counts matter in Gen. SAM)
    t[cur].cnt = 1; lst = cur;
    while (p != -1 && !t[p].nxt[c]) {
      t[p].nxt[c] = cur; p = t[p].lnk;
    }
    if (p == -1) { t[cur].lnk = 0; return; }
    int q = t[p].nxt[c];
    if (t[p].len + 1 == t[q].len) {
      t[cur].lnk = q; return;
    }
    int clone = t.size(); t.push_back(t[q]);
    t[clone].len = t[p].len + 1;
    t[clone].cnt = 0; // Cloned nodes get 0!
    while (p != -1 && t[p].nxt[c] == q) {
      t[p].nxt[c] = clone; p = t[p].lnk;
    }
    t[q].lnk = t[cur].lnk = clone;
  }
  void build(const string& s) {
    for (int i = 0; i < s.size(); i++) add(s[i], i);
  }
  // Topo Sort + Suffix link Tree DP (freq of state)
  void count() {
    int n = t.size(); ord.resize(n);
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) c[t[i].len]++;
    for (int i = 1; i <= n; i++) c[i] += c[i - 1];
    for (int i = 0; i < n; i++) ord[--c[t[i].len]] = i;
    for (int i = n - 1; i > 0; i--)
      t[t[ord[i]].lnk].cnt += t[ord[i]].cnt;
  }
  void reset_dp() { for (auto& node : t) node.dp = -1; }
  // DAG DP (paths for K-th substring / total substrs)
  // MAKE SURE to call count() first if dist == false!
  long long calc_dp(int u, bool dist) {
    if (t[u].dp != -1) return t[u].dp;
    t[u].dp = dist ? 1 : t[u].cnt; // Base case
    for (int i = 0; i < 26; i++) if (t[u].nxt[i])
      t[u].dp += calc_dp(t[u].nxt[i], dist);
    return t[u].dp;
  }
  // Find lexicographically K-th Substring
  string get_kth(long long k, bool dist) {
    if (t[0].dp == -1) calc_dp(0, dist);
    if (k > t[0].dp - (dist ? 1 : t[0].cnt))
      return "-1";
    string ans = ""; kth(0, k, ans, dist); return ans;
  }
  void kth(int u, long long& k, string& ans,
           bool dist) {
    if (k <= 0) return;
    for (int i = 0; i < 26; i++) {
      int v = t[u].nxt[i];
      if (!v) continue;
      if (k > t[v].dp) { k -= t[v].dp; continue; }
      ans += (char)('a' + i);
      k -= (dist ? 1 : t[v].cnt);
      kth(v, k, ans, dist); return;
    }
  }
};
/* --- NODE VARIABLES (BUCKETS) ---
len : Max string len in bucket (Min = t[lnk].len + 1)
focc: 0-based end pos of FIRST occ (first in endpos)
cnt : Exact Occ(VALID AFTER count()), distinct occ: 1
lnk : Suffix link (longest suffix in other bucket)
nxt : DAWG transitions (edges). dp : DAG DP memo state.
lst : Node ID of the whole string built so far
Longest at u: s.substr(t[u].focc-t[u].len+1, t[u].len)
--- 1. BUILD & GENERALIZED SAM (GSA) ---
SAM sa(s.size()); sa.build(s);
GSA: for(auto& str: strs) {sa.lst = 0; sa.build(str);}
--- 2. COUNTING & K-TH (Always call sa.count()!) ---
Distinct Subs : sa.calc_dp(0, 1) - 1 // -1: empty str
Total Subs    : sa.calc_dp(0, 0) - t[0].cnt
K-th Distinct : sa.get_kth(K, 1)
K-th Total    : sa.get_kth(K, 0)
--- 3. PATTERN MATCH (Is Substr? / Occ / First Idx) ---
int u = 0; bool ok = true; // count() first for cnt
for(char c : p) if(!(u = sa.t[u].nxt[c-'a']))
  { ok = false; break; }
// If ok: Occurrences = sa.t[u].cnt,
// First Occ Idx (0-based) = sa.t[u].focc-p.size()+1
--- 4. LONGEST COMMON SUBSTRING (LCS of s1 & s2) ---
SAM sa(s1.size()); sa.build(s1);
int u = 0, l = 0, max_l = 0, best_pos = 0;
for(int i = 0; i < s2.size(); i++) {
  int c = s2[i] - 'a';
  while(u != -1 && !sa.t[u].nxt[c])
    { u = sa.t[u].lnk; l = u==-1 ? 0 : sa.t[u].len; }
  if(u != -1) {
    u = sa.t[u].nxt[c];
    if(++l > max_l) { max_l = l; best_pos = i; }
  } else { u = 0; l = 0; }
} // LCS = s2.substr(best_pos - max_l + 1, max_l)
--- 5. SMALLEST CYCLIC SHIFT (Lexicographically) ---
SAM sa(2 * s.size()); sa.build(s + s);
int u = 0; string ans = "";
for(int i = 0; i < s.size(); i++)
  for(int c = 0; c < 26; c++) if(sa.t[u].nxt[c])
    {ans += (char)(c+'a'); u = sa.t[u].nxt[c]; break;}
LCP of suffixes = LCS of prefixes in reversed string */
