// Successive shortest paths + SPFA (negative costs ok,
// no negative cycles). Returns {max flow, min cost}.
// Flow limit K: pass maxf = K. Max cost: negate costs.
struct MCMF {
  struct E { int to; ll cap, cost; };
  int n; vector<E> e; vector<vector<int>> g;
  vector<ll> dist; vector<int> pe; vector<bool> inq;
  MCMF(int n) : n(n), g(n), dist(n), pe(n), inq(n) {}
  void addEdge(int u, int v, ll cap, ll cost) {
    g[u].push_back(e.size());
    e.push_back({v, cap, cost});
    g[v].push_back(e.size());
    e.push_back({u, 0, -cost});
  }
  bool spfa(int s, int t) {
    fill(dist.begin(), dist.end(), LLONG_MAX);
    queue<int> q; q.push(s); dist[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = false;
      for (int id : g[u]) {
        auto& [v, cap, cost] = e[id];
        if (cap > 0 && dist[u] + cost < dist[v]) {
          dist[v] = dist[u] + cost; pe[v] = id;
          if (!inq[v]) inq[v] = true, q.push(v);
        }
      }
    }
    return dist[t] != LLONG_MAX;
  }
  pair<ll, ll> run(int s, int t, ll maxf = LLONG_MAX) {
    ll flow = 0, cost = 0;
    while (flow < maxf && spfa(s, t)) {
      ll f = maxf - flow;
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        f = min(f, e[pe[v]].cap);
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        e[pe[v]].cap -= f, e[pe[v] ^ 1].cap += f;
      flow += f; cost += f * dist[t];
    }
    return {flow, cost};
  }
};
