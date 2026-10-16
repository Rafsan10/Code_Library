// Subtree of u = flat[tin[u] .. tout[u]] (contiguous)
// -> subtree queries become range queries (BIT / segtree)
const int N = 2e5 + 5;
vector<int> g[N];
int tin[N], tout[N], flat[N], timer_ = 0;
void dfs(int u, int p) {
  tin[u] = timer_;
  flat[timer_++] = u;
  for (int v : g[u])
    if (v != p) dfs(v, u);
  tout[u] = timer_ - 1;
}
// v in subtree of u <=> tin[u] <= tin[v] <= tout[u]
