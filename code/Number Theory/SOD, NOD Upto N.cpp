int SOD_upto_N(int N) { // sqrt(N)
  int res = 0;
  for (int i = 1; i <= N; i++) {
    int j = N / (N / i);  // Last number with same quotient
    res += (N / i) * (i + j) * (j - i + 1) / 2;
    i = j;
  }
  return res;
}
int NOD_upto_N(ll N) { // sqrt(N)
  int res = 0;
  int u = sqrt(N);
  for (int i = 1; i <= u; i++) {
    res += (N / i) - i;
  }
  res = res * 2 + u;
  return res;
}
void NOD_per_number_upto_N(int n) { // n loglog(n)
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      d[j]++;
      // d[j] += i // for sum of divisors
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << d[i] << ' ';
  }
  return 0;
}
