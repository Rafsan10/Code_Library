struct point {
  ll x, y;
  bool operator==(point const& t) const { return (x == t.x && y == t.y); }
};
int orientation(point a, point b, point c) {
  ll d = (c.y - b.y) * (b.x - a.x) - (c.x - b.x) * (b.y - a.y);
  if (d < 0)
    return -1;  // clockwise
  else if (d > 0)
    return 1;  // anticlockwise
  return 0;    // collinear
}

bool clockwise(point a, point b, point c, bool include_collinear) {
  int o = orientation(a, b, c);
  if (o < 0) return true;
  if (o > 0) return false;
  return include_collinear;
}
bool collinear(point a, point b, point c) { return orientation(a, b, c) == 0; }
bool cmp_points(point& p1, point& p2) {
  return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
}
ll distance_sq(point a, point b) {
  ll d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  return d;
}

void print(vector<point>& v) {
  for (auto it : v) {
    cout << "(" << it.x << ", " << it.y << ")" << "\n";
  }
}
vector<point> convex_hull(vector<point>& points,
                          bool include_collinear = false) {
  int sz = (int)points.size();
  point p0 = *min_element(points.begin(), points.end(), cmp_points);
  vector<point> convex_hull_vector = points;
  sort(convex_hull_vector.begin(), convex_hull_vector.end(),
       [&p0](const point& p1, const point& p2) {
         int o = orientation(p0, p1, p2);
         if (o == 0) {
           return distance_sq(p0, p1) < distance_sq(p0, p2);
         }
         return o < 0;
       });
  if (include_collinear) {
    int idx = sz - 1;
    while (idx >= 0 &&
           collinear(p0, convex_hull_vector[idx], convex_hull_vector.back()))
      idx--;
    reverse(convex_hull_vector.begin() + idx + 1, convex_hull_vector.end());
  }
  vector<point> st;
  for (int i = 0; i < sz; i++) {
    while (st.size() >= 2 &&
           !clockwise(st[st.size() - 2], st.back(), convex_hull_vector[i],
                      include_collinear)) {
      st.pop_back();
    }
    st.push_back(convex_hull_vector[i]);
  }
  if (!include_collinear && st.size() == 2 && st[0] == st[1]) {
    st.pop_back();
  }
  return st;
}
