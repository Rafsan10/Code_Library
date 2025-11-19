/*
https://codeforces.com/gym/106107/problem/B
We need to count "good subarrays" [l, r] where:
1. Length >= 2
2. a[l] exists somewhere in b[l...r]
3. a[r] does NOT exist in b[l...r]
*/

#include <bits/stdc++.h>
using namespace std;
#define i64 long long
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int N = 5e5 + 5;
i64 fenwick[N];

void update(int ind, int val) {
  while (ind < N) {
    fenwick[ind] += val;
    ind += ind & -ind;
  }
}
i64 query(int ind) {
  i64 sum = 0;
  while (ind > 0) {
    sum += fenwick[ind];
    ind -= ind & -ind;
  }
  return sum;
}
void solve() {
	int n;
	cin >> n;
	vector<int> comp;
	vector<int> a(n + 1), b(n + 1);
	gp_hash_table<int, vector<int>> mp;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		mp[b[i]].push_back(i);
	}
	vector<int> rend(n + 1, n + 1);
	for (int i = 1; i <= n; i++) {
		if (mp[a[i]].empty()) continue;
		auto it = lower_bound(mp[a[i]].begin(), mp[a[i]].end(), i);
		if (it == mp[a[i]].end()) continue;
		rend[i] = max(i + 1, *it); // length >= 2, l < r
	}
	vector<vector<int>> active(n + 2);
	for (int i = 1; i <= n; i++) {
		if (rend[i] <= n) {
			active[rend[i]].push_back(i); // i to rend[i] is a segment
		}
	}
	gp_hash_table<int, int> last;
	i64 seg_count = 0, ans = 0;
	for (int r = 1; r <= n; r++) {
		last[b[r]] = r;
		for (auto l : active[r]) {
			update(l, 1);
			seg_count++;
		}
		int last_pos = (last.find(a[r]) != last.end()) ? last[a[r]] : 0;
		i64 bad = query(last_pos);
		ans += seg_count - bad;
	}
	cout << ans << '\n';

	// clear fenwick tree
	for (int r = 1; r <= n; r++) {
		for (auto l : active[r]) update(l, -1);
	}
}
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		// cout << "Case " << i << ": ";
		solve();
	}
}