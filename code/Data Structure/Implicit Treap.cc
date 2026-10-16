// Array with split / merge in O(log n) expected:
// insert / erase at position, range reverse, sum.
// Positions are 0-indexed. Edit pull() / push() for
// other range ops (min, add lazy, ...)
mt19937 rngT(chrono::steady_clock::now()
                 .time_since_epoch().count());
struct Treap {
  struct Node {
    int l = 0, r = 0, sz = 1; unsigned pri;
    ll val, sum; bool rev = false;
  };
  vector<Node> t = {Node()}; // t[0] = null, sz 0
  Treap() { t[0].sz = 0; t[0].val = t[0].sum = 0; }
  int newNode(ll v) {
    Node x; x.pri = rngT(); x.val = x.sum = v;
    t.push_back(x); return t.size() - 1;
  }
  void push(int u) {
    if (u && t[u].rev) {
      swap(t[u].l, t[u].r);
      if (t[u].l) t[t[u].l].rev ^= 1;
      if (t[u].r) t[t[u].r].rev ^= 1;
      t[u].rev = false;
    }
  }
  void pull(int u) {
    t[u].sz = 1 + t[t[u].l].sz + t[t[u].r].sz;
    t[u].sum = t[u].val + t[t[u].l].sum
             + t[t[u].r].sum;
  }
  // first k elements -> a, rest -> b
  void split(int u, int k, int& a, int& b) {
    if (!u) { a = b = 0; return; }
    push(u);
    if (t[t[u].l].sz < k) {
      split(t[u].r, k - t[t[u].l].sz - 1, t[u].r, b);
      a = u;
    } else {
      split(t[u].l, k, a, t[u].l);
      b = u;
    }
    pull(u);
  }
  int merge(int a, int b) {
    if (!a || !b) return a ? a : b;
    if (t[a].pri > t[b].pri) {
      push(a); t[a].r = merge(t[a].r, b);
      pull(a); return a;
    }
    push(b); t[b].l = merge(a, t[b].l);
    pull(b); return b;
  }
  int root = 0;
  void insert(int pos, ll v) { // new elem at pos
    int a, b; split(root, pos, a, b);
    root = merge(merge(a, newNode(v)), b);
  }
  void erase(int pos) {
    int a, b, c; split(root, pos, a, b);
    split(b, 1, b, c); root = merge(a, c);
  }
  // apply f to the treap of range [l, r]
  template <class F> void range(int l, int r, F f) {
    int a, b, c; split(root, l, a, b);
    split(b, r - l + 1, b, c);
    f(b); root = merge(merge(a, b), c);
  }
  void reverse(int l, int r) {
    range(l, r, [&](int u) { if (u) t[u].rev ^= 1; });
  }
  ll sum(int l, int r) {
    ll s = 0;
    range(l, r, [&](int u) { s = t[u].sum; });
    return s;
  }
};
