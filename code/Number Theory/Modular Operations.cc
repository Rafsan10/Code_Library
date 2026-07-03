int add(int x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    if (x < 0) x += mod;
    return x;
}
int mul(int x, int y) {
    return (x%mod) * 1LL * (y%mod) % mod;
}
int divide(int x, int y) {
    return mul(x, power(y, mod - 2));
}
