bitset<100005> bs = 1;
for (auto i : a) {
  // if sum s was possible, now s + i is also possible
  bs |= (bs << i);
}
cout << bs.count() - 1 << endl;
