const int N = 1e7 + 3;
vector<int> primes;
int notprime[N];
void sieve() {
  primes.push_back(2);
  for (int i = 4; i < N; i += 2) {
    notprime[i] = true;
  }
  for (int i = 3; i < N; i += 2) {
    if (!notprime[i]) {
      primes.push_back(i);
      for (int j = i * i; j < N; j += 2 * i) {
        notprime[j] = true;
      }
    }
  }
}