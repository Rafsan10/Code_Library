solve(int* arr, int N, int L, int R) {
  int LCM = arr[0];
  for (int i = 1; i < N; i++) {
    LCM = (LCM * arr[i]) / (__gcd(LCM, arr[i]));
  }
  if ((LCM < L && LCM * 2 > R) || LCM > R) {
    return;
  }
  int k = (L / LCM) * LCM;
  if (k < L) k = k + LCM;
  for (int i = k; i <= R; i = i + LCM) cout << i << ' ';
}
