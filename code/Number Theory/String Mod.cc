// (big number given as string) % a
ll strMod(const string& num, ll a) {
  ll res = 0;
  for (char c : num) res = (res * 10 + (c - '0')) % a;
  return res;
}
