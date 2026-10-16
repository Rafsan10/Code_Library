// primes < N. bitset: 1e7 -> 1.2 MB (int array: 40 MB)
const int N = 1e7 + 3;
vector<int> primes;
bitset<N> notprime;
void sieve() {
  notprime[0] = notprime[1] = 1;
  for (ll i = 2; i < N; i++) {
    if (notprime[i]) continue;
    primes.push_back(i);
    for (ll j = i * i; j < N; j += i) notprime[j] = 1;
  }
}
