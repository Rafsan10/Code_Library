// Static RMQ: O(n log n) build, O(1) query. Op must be
// idempotent: min, max, gcd, and, or. 0-indexed [l, r]
template <class T> struct Sparse {
  vector<vector<T>> st;
  T op(T a, T b) { return min(a, b); } // EDIT
  Sparse(const vector<T>& a) {
    int n = a.size(), K = __lg(max(n, 1)) + 1;
    st.assign(K, a);
    for (int k = 1; k < K; k++)
      for (int i = 0; i + (1 << k) <= n; i++)
        st[k][i] = op(st[k - 1][i],
                      st[k - 1][i + (1 << (k - 1))]);
  }
  T query(int l, int r) {
    int k = __lg(r - l + 1);
    return op(st[k][l], st[k][r - (1 << k) + 1]);
  }
};
// Sum (not idempotent): split into powers of 2
