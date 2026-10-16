// 1-indexed. point add, prefix / range sum. O(log n)
struct BIT {
  int n; vector<ll> t;
  BIT(int n) : n(n), t(n + 1, 0) {}
  void update(int i, ll v) {
    for (; i <= n; i += i & -i) t[i] += v;
  }
  ll query(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += t[i];
    return s;
  }
  ll query(int l, int r) {
    return query(r) - query(l - 1);
  }
  // smallest i with prefix sum >= k (all values >= 0)
  int lower_bound(ll k) {
    int pos = 0;
    for (int pw = __lg(n); pw >= 0; pw--)
      if (pos + (1 << pw) <= n &&
          t[pos + (1 << pw)] < k)
        pos += 1 << pw, k -= t[pos];
    return pos + 1;
  }
};
// Range add, point query: update(l,v), update(r+1,-v)
struct Fenwick2D {
  int n, m;
  vector<vector<ll>> t;
  Fenwick2D(int n, int m)
      : n(n), m(m), t(n + 1, vector<ll>(m + 1, 0)) {}
  void update(int i, int j, ll v) {
    for (int x = i; x <= n; x += x & -x)
      for (int y = j; y <= m; y += y & -y) t[x][y] += v;
  }
  ll query(int i, int j) {
    ll s = 0;
    for (int x = i; x > 0; x -= x & -x)
      for (int y = j; y > 0; y -= y & -y) s += t[x][y];
    return s;
  }
  ll query(int r1, int c1, int r2, int c2) {
    return query(r2, c2) - query(r1 - 1, c2)
         - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
  }
};
