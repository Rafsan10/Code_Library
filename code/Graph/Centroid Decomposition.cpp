const int N = 1e5 + 5;
vector<int> g[N];
int sz[N], dead[N], cenpar[N];
void dfs_sz(int u, int p) {
  sz[u] = 1;
  for (int v : g[u]) {
    if (v == p || dead[v]) continue;
    dfs_sz(v, u);
    sz[u] += sz[v];
  }
}
int find_centroid(int num, int u, int p) {
  for (int v : g[u]) {
    if (v != p && !dead[v] && 2 * sz[v] > num) {
      return find_centroid(num, v, u);
    }
  }
  return u;
}
void decompose(int u, int p) {
  dfs_sz(u, p);
  int cent = find_centroid(sz[u], u, p);
  dead[cent] = true;
  cenpar[cent] = p;
  for (int v : g[cent]) {
    if (!dead[v]) {
      decompose(v, cent);
    }
  }
}
