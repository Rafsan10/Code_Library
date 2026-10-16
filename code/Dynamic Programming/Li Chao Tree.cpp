// MIN query, any line order, x in [L, R]. O(log C)
// MAX: add(-m,-c), ans=-query(x). Dynamic, x up to 1e9
// add_seg(l,r,m,c): line only on [l,r]. O(log^2 C)
struct LiChao {
  struct Line {
    ll m = 0, c = LLONG_MAX;
    ll eval(ll x) const { return m * x + c; }
  };
  struct Node { Line ln; int lc = 0, rc = 0; };
  vector<Node> t; ll L, R;
  LiChao(ll L, ll R) : t(2), L(L), R(R) {} // 1=root
  int child(int u, bool r) { // make if missing
    if (!(r ? t[u].rc : t[u].lc)) {
      int x = t.size(); t.emplace_back();
      (r ? t[u].rc : t[u].lc) = x;
    }
    return r ? t[u].rc : t[u].lc;
  }
  void add(int u, ll l, ll r, Line nl) {
    ll mid = l + (r - l) / 2;
    bool lef = nl.eval(l) < t[u].ln.eval(l);
    bool md = nl.eval(mid) < t[u].ln.eval(mid);
    if (md) swap(t[u].ln, nl);
    if (l == r || nl.c == LLONG_MAX) return;
    if (lef != md) add(child(u, 0), l, mid, nl);
    else add(child(u, 1), mid + 1, r, nl);
  }
  void add_seg(int u, ll l, ll r, ll a, ll b, Line nl) {
    if (b < l || r < a) return;
    if (a <= l && r <= b) { add(u, l, r, nl); return; }
    ll mid = l + (r - l) / 2;
    add_seg(child(u, 0), l, mid, a, b, nl);
    add_seg(child(u, 1), mid + 1, r, a, b, nl);
  }
  ll query(int u, ll l, ll r, ll x) {
    if (!u) return LLONG_MAX;
    ll res = t[u].ln.eval(x), mid = l + (r - l) / 2;
    if (l == r) return res;
    ll q = x <= mid ? query(t[u].lc, l, mid, x)
                    : query(t[u].rc, mid + 1, r, x);
    return min(res, q);
  }
  void add(ll m, ll c) { add(1, L, R, {m, c}); }
  void add_seg(ll l, ll r, ll m, ll c) {
    add_seg(1, L, R, l, r, {m, c});
  }
  ll query(ll x) { return query(1, L, R, x); }
};
