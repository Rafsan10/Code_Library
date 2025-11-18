int fenwick[N];
void update(int ind, int val) {
  while (ind < N) {
    fenwick[ind] += val;
    ind += ind & -ind;
  }
}
int query(int ind) {
  int sum = 0;
  while (ind > 0) {
    sum += fenwick[ind];
    ind -= ind & -ind;
  }
  return sum;
}

struct Fenwick2D {
  vector<vector<int>> t;
  int n, m;
  Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<int>(m + 1, 0)) {}

  void update(int i, int j, int v) {
    for (int x = i; x <= n; x += x & -x)
      for (int y = j; y <= m; y += y & -y) t[x][y] += v;
  }

  int query(int i, int j) {
    int s = 0;
    for (int x = i; x > 0; x -= x & -x)
      for (int y = j; y > 0; y -= y & -y) s += t[x][y];
    return s;
  }

  int query(int r1, int c1, int r2, int c2) {
    return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) +
           query(r1 - 1, c1 - 1);
  }
};