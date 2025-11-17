vector<int> v = {7, 3, 5, 3, 6, 2, 9, 8};
vector<int> seq;
for (auto i : v) {
  auto id = lower_bound(seq.begin(), seq.end(), i);
  if (id == seq.end())
    seq.push_back(i);
  else
    seq[id - seq.begin()] = i;
}
cout << seq.size() << endl;

void lis(vector<int> &v) {
	int n = v.size();
	vector<int> dp(n + 1, 1), hash(n);
	int mx = 1, lastInd = 0;
	for (int i = 0; i < n; i++) {
		hash[i] = i;
		for (int prev = 0; prev < i; prev++) {
			if (v[i] > v[prev] && 1 + dp[prev] > dp[i]) {
				dp[i] = 1 + dp[prev];
				hash[i] = prev;
			}
		}
		if (mx < dp[i]) {
			mx = dp[i];
			lastInd = i;
		}
	}
	vector<int> printSeq;
	printSeq.push_back(v[lastInd]);
	while (hash[lastInd] != lastInd) {
		lastInd = hash[lastInd];
		printSeq.push_back(v[lastInd]);
	}
	reverse(printSeq.begin(), printSeq.end());
	cout << mx << "\n";
	for (int i : printSeq) cout << i << " ";
	cout << "\n";

	// nlogn. segment tree max
	vector<int> dp(n + 1);

	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		int mx = query(0, 1, N, 1, a[i] - 1);
		dp[i] = max(dp[i], mx + 1);
		update(0, 1, N, a[i], dp[i]);
	}
	int ans = *max_element(dp.begin(), dp.end());
}
