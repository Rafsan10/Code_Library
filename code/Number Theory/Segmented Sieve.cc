void segmentedSieve(int L, int R) {
  bool isPrime[R - L + 1];
  for (int i = 0; i <= R - L + 1; i++) isPrime[i] = true;
  if (L == 1) isPrime[0] = false;
  for (int i = 0; primes[i] * primes[i] <= R; i++) {
    int curPrime = primes[i];
    int base = curPrime * curPrime;
    if (base < L) {
      base = ((L + curPrime - 1) / curPrime) * curPrime;
    }
    for (int j = base; j <= R; j += curPrime) isPrime[j - L] = false;
  }
  for (int i = 0; i <= R - L; i++) {
    if (isPrime[i] == true) cout << L + i << '\n';
  }
  cout << '\n';
}
