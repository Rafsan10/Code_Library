struct Congruence{
  long long a, m;
};
ll CRT(vector<Congruence> const &congruences){
  ll M = 1;
  for (auto const &congruence : congruences)
    M *= congruence.m;
  ll solution = 0;
  for (auto const &congruence : congruences){
    ll a_i = congruence.a;
    ll M_i = M / congruence.m;
    ll N_i = mod_inv(M_i, congruence.m);
    solution = (solution + a_i * M_i % M * N_i) % M;
  }
  return solution;
}