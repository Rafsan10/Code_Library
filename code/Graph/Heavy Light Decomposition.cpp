vector<pair<int, int>> g[N];
int edge_to_ch[N];
int par[N], dep[N], sz[N];

void dfs(int u, int p = 0) {
	sz[u] = 1, par[u] = p;
	dep[u] = dep[p] + 1;
	int mx = 0;
	for (auto &[v, idx]: g[u]) {
		if (v == p) continue;
		edge_to_ch[idx] = v;
		dfs(v, u);
		sz[u] += sz[v];
		if (sz[v] > mx) {
			mx = sz[v];
			swap(v, g[u][0].first);
		}
	}
}

int T, head[N], st[N], en[N];

void dfs_hld(int u, int p = 0) {
	st[u] = ++T;
	head[u] = (p != 0 && g[p][0].first == u) ? head[p] : u;
	for (auto [v, idx]: g[u]) {
		if (v == p) continue;
		dfs_hld(v, u);
	}
	en[u] = T;
}
int lca(int a, int b) {
	for (; head[a] != head[b]; b = par[head[b]]) {
		if (dep[head[a]] > dep[head[b]]) swap(a, b);
	}
	if (dep[a] > dep[b]) swap(a, b);
	return a;
}
int n;
// process node u upto it's ancestor a
// if excl is true, a won't process
i64 chain_process(int a, int u, bool excl = false) {
	i64 ans = 0;
	for (; head[u] != head[a]; u = par[head[u]]) {
		ans = max(ans, query(1, 1, n, st[head[u]], st[u]));	
	}
	ans = max(ans, query(1, 1, n, st[a] + excl, st[u]));	
	return ans;
}
// process path from node a to b
// if excl is true, lca won't process
i64 path_process(int a, int b, bool excl = false) {
	i64 ans = 0;
	for (; head[a] != head[b]; b = par[head[b]]) {
		if (dep[head[a]] > dep[head[b]]) swap(a, b);
		ans = max(ans, query(1, 1, n, st[head[b]], st[b]));
	}
	if (dep[a] > dep[b]) swap(a, b);
	ans = max(ans, query(1, 1, n, st[a] + excl, st[b]));
	return ans;
}
// update path from node u to v
// if excl is true, lca won't update
void path_update(int a, int b, int val, bool excl = false) {
  for (; head[a] != head[b]; b = par[head[b]]) {
    if (dep[head[a]] > dep[head[b]]) swap(a, b);
    update(1, 1, n, st[head[b]], st[b], val);
  }
  if (dep[a] > dep[b]) swap(a, b);
  update(1, 1, n, st[a] + excl, st[b], val);
}
/*
	 dfs(1);
	 head[1] = 1;
	 dfs_hld(1);
	 build(1, 1, n);
*/
void solve() {
  cin >> n;
  int q;
  cin >> q;
  for (int i = 1; i < n; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    g[u].push_back({v, i});
    g[v].push_back({u, i});
    edge_cost[i] = c;
  }
  dfs(1);
  head[1] = 1;
  dfs_hld(1);
  for (int i = 1; i < n; i++) {
    int u = edge_to_ch[i];
    arr[st[u]] = edge_cost[i];
  }
  build(1, 1, n);
  while (q--) {
    int u, v, val;
    cin >> u >> v >> val;
    path_update(u, v, val, true);
    cout << path_process(u, v, true) << '\n';
  }
}
