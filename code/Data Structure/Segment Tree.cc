const int N = 100005;
ll arr[N];

// Maximum subarray sum in range [l, r]
struct Node {
	ll sum, pref, suff, ans;
	Node() {
		sum = 0;
		pref = suff = ans = -inf;
	}
};
Node seg[4 * N];
Node combine(Node l, Node r) {
	Node res;
	res.sum = l.sum + r.sum;
	res.pref = max(l.pref, l.sum + r.pref);
	res.suff = max(r.suff, r.sum + l.suff);
	res.ans = max({l.ans, r.ans, res.pref, res.suff, res.sum});
	res.ans = max(res.ans, l.suff + r.pref);
	return res;
}
void build(int node, int low, int high) {
  if (low == high) {
    seg[node].sum = arr[low];
    return;
  }
  int mid = (low + high) / 2;
  build(2 * node, low, mid);
  build(2 * node + 1, mid + 1, high);
  seg[node] = combine(seg[2 * node], seg[2 * node + 1]);
}
Node query(int node, int low, int high, int l, int r) {
  if (low >= l && high <= r) return seg[node];
  if (low > r || high < l) return Node();  // check it!
  int mid = (low + high) / 2;
  Node left = query(2 * node, low, mid, l, r);
  Node right = query(2 * node + 1, mid + 1, high, l, r);
  return combine(left, right);
}
void update(int node, int low, int high, int pos, int val) {
  if (low == high) {
    seg[node].sum = val;
    return;
  }
  int mid = (low + high) / 2;
  if (low <= pos && pos <= mid)
    update(2 * node, low, mid, pos, val);
  else
    update(2 * node + 1, mid + 1, high, pos, val);
  seg[node] = combine(seg[2 * node], seg[2 * node + 1]);
}

