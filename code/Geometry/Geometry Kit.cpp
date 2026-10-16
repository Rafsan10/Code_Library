// T = ll for exact integer geometry, ld for real
typedef long double ld;
const ld EPS = 1e-9, PI = acosl(-1);
template <class T> struct P {
  T x, y;
  P(T x = 0, T y = 0) : x(x), y(y) {}
  P operator+(P o) const { return P(x + o.x, y + o.y);}
  P operator-(P o) const { return P(x - o.x, y - o.y);}
  P operator*(T k) const { return P(x * k, y * k); }
  P operator/(T k) const { return P(x / k, y / k); }
  bool operator<(P o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
  bool operator==(P o) const {
    return x == o.x && y == o.y;
  }
  T dot(P o) const { return x * o.x + y * o.y; }
  T cross(P o) const { return x * o.y - y * o.x; }
  T cross(P a, P b) const { // (a - this) x (b - this)
    return (a - *this).cross(b - *this);
  }
  T norm2() const { return x * x + y * y; }
  ld len() const { return sqrtl((ld)norm2()); }
  ld ang() const { return atan2l((ld)y, (ld)x); }
  P perp() const { return P(-y, x); } // rotate +90
  P rot(ld a) const { // real T only
    return P(x * cosl(a) - y * sinl(a),
             x * sinl(a) + y * cosl(a));
  }
};
using pt = P<ll>; using ptd = P<ld>;
int sgn(ll v) { return (v > 0) - (v < 0); }
int sgn(ld v) { return (v > EPS) - (v < -EPS); }
// 1: c left of a->b (ccw), -1: right, 0: collinear
template <class T> int orient(P<T> a, P<T> b, P<T> c) {
  return sgn(a.cross(b, c));
}
template <class T> bool onSeg(P<T> p, P<T> a, P<T> b) {
  return orient(a, b, p) == 0 &&
         sgn((a - p).dot(b - p)) <= 0;
}
// segments ab and cd intersect (touching counts)
template <class T>
bool segInter(P<T> a, P<T> b, P<T> c, P<T> d) {
  if (onSeg(c, a, b) || onSeg(d, a, b) ||
      onSeg(a, c, d) || onSeg(b, c, d)) return true;
  return orient(a, b, c) * orient(a, b, d) < 0 &&
         orient(c, d, a) * orient(c, d, b) < 0;
}
// intersection of LINES ab, cd (must not be parallel)
ptd lineInter(ptd a, ptd b, ptd c, ptd d) {
  ld t = (c - a).cross(d - c) / (b - a).cross(d - c);
  return a + (b - a) * t;
}
ld distLine(ptd p, ptd a, ptd b) { // line ab
  return fabsl(a.cross(b, p)) / (b - a).len();
}
ld distSeg(ptd p, ptd a, ptd b) { // segment ab
  if (a == b) return (p - a).len();
  ptd d = b - a;
  ld t = (p - a).dot(d) / d.norm2();
  t = max((ld)0, min((ld)1, t));
  return (p - (a + d * t)).len();
}
ptd project(ptd p, ptd a, ptd b) { // foot on line ab
  ptd d = b - a;
  return a + d * ((p - a).dot(d) / d.norm2());
}
// ---- Polygons (vertices in order) ----
// 2 * signed area (> 0 if CCW). Pick: A = I + B/2 - 1
template <class T> T area2(const vector<P<T>>& p) {
  T s = 0;
  for (int i = 0, n = p.size(); i < n; i++)
    s += p[i].cross(p[(i + 1) % n]);
  return s;
}
// lattice points on segment ab (incl. both ends)
ll boundaryPts(pt a, pt b) {
  return __gcd(llabs(a.x - b.x), llabs(a.y - b.y)) + 1;
}
// 1 inside, 0 on boundary, -1 outside. O(n), any simple
template <class T>
int inPoly(const vector<P<T>>& p, P<T> q) {
  int n = p.size(); bool in = false;
  for (int i = 0; i < n; i++) {
    P<T> a = p[i], b = p[(i + 1) % n];
    if (onSeg(q, a, b)) return 0;
    if ((a.y > q.y) != (b.y > q.y) &&
        (b.y > a.y) == (sgn(a.cross(b, q)) > 0))
      in = !in;
  }
  return in ? 1 : -1;
}
// Convex hull, monotone chain, CCW, no collinear pts
// (change <= 0 to < 0 to keep collinear; not if all
// points are collinear)
template <class T> vector<P<T>> hull(vector<P<T>> p) {
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size(), k = 0;
  if (n < 3) return p;
  vector<P<T>> h(2 * n);
  auto bad = [&](int i) { // not a strict left turn
    return sgn(h[k - 2].cross(h[k - 1], p[i])) <= 0;
  };
  for (int i = 0; i < n; h[k++] = p[i++])
    while (k >= 2 && bad(i)) k--;
  for (int i = n-2, t = k+1; i >= 0; h[k++] = p[i--])
    while (k >= t && bad(i)) k--;
  h.resize(k - 1);
  return h;
}
// q inside or on convex polygon h (CCW, from hull())
// O(log n)
template <class T>
bool inConvex(const vector<P<T>>& h, P<T> q) {
  int n = h.size();
  if (n == 1) return q == h[0];
  if (n == 2) return onSeg(q, h[0], h[1]);
  if (orient(h[0], h[1], q) < 0 ||
      orient(h[0], h[n - 1], q) > 0) return false;
  int l = 1, r = n - 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (orient(h[0], h[m], q) >= 0) l = m; else r = m;
  }
  return orient(h[l], h[r], q) >= 0;
}
// max squared distance between points of hull h
template <class T> T diameter2(const vector<P<T>>& h) {
  int n = h.size();
  if (n == 1) return 0;
  T best = 0;
  for (int i = 0, j = 1; i < n; i++) {
    int ni = (i + 1) % n;
    while ((h[ni] - h[i]).cross(h[(j + 1) % n] - h[j])
           > 0) j = (j + 1) % n;
    best = max({best, (h[i] - h[j]).norm2(),
                (h[ni] - h[j]).norm2()});
  }
  return best;
}
// closest pair of points, squared distance. O(n log n)
ll closestPair2(vector<pt> p) {
  sort(p.begin(), p.end());
  set<pair<ll, ll>> s; // (y, x) of points in the strip
  ll best = LLONG_MAX;
  for (int i = 0, j = 0; i < (int)p.size(); i++) {
    ll d = ceill(sqrtl((ld)best));
    while (j < i && p[i].x - p[j].x >= d)
      s.erase({p[j].y, p[j].x}), j++;
    auto it = s.lower_bound({p[i].y - d, LLONG_MIN});
    for (; it != s.end() && it->first <= p[i].y + d;
         ++it) {
      ll dx = p[i].x - it->second;
      ll dy = p[i].y - it->first;
      best = min(best, dx * dx + dy * dy);
    }
    s.insert({p[i].y, p[i].x});
  }
  return best;
}
// ---- Circles ----
ptd circumcenter(ptd a, ptd b, ptd c) {
  ptd B = b - a, C = c - a;
  ld d = 2 * B.cross(C);
  return a + ptd(C.y * B.norm2() - B.y * C.norm2(),
                 B.x * C.norm2() - C.x * B.norm2()) / d;
}
// minimum enclosing circle, expected O(n). {center, r}
pair<ptd, ld> mec(vector<ptd> p) {
  shuffle(p.begin(), p.end(), mt19937(1234));
  ptd o = p[0]; ld r = 0;
  auto out = [&](ptd q) {
    return (q - o).len() > r + EPS;
  };
  for (int i = 1; i < (int)p.size(); i++) {
    if (!out(p[i])) continue;
    o = p[i]; r = 0;
    for (int j = 0; j < i; j++) {
      if (!out(p[j])) continue;
      o = (p[i] + p[j]) / 2; r = (p[i] - o).len();
      for (int k = 0; k < j; k++) {
        if (!out(p[k])) continue;
        o = circumcenter(p[i], p[j], p[k]);
        r = (p[i] - o).len();
      }
    }
  }
  return {o, r};
}
// line ab with circle (o, r): 0, 1 or 2 points
vector<ptd> circleLine(ptd o, ld r, ptd a, ptd b) {
  ptd f = project(o, a, b);
  ld h2 = r * r - (f - o).norm2();
  if (h2 < -EPS) return {};
  ptd d = (b - a) / (b - a).len();
  d = d * sqrtl(max((ld)0, h2));
  if (h2 < EPS) return {f};
  return {f - d, f + d};
}
// circles (o1, r1), (o2, r2): intersection points
vector<ptd> circleCircle(ptd o1, ld r1, ptd o2, ld r2) {
  ptd d = o2 - o1; ld d2 = d.norm2();
  if (d2 < EPS) return {}; // concentric
  ld a = (d2 + r1 * r1 - r2 * r2) / (2 * d2);
  ld h2 = r1 * r1 - a * a * d2;
  if (h2 < -EPS) return {};
  ptd m = o1 + d * a;
  ptd off = d.perp() * sqrtl(max((ld)0, h2) / d2);
  if (h2 < EPS) return {m};
  return {m - off, m + off};
}
