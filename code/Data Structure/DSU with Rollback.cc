// Union by size, NO path compression -> find O(log n).
// rollback(snap) undoes all unites after snapshot().
// For: offline dynamic connectivity (segtree on time),
// Mo's + DSU, divide & conquer over queries.
struct DSURollback {
  vector<int> par, sz;
  vector<pair<int, int>> ops; // {kept root, merged}
  int comps;
  DSURollback(int n)
      : par(n + 1), sz(n + 1, 1), comps(n) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    while (u != par[u]) u = par[u];
    return u;
  }
  bool unite(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u; sz[u] += sz[v]; comps--;
    ops.push_back({u, v});
    return true;
  }
  int snapshot() { return ops.size(); }
  void rollback(int snap) {
    while ((int)ops.size() > snap) {
      auto [u, v] = ops.back(); ops.pop_back();
      par[v] = v; sz[u] -= sz[v]; comps++;
    }
  }
};
