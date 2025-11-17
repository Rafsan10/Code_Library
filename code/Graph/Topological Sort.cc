vector<int> topologicalSort(int V, vector<vector<int>>& g) {
  vector<int> inDegree(V, 0);
  vector<int> result;
  queue<int> q;
  for (int u = 0; u < V; u++) {
    for (int v : g[u]) {
      inDegree[v]++;
    }
  }
  for (int i = 0; i < V; i++) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);
    for (int v : g[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }
  // You may need to check inDegree of all the vertices is 0
  if (result.size() != V) {
    cout << "Graph contains a cycle, topological sort not possible!" << endl;
    return {};
  }

  return result;
}
