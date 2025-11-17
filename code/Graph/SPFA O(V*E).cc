int q[3001] = {0};  // queue for node
it d[1001] = {0};   // record shortest path
from start to ith node bool f[1001] = {0};
int a[1001][1001] = {0};  // adjacency list
int w[1001][1001] = {0};  // adjacency matrix
int main(void) {
  int n = 0, m = 0;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int x = 0, y = 0, z = 0;
    cin >> x >> y >> z;
    // node x to node y has weight z
    a[x][0]++;
    a[x][a[x][0]] = y;
    w[x][y] = z;
    /*
    // for undirected graph
     a[x][0]++;
     a[y][a[y][0]]=x;
    w[y][x]=z;
    */
  }
  int s = 0, e = 0;
  cin >> s >> e;  // s: start, e: end
  SPFA(s);
  cout << d[e] << endl;
  return 0;
}
void SPFA(int v0) {
  int t, h, u, v;
  for (int i = 0; i < 1001; i++) d[i] = INT_MAX;
  for (int i = 0; i < 1001; i++) f[i] = false;
  d[v0] = 0;
  h = 0;
  t = 1;
  q[1] = v0;
  f[v0] = true;
  while (h != t) {
    h++;
    if (h > 3000) h = 1;
    u = q[h];
    for (int j = 1; j <= a[u][0]; j++) {
      v = a[u][j];
      if (d[u] + w[u][v] < d[v])  // change to > if calculating longest path
      {
        d[v] = d[u] + w[u][v];
        if (!f[v]) {
          t++;
          if (t > 3000) t = 1;
          q[t] = v;
          f[v] = true;
        }
      }
    }
    f[u] = false;
  }
}
