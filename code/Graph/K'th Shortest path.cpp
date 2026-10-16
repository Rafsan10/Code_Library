// d[v] = K smallest walk lengths src -> v (sorted, walks
// may repeat vertices). Each node popped <= K times.
// O(K * (V + E) log). adj[u] = {v, w}, w >= 0
vector<vector<ll>> kShortest(int src, int K,
    vector<vector<pair<int, ll>>>& adj) {
  int n = adj.size();
  vector<vector<ll>> d(n);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                 greater<pair<ll, int>>> pq;
  pq.push({0, src});
  while (!pq.empty()) {
    auto [du, u] = pq.top(); pq.pop();
    if ((int)d[u].size() >= K) continue;
    d[u].push_back(du);
    for (auto [v, w] : adj[u])
      if ((int)d[v].size() < K) pq.push({du + w, v});
  }
  return d;
}
