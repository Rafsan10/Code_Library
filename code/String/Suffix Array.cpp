struct SuffixArray {
	// p suffix array 1 base, 0 index for dollar
	// rank will show 1 index value
	// 0 base suffix array -> suf[rank[i] - 1] = i
	vector<int> p, c, rank, lcp;
	vector<vector<int>> st;
	SuffixArray(string const& s) {
		build_suffix(s + char(1));
		build_rank(p.size());
		build_lcp(s + char(1));
		build_sparse_table(lcp.size());
	}
	void build_suffix(string const& s) {
		int n = s.size();
		const int MX_ASCII = 256;
		vector<int> cnt(max(MX_ASCII, n), 0);
		p.resize(n); c.resize(n);
		for (int i = 0; i < n; i++) cnt[s[i]]++;
		for (int i=1; i<MX_ASCII; i++) cnt[i]+=cnt[i-1];
		for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
		c[p[0]] = 0;
		int classes = 1;
		for (int i = 1; i < n; i++) {
			if (s[p[i]] != s[p[i-1]]) classes++;
			c[p[i]] = classes - 1;
		}
		vector<int> pn(n), cn(n);
		for (int h = 0; (1 << h) < n; ++h) {
			for (int i = 0; i < n; i++) {
				pn[i] = p[i] - (1 << h);
				if (pn[i] < 0) pn[i] += n;
			}
			fill(cnt.begin(), cnt.begin() + classes, 0);
			for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
			for (int i=1; i<classes; i++) cnt[i]+=cnt[i-1];
			for (int i=n-1;i>=0;i--) p[--cnt[c[pn[i]]]]=pn[i];
			cn[p[0]] = 0; classes = 1;
			for (int i = 1; i < n; i++) {
				pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
				pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
				if (cur != prev) ++classes;
				cn[p[i]] = classes - 1;
			}
			c.swap(cn);
		}
	}
	void build_rank(int n) {
		rank.resize(n, 0);
		for (int i = 0; i < n; i++) rank[p[i]] = i;
	}
	void build_lcp(string const& s) {
		int n = s.size(), k = 0;
		lcp.resize(n - 1, 0);
		for (int i = 0; i < n; i++) {
			if (rank[i] == n - 1) {
				k = 0;
				continue;
			}
			int j = p[rank[i] + 1];
			while (i + k < n && j + k < n && s[i+k] == s[j+k])
				k++;
			lcp[rank[i]] = k;
			if (k) k--;
		}
	}
	void build_sparse_table(int n) {
		int lim = __lg(n);
		st.resize(lim + 1, vector<int>(n)); st[0] = lcp;
		for (int k = 1; k <= lim; k++)
			for (int i = 0; i + (1 << k) <= n; i++)
				st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
	}
	int get_lcp(int i) { return lcp[i]; }
	int get_lcp(int i, int j) {
		if (j < i) swap(i, j);
		j--; /*for lcp from i to j we don't need last lcp*/
		int K = __lg(j - i + 1);
		return min(st[K][i], st[K][j - (1 << K) + 1]);
	}
	// Compare two substrings (l1, r1) and (l2, r2)
	int compare(int l1, int r1, int l2, int r2) {
		int len1 = r1 - l1 + 1;
		int len2 = r2 - l2 + 1;
		int pos1 = rank[l1];
		int pos2 = rank[l2];
		if (pos1 == pos2) {
			if (len1 != len2) return len1 < len2 ? -1 : 1;
			return 0;
		}
		int common = get_lcp(min(pos1, pos2), max(pos1, pos2));
		int compare_len = min(min(len1, len2), common);
		if (compare_len == len1 && compare_len == len2) return 0;
		if (compare_len == len1) return -1;
		if (compare_len == len2) return 1;
		return pos1 < pos2 ? -1 : 1;
	}
};
// s.compare(suf[mid], min(n - suf[mid], m), t) -> -1(small), 0(equal), 1(large)
