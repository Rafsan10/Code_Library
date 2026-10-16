// MST using DSU (Data Structure section). Nodes 1..n
// edges: {w, u, v}. Returns MST weight, fills `used`.
ll kruskal(int n, vector<array<ll, 3>>& edges,
           vector<array<ll, 3>>& used) {
  sort(edges.begin(), edges.end());
  DSU d(n); ll total = 0;
  for (auto& [w, u, v] : edges)
    if (d.find(u) != d.find(v)) {
      d.unite(u, v);
      total += w;
      used.push_back({w, u, v});
    }
  return total; // if used.size() < n - 1: not connected
}
