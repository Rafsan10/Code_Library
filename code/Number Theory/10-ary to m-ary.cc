// base conversion, 2 <= m <= 36, n >= 0
const string DIG = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string tenToM(ll n, int m) {
  if (n == 0) return "0";
  string res;
  while (n > 0) { res += DIG[n % m]; n /= m; }
  reverse(res.begin(), res.end());
  return res;
}
ll mToTen(const string& s, int m) {
  ll res = 0;
  for (char c : s) res = res * m + DIG.find(toupper(c));
  return res;
}
