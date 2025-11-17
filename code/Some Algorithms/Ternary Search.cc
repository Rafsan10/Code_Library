double ternary_search(double l, double r) {
  double eps = 1e-9;  // error limit
  while (r - l > eps) {
    double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
    double f1 = f(m1), f2 = f(m2);  // evaluates the function at m1, m2
    if (f1 < f2) l = m1;
    else r = m2;
  }
  return f(l);  // return the maximum of f(x) in [l, r]
}
