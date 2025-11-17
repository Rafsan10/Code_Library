constexpr int N = 100005;
i64 arr[N], seg[4 * N];

i64 combine(i64 l, i64 r) { return l + r; }
void build(int ind, int low, int high) {
  if (low == high) {
    seg[ind] = arr[low];
    return;
  }
  int mid = (low + high) / 2;
  build(2 * ind, low, mid);
  build(2 * ind + 1, mid + 1, high);
  seg[ind] = combine(seg[2 * ind], seg[2 * ind + 1]);
}
i64 query(int ind, int low, int high, int l, int r) {
  if (low >= l && high <= r) return seg[ind];
  if (low > r || high < l) return 0;  // check it!
  int mid = (low + high) / 2;
  i64 left = query(2 * ind, low, mid, l, r);
  i64 right = query(2 * ind + 1, mid + 1, high, l, r);
  return combine(left, right);
}
void update(int ind, int low, int high, int node, int val) {
  if (low == high) {
    seg[ind] = val;
    return;
  }
  int mid = (low + high) / 2;
  if (low <= node && node <= mid)
    update(2 * ind, low, mid, node, val);
  else
    update(2 * ind + 1, mid + 1, high, node, val);
  seg[ind] = combine(seg[2 * ind], seg[2 * ind + 1]);
}
