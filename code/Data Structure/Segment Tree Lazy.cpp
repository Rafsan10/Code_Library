const int N = 1e5 + 5;
i64 arr[N], seg[N << 2], lz[N << 2];

i64 combine(i64 l, i64 r) {
	return l + r;
}
void push(int node, int l, int r) {
	if (lz[node] == 0) return;
	int mid = (l + r) >> 1;
	lz[node << 1] += lz[node];
	seg[node << 1] += lz[node] * (mid - l + 1);
	lz[node << 1 | 1] += lz[node];
	seg[node << 1 | 1] += lz[node] * (r - mid);
	lz[node] = 0;
}
void build(int node, int l, int r) {
	if(l == r) {
		seg[node] = arr[l];
		lz[node] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(node << 1, l, mid);
	build(node << 1 | 1, mid + 1, r);
	seg[node] = combine(seg[node << 1], seg[node << 1 | 1]);
}
void update(int node, int l, int r, int ql, int qr, int val) {
	if(qr < l || r < ql) return;
	if(ql <= l && r <= qr) {
		seg[node] += 1LL * val * (r - l + 1);	// check it!
		lz[node] += val;
		return;
	}
	push(node, l, r);
	int mid = (l + r) >> 1;
	update(node << 1, l, mid, ql, qr, val);
	update(node << 1 | 1, mid + 1, r, ql, qr, val);
	seg[node] = combine(seg[node << 1], seg[node << 1 | 1]);
}
i64 query(int node, int l, int r, int ql, int qr) {
	if(qr < l || r < ql) return 0; // check it!
	if(ql <= l && r <= qr) return seg[node];
	push(node, l, r);
	int mid = (l + r) >> 1;
	return combine(query(node << 1, l, mid, ql, qr), query(node << 1 | 1, mid + 1, r, ql, qr));
}
