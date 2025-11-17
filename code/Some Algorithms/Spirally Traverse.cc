vector<int> spirallyTraverse(vector<vector<int>>& mat) {
  int m = mat.size();
  int n = mat[0].size();
  vector<int> res;
  vector<vector<bool>> vis(m, vector<bool>(n, false));
  vector<int> dr = {0, 1, 0, -1};
  vector<int> dc = {1, 0, -1, 0};
  int r = 0, c = 0;
  int idx = 0;
  for (int i = 0; i < m * n; ++i) {
    res.push_back(mat[r][c]);
    vis[r][c] = true;
    int newR = r + dr[idx];
    int newC = c + dc[idx];
    if (0 <= newR && newR < m && 0 <= newC && newC < n && !vis[newR][newC]) {
      r = newR;
      c = newC;
    } else {
      idx = (idx + 1) % 4;
      r += dr[idx];
      c += dc[idx];
    }
  }
  return res;
}
