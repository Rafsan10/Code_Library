array<vector<int>, 2> get_sa(string& s, int lim=128) {  // for integer, just change string to vector<int> and minimum value of vector must be >= 1
  int n = s.size() + 1, k = 0, a, b;
  vector<int> x(begin(s), end(s)+1), y(n), sa(n), lcp(n), ws(max(n, lim)), rank(n);
  x.back() = 0;
  iota(begin(sa), end(sa), 0);
  for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p)
  {
    p = j, iota(begin(y), end(y), n - j);
    for (int i = 0; i < n; ++i){
      if (sa[i] >= j) y[p++] = sa[i] - j;
    }
    fill(begin(ws), end(ws), 0);
    for (int i = 0; i < n; ++i) ws[x[i]]++;
    for (int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
    for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
    swap(x, y), p = 1, x[sa[0]] = 0;
    for (int i = 1; i < n; ++i){
      a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
  }
  for (int i = 1; i < n; ++i) rank[sa[i]] = i;
  for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k){
    for (k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
  }
  sa.erase(sa.begin()), lcp.erase(lcp.begin());
  return {sa, lcp};
}
## Comparing Two Substrings
auto compare = [&] (int l1, int r1, int l2, int r2) {
  int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
  int len = min(len1, len2);
  int i = pos[l1], j = pos[l2], x;
  if (l1 != l2) x = st.query(i, j);
  else x = len;
  if (x >= len) {
    if (len1 == len2) return 0;
    if (len1 < len2) return -1;
    return 1;
  }
  if (s[l1 + x] < s[l2 + x]) return -1;
  return 1;
};
## Kth Unique Substring
auto kth = [&] (ll k) {
  int i = 0;
  while (i + 1 < n and k > n - sa[i] - lcp[i]) {
    k -= n - sa[i] - lcp[i];
    i++;
  }
  k = min(k, 0ll + n - sa[i] - lcp[i]);
  array<int, 2> ret = {sa[i], k + lcp[i]};
  return ret;
};
## Kth Unique Substring (Multiple Queries)
vector<ll> pref(n + 1);
for (int i = 0; i < n; ++i) {
  pref[i + 1] = pref[i] + (n - sa[i] - lcp[i]);
}
auto kth = [&] (ll k) {
  int i = lower_bound(pref.begin(), pref.end(), k) - pref.begin();
  i--;
  k -= pref[i];
  return array<int, 2>{sa[i], k + lcp[i]};
};
auto [i, len] = kth(k);
cout << s.substr(i, len) << "\n";
## Kth Substring (not necessarily unique)
ll k; cin >> k;
auto ok = [&] (ll x) {
  auto [i, len] = kth(x);
  ll tot = 0;
  for (int j = 0; j < pos[i]; ++j) {
    tot += n - sa[j];
  }
  tot += len;
  int mn = len;
  for (int j = pos[i] + 1; j < n; ++j) {
    mn = min(mn, lcp[j]);
    tot += mn;
  }
  return tot >= k;
};
ll lo = 1, hi = 1;
while (!ok(hi)) hi = hi << 1;
while (lo <= hi) {
  ll mid = (lo + hi) >> 1;
  if (ok(mid)) hi = mid - 1;
  else lo = mid + 1;
}
## Several Consecutive Identical Substrings
auto [sa, lcp] = get_sa(s);
Sparse st(sa, lcp);
auto rev_s = s;
reverse(rev_s.begin(), rev_s.end());
auto [rev_sa, rev_lcp] = get_sa(rev_s);
Sparse rev_st(rev_sa, rev_lcp);
int k = 1;
for (int len = 1; len <= n / 2; ++len) {
  for (int i = 0; i + len < n; i += len) {
    int er = st.get_lcp(i, i + len);
    int el = 0;
    if (i) el = rev_st.get_lcp(n - i, n - i - len); // rev lcp of (i - 1, i + len - 1)
    k = max(k, 1 + (er + el) / len);
  }
}
## Sparse Table for LCP Array
struct Sparse {
    int n;
    vector<array<int, K>> st;
    vector<int> pos;
    Sparse (vector<int> sa, vector<int> &lcp) {
        n = sa.size();
        pos.resize(n);
        for (int i = 0; i < n; ++i) {
            pos[sa[i]] = i;
        }
        st.resize(n);
        for(int i = 0; i < n; ++i) st[i][0]=lcp[i];
        for(int k = 0; k + 1 < K; ++k)
          for(int i = 0; i + (2 << k) <= n; ++i)
            st[i][k + 1] = min(st[i][k], st[i + (1 << k)][k]);
    }

    int get_lcp(int l, int r) {
      l = pos[l];
      r = pos[r];
      if (l > r) swap(l, r);
      assert(l < r);
      l++;
      int k = lg[r - l + 1];
      return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
};