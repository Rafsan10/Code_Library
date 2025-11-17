#define accuracy chrono::steady_clock::now().time_since_epoch().count()
mt19937 rng(accuracy);
int rand(int l, int r) {
  uniform_int_distribution<int> ludo(l, r);
  return ludo(rng);
}
