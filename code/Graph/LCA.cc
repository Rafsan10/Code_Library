const int N = 1e5 + 5, LG = 17;
vector<int> g[N];
int depth[N], parent[N][LG];
void dfs(int u, int p) {
  depth[u] = depth[p] + 1;
  parent[u][0] = p;
  for (int i = 1; i < LG; i++) {
    parent[u][i] = parent[parent[u][i - 1]][i - 1];
  }
  for (int v : g[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
}
int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];
  for (int i = 0; i < LG; i++) {
    if (diff >> i & 1) {
      u = parent[u][i];
    }
  }
  if (u == v) return u;
  for (int i = LG - 1; i >= 0; i--) {
    if (parent[u][i] != parent[v][i]) {
      u = parent[u][i];
      v = parent[v][i];
    }
  }
  return parent[u][0];
}
int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
int kthParent(int u, int k) {
  for (int i = 0; i < LG; i++) {
    if (k >> i & 1) {
      u = parent[u][i];
    }
  }
  return u;
}
