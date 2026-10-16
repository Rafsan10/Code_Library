// Auto-mod arithmetic. MOD must be PRIME for division
template <int MOD> struct Mint {
  int v;
  Mint(ll x = 0) { v = x % MOD; if (v < 0) v += MOD; }
  Mint& operator+=(Mint o) {
    if ((v += o.v) >= MOD) v -= MOD;
    return *this;
  }
  Mint& operator-=(Mint o) {
    if ((v -= o.v) < 0) v += MOD;
    return *this;
  }
  Mint& operator*=(Mint o) {
    v = 1LL * v * o.v % MOD;
    return *this;
  }
  Mint pow(ll e) const {
    Mint r = 1, b = *this;
    for (; e > 0; e >>= 1, b *= b) if (e & 1) r *= b;
    return r;
  }
  Mint inv() const { return pow(MOD - 2); }
  Mint& operator/=(Mint o) { return *this *= o.inv(); }
  friend Mint operator+(Mint a, Mint b) {return a += b;}
  friend Mint operator-(Mint a, Mint b) {return a -= b;}
  friend Mint operator*(Mint a, Mint b) {return a *= b;}
  friend Mint operator/(Mint a, Mint b) {return a /= b;}
  bool operator==(Mint o) const { return v == o.v; }
  friend ostream& operator<<(ostream& os, Mint a) {
    return os << a.v;
  }
};
using mint = Mint<1000000007>; // or 998244353
// mint a = 5, b = 3; cout << a / b << a.pow(10);
