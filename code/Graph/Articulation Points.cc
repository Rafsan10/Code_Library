const int N = 2e5 + 5;
vector < int > g[N];
int vis[N], st[N], low[N], adjComp[N];
int clk, n;

void dfs(int u, int p) {
  vis[u] = 1;
  ++clk;
  st[u] = clk;
  low[u] = clk;
  int child = 0;
  for (int v: g[u]) {
    if (v == p) continue;
    if (vis[v]) {
      low[u] = min(low[u], st[v]);
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= st[u] && p != 0) {
        adjComp[u]++;
      }
      child++;
    }
  }
  if (p == 0 && child > 1) {
    adjComp[u] = child - 1;
  }
}
void find_vertices() {
  clk = 0;
  for (int i = 1; i <= n; i++) {
    vis[i] = 0;
    st[i] = low[i] = -1;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, 0);
    }
  }
}
