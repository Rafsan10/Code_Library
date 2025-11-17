int cntOnes(int n) {
  int cnt = 0;
  for (int i = 1; i <= n; i <<= 1) {
    int x = (n + 1) / (i << 1);
    cnt += x * i;
    if ((n + 1) % i && n & i) cnt += (n + 1) % i;
  }
  return cnt;
}
