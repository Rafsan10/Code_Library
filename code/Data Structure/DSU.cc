class DisjointSet {
  vector<int> par, sz, minElmt, maxElmt, cntElmt;

 public:
  DisjointSet(int n) {
    par.resize(n + 1);
    sz.resize(n + 1, 1);
    minElmt.resize(n + 1);
    maxElmt.resize(n + 1);
    cntElmt.resize(n + 1, 1);
    for (int i = 1; i <= n; i++) par[i] = minElmt[i] = maxElmt[i] = i;
  }
  int findUPar(int u) {
    if (u == par[u]) return u;
    return par[u] = findUPar(par[u]);
  }
  void unionBySize(int u, int v) {
    int pU = findUPar(u);
    int pV = findUPar(v);
    if (pU == pV) return;
    if (sz[pU] < sz[pV]) swap(pU, pV);
    par[pV] = pU;
    sz[pU] += sz[pV];
    cntElmt[pU] += cntElmt[pV];
    minElmt[pU] = min(minElmt[pU], minElmt[pV]);
    maxElmt[pU] = max(maxElmt[pU], maxElmt[pV]);
  }
  int getMinElementIntheSet(int u) { return minElmt[findUPar(u)]; }
  int getMaxElementIntheSet(int u) { return maxElmt[findUPar(u)]; }
  int getNumofElementIntheSet(int u) { return cntElmt[findUPar(u)]; }
};
