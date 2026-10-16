// Shortest path when weights are only 0 or 1, O(V + E)
// adj[u] = {v, w}, w in {0, 1}. Also grid problems.
vector<int> bfs01(int src,
                  vector<vector<pair<int, int>>>& adj) {
  vector<int> d(adj.size(), INT_MAX);
  deque<int> dq;
  d[src] = 0; dq.push_back(src);
  while (!dq.empty()) {
    int u = dq.front(); dq.pop_front();
    for (auto [v, w] : adj[u])
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        if (w == 0) dq.push_front(v);
        else dq.push_back(v);
      }
  }
  return d;
}
