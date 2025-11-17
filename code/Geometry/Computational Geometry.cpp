typedef long long int T;
typedef double Tf;
Tf eps = 1e-10;

// int sgn(Tf x)
// {
//     if (fabs(x) < eps) return 0;
//     if (x > 0) return 1;
//     return -1;
// }

int sgn(T x) {
  if (x == 0) return 0;
  if (x > 0)
    return 1;
  else
    return -1;
}
struct point {
  T x, y;
  point(T x = 0, T y = 0) {
    this->x = x;
    this->y = y;
  }
  point operator+(point p) { return point(x + p.x, y + p.y); }
  point operator-(point p) { return point(x - p.x, y - p.y); }
  Tf len() { return sqrt(x * x + y * y); }
  T norm() { return x * x + y * y; }
  point operator*(T a) { return point(x * a, y * a); }
  point operator/(T a) { return point(x / a, y / a); }
  // integer
  bool operator==(point p) { return p.x == x && p.y == y; }
  // float
  // bool operator==(point p) {
  //     return sgn(p.x - x) == 0 && sgn(p.y - y) == 0;
  // }
  bool operator<(point p) {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
  // float
  // bool operator<(point p) {
  //     if (sgn(p.x - x) == 0) return sgn(y - p.y) == -1;
  //     return sgn(x - p.x) == -1;
  // }
};
T dot(point a, point b) { return a.x * b.x + a.y * b.y; }
T cross(point a, point b) { return a.x * b.y - b.x * a.y; }
T orien(point a, point b, point c) { return cross(a - b, a - c); }

Tf area(point a, point b, point c) { return abs(orien(a, b, c)) / (Tf)2; }

struct segment {
  point a, b;
  bool onSegment(point p) {
    if (sgn(orien(a, b, p)) != 0) return false;
    return sgn(dot(p - a, p - b)) <= 0;
  }
  bool intersection(segment s) {
    if (onSegment(s.a)) return true;
    if (onSegment(s.b)) return true;
    if (s.onSegment(a)) return true;
    if (s.onSegment(b)) return true;
    int s1 = sgn(orien(a, b, s.a));
    int s2 = sgn(orien(a, b, s.b));
    int s3 = sgn(orien(s.a, s.b, a));
    int s4 = sgn(orien(s.a, s.b, b));
    if (s1 * s2 < 0 && s3 * s4 < 0) return true;
    return false;
  }
};
ostream& operator<<(ostream& os, point p) {
  return os << "(" << p.x << "," << p.y << ")";
}
