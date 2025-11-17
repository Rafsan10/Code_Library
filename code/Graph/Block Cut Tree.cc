const int N = 2e5 + 5;

vector<int> g[N], bct[2 * N];
int vis[N], low[N], disc[N], is_art[N];
stack<int> stk;
vector<int> block_of[N];
int clk, n, m, bct_nodes, root;

void dfs(int u, int p) {
  vis[u] = 1;
  disc[u] = low[u] = ++clk;
  stk.push(u);
  int child = 0;

  for (int v : g[u]) {
    if (v == p) continue;
    if (!vis[v]) {
      child++;
      dfs(v, u);
      low[u] = min(low[u], low[v]);

      if ((p == -1 && child > 1) || (p != -1 && low[v] >= disc[u])) {
        is_art[u] = 1;
        vector<int> block;
        while (stk.top() != v) {
          block.push_back(stk.top());
          stk.pop();
        }
        block.push_back(stk.top());
        stk.pop();
        block.push_back(u);

        int block_id = ++bct_nodes;
        for (int x : block) {
          block_of[x].push_back(block_id);
          if (is_art[x]) {
            bct[x].push_back(block_id);
            bct[block_id].push_back(x);
          }
        }
      }
    } else {
      low[u] = min(low[u], disc[v]);
    }
  }
}

void build_bct() {
  clk = 0;
  bct_nodes = n;
  for (int i = 1; i <= n; i++) {
    vis[i] = is_art[i] = 0;
    block_of[i].clear();
    bct[i].clear();
  }
  for (int i = n + 1; i <= 2 * n; i++) bct[i].clear();

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, -1);
      if (!stk.empty()) {
        int block_id = ++bct_nodes;
        while (!stk.empty()) {
          int x = stk.top();
          stk.pop();
          block_of[x].push_back(block_id);
          if (is_art[x]) {
            bct[x].push_back(block_id);
            bct[block_id].push_back(x);
          }
        }
      }
    }
  }

  root = n + 1;
  for (int i = 1; i <= n; i++) {
    if (is_art[i]) {
      root = i;
      break;
    }
  }
}
