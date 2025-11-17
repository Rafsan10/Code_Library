unordered_map<int, int> Start, End, Val;
unordered_map<int, pair<int, int>> Range;
int start = 0;
void dfs(int node) {
  visited[node] = true;
  Start[node] = start++;
  for (auto child : adj[node]) {
    if (!visited[child]) dfs(child);
  }
  End[node] = start - 1;
}
dfs(1);
vector<int> FlatArray(start + 5);
for (auto i : Start) {
  FlatArray[i.second] = Val[i.first];
  Range[i.first] = {i.second, End[i.first]};
