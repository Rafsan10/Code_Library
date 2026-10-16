// O(V^2 E), unit capacity / bipartite: O(E sqrt V)
// Min cut: after maxflow, S side = level[v] != -1
// Bipartite matching: src->L (1), L->R (1), R->sink (1)
struct Dinic {
  struct E { int to; ll cap; };
  vector<E> e; vector<vector<int>> g;
  vector<int> level, it;
  Dinic(int n) : g(n), level(n), it(n) {}
  int addEdge(int u, int v, ll cap, ll rcap = 0) {
    g[u].push_back(e.size()); e.push_back({v, cap});
    g[v].push_back(e.size()); e.push_back({u, rcap});
    return e.size() - 2; // id; flow on it = e[id ^ 1].cap
  }
  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q; q.push(s); level[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : g[u])
        if (e[id].cap > 0 && level[e[id].to] == -1) {
          level[e[id].to] = level[u] + 1;
          q.push(e[id].to);
        }
    }
    return level[t] != -1;
  }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    for (int& i = it[u]; i < (int)g[u].size(); i++) {
      int id = g[u][i], v = e[id].to;
      if (e[id].cap > 0 && level[v] == level[u] + 1) {
        ll got = dfs(v, t, min(f, e[id].cap));
        if (got > 0) {
          e[id].cap -= got; e[id ^ 1].cap += got;
          return got;
        }
      }
    }
    return 0;
  }
  ll maxflow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
      fill(it.begin(), it.end(), 0);
      while (ll f = dfs(s, t, LLONG_MAX)) flow += f;
    }
    return flow;
  }
};
