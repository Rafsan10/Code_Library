void bellmanFord(int num_of_nd, int src) {
  dist[src] = 0;
  for (int step = 0; step < num_of_nd; step) {
    for (int i = 1; i <= num_of_nd; i++) {
      for (auto it : adj[i]) {
        int u = i;
        int v = it.first;
        int wt = it.second;
        if (dist[u] != inf && ((dist[u] + wt) < dist[v])) {
          if (step == num_of_nd - 1) {
            cout << "Negative cycle found\n ";
            return;
          }
          dist[v] = dist[u] + wt;
          parent[v] = u;
        }
      }
    }
  }
  for (int i = 1; i <= num_of_nd; i++) cout << dist[i] << " ";
  cout << endl;
}
