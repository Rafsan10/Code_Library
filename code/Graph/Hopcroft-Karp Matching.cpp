// Max bipartite matching, O(E sqrt V). Left 0..n-1,
// right 0..m-1, adj[u] = right neighbours of left u.
// Konig: min vertex cover = max matching,
// max independent set = n + m - matching
struct HopcroftKarp {
  int n, m;
  vector<vector<int>> adj;
  vector<int> mL, mR, dist;
  HopcroftKarp(int n, int m)
      : n(n), m(m), adj(n), mL(n, -1), mR(m, -1), dist(n) {}
  void addEdge(int u, int v) { adj[u].push_back(v); }
  bool bfs() {
    queue<int> q; bool found = false;
    for (int u = 0; u < n; u++) {
      dist[u] = mL[u] == -1 ? 0 : -1;
      if (!dist[u]) q.push(u);
    }
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        int w = mR[v];
        if (w == -1) found = true;
        else if (dist[w] == -1) dist[w] = dist[u] + 1, q.push(w);
      }
    }
    return found;
  }
  bool dfs(int u) {
    for (int v : adj[u]) {
      int w = mR[v];
      if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
        mL[u] = v; mR[v] = u;
        return true;
      }
    }
    dist[u] = -1;
    return false;
  }
  int maxMatching() {
    int res = 0;
    while (bfs())
      for (int u = 0; u < n; u++)
        if (mL[u] == -1 && dfs(u)) res++;
    return res;
  }
};
