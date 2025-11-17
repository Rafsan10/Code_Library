constexpr int N = 1000005;

void Divisors(int n) {
  int sum = 1, total = 1;
  int mnP = INT_MAX, mxP = INT_MIN, cntP = 0, totalP = 0;
  for (int i = 0; i < N && Prime[i] * Prime[i] <= n; i++) {
    if (n % Prime[i] == 0) {
      mnP = min(mnP, Prime[i]);
      mxP = max(mnP, Prime[i]);
      int k = 0;
      cntP++;
      while (n % Prime[i] == 0) {
        k++;
        n /= Prime[i];
      }

      sum *= (k + 1);  // NOD
      totalP += k;
      int s = 0, p = 1;
      while (k-- >= 0) {
        s += p;
        p *= Prime[i];
      };
      total *= s;  // SOD
    }
  }
  if (n > 1) {
    cntP++, totalP++;
    sum *= 2;
    total *= (1 + n);
    mnP = min(mnP, n);
    mxP = max(mnP, n);
  }
  cout << mnP << " " << mxP << " " << cntP << " " << totalP << " " << sum << " "
       << total << "\n";
}
