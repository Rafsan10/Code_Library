void catalan(int n) {
  int res = 1;
  cout << res << " ";
  for (int i = 1; i < n; i++) {
    res = (res * (4 * i - 2)) / (i + 1);
    cout << res << " ";
  }
}
