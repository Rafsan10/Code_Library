const int N = 2e5 + 5;
vector < pair < int, int >> g[N];
int vis[N], st[N], low[N];
int clk, n;
vector < pair < int, int >> bridges;

void dfs(int u, int p, int edg) {
  vis[u] = 1;
  ++clk;
  st[u] = clk;
  low[u] = clk;
  for (auto[v, id]: g[u]) {
    // handled parallel edges between u, v
    if (v == p && id == edg) continue;
    if (vis[v]) {
      low[u] = min(low[u], st[v]);
    } else {
      dfs(v, u, id);
      low[u] = min(low[u], low[v]);
      if (st[u] < low[v]) {
        // edge u, v has bridge
        bridges.push_back({
          u,
          v
        });
      }
    }
  }
}
void find_bridges() {
  clk = 0;
  for (int i = 1; i <= n; i++) {
    vis[i] = 0;
    st[i] = low[i] = -1;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, 0, -1);
    }
  }
}
