// n boolean vars 0..n-1. Literal: var x true = 2x,
// false = 2x+1. Tarjan SCC, O(n + clauses)
struct TwoSat {
  int n; vector<vector<int>> g;
  vector<int> comp, low, tin, stk; vector<bool> val;
  int timer = 0, nc = 0;
  TwoSat(int n) : n(n), g(2 * n) {}
  int lit(int x, bool v) { return 2 * x + !v; }
  // (x == vx) OR (y == vy)
  void either(int x, bool vx, int y, bool vy) {
    int a = lit(x, vx), b = lit(y, vy);
    g[a ^ 1].push_back(b); g[b ^ 1].push_back(a);
  }
  void setVal(int x, bool v) { either(x, v, x, v); }
  void implies(int x, bool vx, int y, bool vy) { // x -> y
    either(x, !vx, y, vy);
  }
  void dfs(int u) {
    low[u] = tin[u] = ++timer; stk.push_back(u);
    for (int v : g[u]) {
      if (!tin[v]) dfs(v), low[u] = min(low[u], low[v]);
      else if (comp[v] == -1) low[u] = min(low[u], tin[v]);
    }
    if (low[u] == tin[u]) {
      int v;
      do { v = stk.back(); stk.pop_back(); comp[v] = nc; }
      while (v != u);
      nc++;
    }
  }
  bool solve() { // val[x] = assignment if satisfiable
    comp.assign(2 * n, -1); low.assign(2 * n, 0);
    tin.assign(2 * n, 0); val.assign(n, false);
    for (int i = 0; i < 2 * n; i++) if (!tin[i]) dfs(i);
    for (int x = 0; x < n; x++) {
      if (comp[2 * x] == comp[2 * x + 1]) return false;
      val[x] = comp[2 * x] < comp[2 * x + 1]; // Tarjan order
    }
    return true;
  }
};
