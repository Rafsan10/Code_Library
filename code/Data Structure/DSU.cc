struct DSU {
  vector<int> par, sz, minElmt, maxElmt, cntElmt;
  int cc;
 public:
  DSU(int n) {
    par.resize(n + 1);
    sz.resize(n + 1, 1);
    minElmt.resize(n + 1);
    maxElmt.resize(n + 1);
    cntElmt.resize(n + 1, 1);
    cc = n;
    for (int i = 1; i <= n; i++)
      par[i] = minElmt[i] = maxElmt[i] = i;
  }
  int find(int u) {
    if (u == par[u]) return u;
    return par[u] = find(par[u]);
  }
  void unite(int u, int v) {
    int pU = find(u);
    int pV = find(v);
    if (pU == pV) return;
    if (sz[pU] < sz[pV]) swap(pU, pV);
    par[pV] = pU;
    sz[pU] += sz[pV];
    cc--;
    cntElmt[pU] += cntElmt[pV];
    minElmt[pU] = min(minElmt[pU], minElmt[pV]);
    maxElmt[pU] = max(maxElmt[pU], maxElmt[pV]);
  }
  // min / max / count of elements in u's set
  int getMin(int u) { return minElmt[find(u)]; }
  int getMax(int u) { return maxElmt[find(u)]; }
  int getCnt(int u) { return cntElmt[find(u)]; }
};