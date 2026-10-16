// Polynomial multiplication O(n log n)
// NTT: exact mod 998244353 (root 3). Any mod: FFT with
// 15-bit split, or CRT of 3 NTT primes.
const int MODN = 998244353, ROOT = 3;
ll pw(ll b, ll e) {
  ll r = 1; b %= MODN;
  for (; e; e >>= 1, b = b * b % MODN)
    if (e & 1) r = r * b % MODN;
  return r;
}
void ntt(vector<ll>& a, bool inv) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    ll w = pw(ROOT, (MODN - 1) / len);
    if (inv) w = pw(w, MODN - 2);
    for (int i = 0; i < n; i += len) {
      ll wn = 1;
      for (int j = 0; j < len / 2; j++) {
        ll u = a[i + j];
        ll v = a[i + j + len / 2] * wn % MODN;
        a[i + j] = (u + v) % MODN;
        a[i + j + len / 2] = (u - v + MODN) % MODN;
        wn = wn * w % MODN;
      }
    }
  }
  if (inv) {
    ll ni = pw(n, MODN - 2);
    for (ll& x : a) x = x * ni % MODN;
  }
}
vector<ll> multiply(vector<ll> a, vector<ll> b) {
  if (a.empty() || b.empty()) return {};
  int need = a.size() + b.size() - 1, n = 1;
  while (n < need) n <<= 1;
  a.resize(n); b.resize(n);
  ntt(a, false); ntt(b, false);
  for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MODN;
  ntt(a, true); a.resize(need);
  return a;
}
// FFT (doubles): exact if result coefficients < ~1e15
typedef complex<double> cd;
void fft(vector<cd>& a, bool inv) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * acos(-1) / len * (inv ? -1 : 1);
    cd w(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd wn(1);
      for (int j = 0; j < len / 2; j++, wn *= w) {
        cd u = a[i + j], v = a[i + j + len / 2] * wn;
        a[i + j] = u + v; a[i + j + len / 2] = u - v;
      }
    }
  }
  if (inv) for (cd& x : a) x /= n;
}
vector<ll> multiplyFFT(vector<ll>& a, vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  int need = a.size() + b.size() - 1, n = 1;
  while (n < need) n <<= 1;
  vector<cd> fa(a.begin(), a.end());
  vector<cd> fb(b.begin(), b.end());
  fa.resize(n); fb.resize(n);
  fft(fa, false); fft(fb, false);
  for (int i = 0; i < n; i++) fa[i] *= fb[i];
  fft(fa, true);
  vector<ll> res(need);
  for (int i = 0; i < need; i++)
    res[i] = llround(fa[i].real());
  return res;
}
