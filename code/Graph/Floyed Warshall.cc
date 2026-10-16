// Init: dist[i][i] = 0, dist[u][v] = min(w), else INF
// Negative cycle exists iff dist[i][i] < 0 after run
const ll INF = 1e18;
const int MAXN = 505;
ll dist[MAXN][MAXN];
void floydWarshall(int n) {
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (dist[i][k] < INF && dist[k][j] < INF)
          dist[i][j] =
              min(dist[i][j], dist[i][k] + dist[k][j]);
}
