// 4-dir, 8-dir (first 4 + diagonals), knight moves
int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
int kx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int ky[] = {1, 2, 2, 1, -1, -2, -2, -1};
// Grid BFS from (sx, sy), '#' = wall, -1 = unreachable
vector<vector<int>> gridBFS(vector<string>& g, int sx,
                            int sy) {
  int n = g.size(), m = g[0].size();
  vector<vector<int>> d(n, vector<int>(m, -1));
  queue<pair<int, int>> q;
  d[sx][sy] = 0; q.push({sx, sy});
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m)
        continue;
      if (g[nx][ny] == '#' || d[nx][ny] != -1)
        continue;
      d[nx][ny] = d[x][y] + 1; q.push({nx, ny});
    }
  }
  return d;
}
// Bipartite check (2-coloring), col[v] in {0, 1}
bool bipartite(vector<vector<int>>& adj,
               vector<int>& col) {
  int n = adj.size(); col.assign(n, -1);
  for (int s = 0; s < n; s++) {
    if (col[s] != -1) continue;
    queue<int> q; q.push(s); col[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (col[v] == -1)
          col[v] = col[u] ^ 1, q.push(v);
        else if (col[v] == col[u]) return false;
      }
    }
  }
  return true;
}
// Directed cycle: 0 unvisited, 1 on stack, 2 done
bool hasCycle(int u, vector<vector<int>>& adj,
              vector<int>& st) {
  st[u] = 1;
  for (int v : adj[u]) {
    if (st[v] == 1) return true;
    if (st[v] == 0 && hasCycle(v, adj, st))
      return true;
  }
  st[u] = 2;
  return false;
}
