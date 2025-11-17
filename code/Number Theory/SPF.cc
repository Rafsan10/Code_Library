int spf[N];
void buildSpf() {
  for (int i = 2; i < N; i++) {
    spf[i] = i;
  }
  for (int i = 2; 1LL * i * i < N; i++)
    if (spf[i] == i)
      for (int j = i * i; j < N; j += i)
        if (spf[j] == j) spf[j] = i;
}
