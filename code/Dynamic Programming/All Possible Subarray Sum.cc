bitset<100005> bs = 1;
for (auto i : a) {
  bs |= (bs << i);  // if previous 1 value pos is possible now ith bit or ith sm
                    // is also possible
}
cout << bs.count() - 1 << endl;
