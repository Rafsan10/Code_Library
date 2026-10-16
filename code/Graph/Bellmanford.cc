// Nodes 1..n. Both return false if a NEGATIVE CYCLE is
// reachable from src. d[v] = INF if unreachable.
const ll INF = 1e18;
struct Edge { int u, v; ll w; };
// Bellman-Ford O(V * E)
bool bellmanFord(int n, int src, vector<Edge>& e,
                 vector<ll>& d) {
  d.assign(n + 1, INF); d[src] = 0;
  for (int it = 1; it <= n; it++) {
    bool any = false;
    for (auto [u, v, w] : e)
      if (d[u] < INF && d[u] + w < d[v]) {
        d[v] = d[u] + w; any = true;
        if (it == n) return false; // n-th pass relaxed
      }
    if (!any) break;
  }
  return true;
}
// SPFA: usually fast, worst O(V * E). adj[u] = {v, w}
bool spfa(int n, int src,
          vector<vector<pair<int, ll>>>& adj,
          vector<ll>& d) {
  d.assign(n + 1, INF);
  vector<int> len(n + 1, 0); // edges on current path
  vector<bool> inq(n + 1, false);
  queue<int> q;
  d[src] = 0; q.push(src); inq[src] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop(); inq[u] = false;
    for (auto [v, w] : adj[u])
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        len[v] = len[u] + 1;
        if (len[v] >= n) return false;
        if (!inq[v]) q.push(v), inq[v] = true;
      }
  }
  return true;
}
