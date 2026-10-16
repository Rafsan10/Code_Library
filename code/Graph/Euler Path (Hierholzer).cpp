// Euler path/circuit using every edge once. O(V + E)
// Undirected: 0 or 2 odd-degree vertices (start at odd)
// Directed: out-in = 1 at start, in-out = 1 at end,
// else 0. Returns vertices; size != E + 1 -> impossible
// (also when edges are in more than one component)
vector<int> eulerPath(int n,
    vector<pair<int, int>>& edges,
    bool directed, int start) {
  vector<vector<pair<int, int>>> g(n); // {to, edge id}
  for (int i = 0; i < (int)edges.size(); i++) {
    auto [u, v] = edges[i];
    g[u].push_back({v, i});
    if (!directed) g[v].push_back({u, i});
  }
  vector<bool> used(edges.size(), false);
  vector<int> ptr(n, 0), path, stk = {start};
  while (!stk.empty()) {
    int u = stk.back();
    while (ptr[u] < (int)g[u].size() &&
           used[g[u][ptr[u]].second]) ptr[u]++;
    if (ptr[u] == (int)g[u].size()) {
      path.push_back(u); stk.pop_back();
    } else {
      auto [v, id] = g[u][ptr[u]++];
      used[id] = true; stk.push_back(v);
    }
  }
  reverse(path.begin(), path.end());
  return path;
}
