// ei = edge index (position of neighbour in g[u])
// merge    : Agg * Value * Vertex(int) * ei -> Agg
// base     : Vertex(int) -> Agg
// finalize : Agg * Vertex(int) * ei -> Value
namespace reroot {
const auto exclusive = [](const auto& a,
    const auto& base, const auto& merge, int vertex) {
  int n = (int)a.size();
  using Agg = decay_t<decltype(base)>;
  vector<Agg> b(n, base);
  for (int bit = (int)__lg(n); bit >= 0; --bit) {
    for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
    int sz = n - (n & !bit);
    for (int i = 0; i < sz; ++i) {
      int index = (i >> bit) ^ 1;
      b[index] = merge(b[index], a[i], vertex, i);
    }
  }
  return b;
};
const auto rerooter = [](const auto& g,
    const auto& base, const auto& merge,
    const auto& finalize) {
  int n = (int)g.size();
  using Agg = decay_t<decltype(base(0))>;
  using Value =
      decay_t<decltype(finalize(base(0), 0, 0))>;
  vector<Value> root_dp(n), dp(n);
  vector<vector<Value>> edge_dp(n), redge_dp(n);
  vector<int> bfs, parent(n);
  bfs.reserve(n);
  bfs.push_back(0);
  for (int i = 0; i < n; ++i) {
    int u = bfs[i];
    for (auto v : g[u]) {
      if (parent[u] == v) continue;
      parent[v] = u;
      bfs.push_back(v);
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    int u = bfs[i];
    int par_ei = -1;
    Agg agg = base(u);
    for (int ei = 0; ei < (int)g[u].size(); ++ei) {
      int v = g[u][ei];
      if (parent[u] == v) {
        par_ei = ei;
        continue;
      }
      agg = merge(agg, dp[v], u, ei);
    }
    dp[u] = finalize(agg, u, par_ei);
  }
  for (auto u : bfs) {
    dp[parent[u]] = dp[u];
    edge_dp[u].reserve(g[u].size());
    for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
    auto dp_excl =
        exclusive(edge_dp[u], base(u), merge, u);
    redge_dp[u].reserve(g[u].size());
    for (int i = 0; i < (int)dp_excl.size(); ++i) {
      auto merge_value = finalize(dp_excl[i], u, i);
      redge_dp[u].push_back(merge_value);
    }
    root_dp[u] = finalize(n > 1 ? merge(dp_excl[0],
        edge_dp[u][0], u, 0) : base(u), u, -1);
    for (int i = 0; i < (int)g[u].size(); ++i) {
      dp[g[u][i]] = redge_dp[u][i];
    }
  }
  return make_tuple(move(root_dp), move(edge_dp),
                    move(redge_dp));
};
}  // namespace reroot
void solve() {
  using Agg = int;
  using Value = int;
  auto base = [](int vertex) -> Agg { return 0; };
  auto merge = [](Agg vertex_dp, Value neighbor_dp,
                  int vertex, int ei) -> Agg {
    return vertex_dp + max(neighbor_dp, 0);
  };
  auto finalize = [&](Agg vertex_dp, int vertex,
                      int ei) -> Value {
    return vertex_dp + 2 * color[vertex] - 1;
  };
  auto [reroot_result, edge_dp, redge_dp] =
      reroot::rerooter(g, base, merge, finalize);
  for (auto dp : reroot_result) {
    cout << dp << ' ';
  }
  cout << '\n';
}
