// adj[u] = {v, w}, w >= 0. dist = INF if unreachable
const ll INF = 1e18;
vector<ll> dijkstra(int src,
                   vector<vector<pair<int, ll>>>& adj) {
  int n = adj.size();
  vector<ll> d(n, INF);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                 greater<pair<ll, int>>> pq;
  d[src] = 0; pq.push({0, src});
  while (!pq.empty()) {
    auto [du, u] = pq.top(); pq.pop();
    if (du != d[u]) continue; // stale entry
    for (auto [v, w] : adj[u])
      if (du + w < d[v]) {
        d[v] = du + w;
        pq.push({d[v], v});
      }
  }
  return d;
}
