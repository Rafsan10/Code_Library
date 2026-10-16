// Answer a query for EVERY subtree, O(n log n) (sack)
// Example: number of distinct colors in subtree of u.
// Edit add()/remove effect and the answer line only.
const int N = 2e5 + 5;
vector<int> g[N];
int col[N], sz[N], big[N], tin[N], tout[N], ver[N], T;
int cnt[N], distinct_, ans[N];
void dfs_sz(int u, int p) {
  sz[u] = 1; big[u] = -1;
  tin[u] = T; ver[T++] = u;
  for (int v : g[u]) if (v != p) {
    dfs_sz(v, u); sz[u] += sz[v];
    if (big[u] == -1 || sz[v] > sz[big[u]]) big[u] = v;
  }
  tout[u] = T; // subtree = ver[tin[u] .. tout[u]-1]
}
void add(int u, int d) { // d = +1 add u, -1 remove u
  if (d == 1 && cnt[col[u]]++ == 0) distinct_++;
  if (d == -1 && --cnt[col[u]] == 0) distinct_--;
}
void dfs(int u, int p, bool keep) {
  for (int v : g[u])
    if (v != p && v != big[u]) dfs(v, u, false);
  if (big[u] != -1) dfs(big[u], u, true); // keep heavy
  for (int v : g[u])
    if (v != p && v != big[u])
      for (int i = tin[v]; i < tout[v]; i++)
        add(ver[i], 1);
  add(u, 1);
  ans[u] = distinct_; // answer queries of u here
  if (!keep)
    for (int i = tin[u]; i < tout[u]; i++)
      add(ver[i], -1);
}
// dfs_sz(1, 0); dfs(1, 0, true);
// Small-to-large merging of sets: keep the bigger
// if (S[a].size() < S[b].size()) swap(S[a], S[b]);
// for (auto x : S[b]) S[a].insert(x); -> O(n log^2 n)
