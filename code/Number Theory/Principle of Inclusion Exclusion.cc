// count numbers in [1, n] not divisible by any of the
// integers in the given array a. It is n - (div by one
// number - div by two numbers + div by three - ...)
int PIE(int div[], int n, int num) {
  int sum = 0;
  for (int msk = 1; msk < (1 << n); ++msk) {
    int bit_cnt = 0;
    int cur_lcm = 1;
    for (int i = 0; i < n; ++i) {
      if (msk & (1 << i)) {
        ++bit_cnt;
        cur_lcm = LCM(cur_lcm, div[i]);
      }
    }
    int cur = num / cur_lcm;
    if (bit_cnt & 1) sum += cur;
    else sum -= cur;
  }
  return num - sum;
}