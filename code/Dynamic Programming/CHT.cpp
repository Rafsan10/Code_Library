/* INITIALIZATION & INSERTION RULES:
- Max Query: `CHT cht(true);`  --> Slopes MUST be added
  INCREASING (m1 <= m2 <= m3)
- Min Query: `CHT cht(false);` --> Slopes MUST be added
  DECREASING (m1 >= m2 >= m3)
QUERY RULES:
- `query(x)`: O(log N) for ANY x -> USE THIS BY DEFAULT
- `query_monotonic(x)`: O(1) -> ONLY if x INCREASING!
  (x decreasing: query(x) or reverse offline queries)
(Slopes in ANY order -> use Li Chao Tree) */
struct CHT {
  struct Line {
    ll m, c;
    ll eval(ll x) const { return m * x + c; }
  };
  vector<Line> lines; bool is_max; int ptr = 0;
  CHT(bool is_max = true) : is_max(is_max) {}
  bool bad(const Line& l1, const Line& l2,
           const Line& l3) {
    return (__int128)(l1.c - l2.c) * (l3.m - l2.m) >=
           (__int128)(l2.c - l3.c) * (l2.m - l1.m);
  }
  void add(ll m, ll c) {
    if (!is_max) { m = -m; c = -c; }
    Line l = {m, c};
    while (!lines.empty() && lines.back().m == l.m) {
      if (lines.back().c >= l.c) return;
      lines.pop_back();
    }
    while (lines.size() >= 2 &&
        bad(lines[lines.size() - 2], lines.back(), l))
      lines.pop_back();
    lines.push_back(l);
  }
  ll query(ll x) const {
    assert(!lines.empty());
    int l = 0, r = lines.size() - 1;
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (lines[mid].eval(x) < lines[mid + 1].eval(x))
        l = mid + 1;
      else r = mid;
    }
    return is_max ? lines[l].eval(x)
                  : -lines[l].eval(x);
  }
  ll query_monotonic(ll x) {
    assert(!lines.empty());
    ptr = min(ptr, (int)lines.size() - 1);
    while (ptr + 1 < lines.size() &&
           lines[ptr].eval(x) < lines[ptr + 1].eval(x))
      ptr++;
    return is_max ? lines[ptr].eval(x)
                  : -lines[ptr].eval(x);
  }
};
