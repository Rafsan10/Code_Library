vector<pair<int, pair<int, int>>> Krushkal(
    vector<pair<int, pair<int, int>>>& edges, int n) {
  sort(edges.begin(), edges.end());
  vector<pair<int, pair<int, int>>> ans;
  DisjointSet D(n);
  for (auto it : edges) {
    if (D.findUPar(it.second.first) != D.findUPar(it.second.second)) {
      ans.push_back({it.first, {it.second.first, it.second.second}});
      D.unionBySize(it.second.first, it.second.second);
    }
  }
  return ans;
}
