// Persistent segtree over compressed values [0, sz).
// root[i] = tree of a[1..i]; [l,r] = root[r]-root[l-1]
// kth smallest in a[l..r], count <= x: O(log n)
const int MAXN = 2e5 + 5, LOG = 20;
int lc[MAXN * LOG], rc[MAXN * LOG], cnt[MAXN * LOG];
int nodes;
int root[MAXN];
int update(int prev, int l, int r, int pos) { // +1
  int cur = ++nodes;
  lc[cur] = lc[prev], rc[cur] = rc[prev];
  cnt[cur] = cnt[prev] + 1;
  if (l == r) return cur;
  int mid = (l + r) / 2;
  if (pos <= mid)
    lc[cur] = update(lc[prev], l, mid, pos);
  else rc[cur] = update(rc[prev], mid + 1, r, pos);
  return cur;
}
// k-th smallest (1-based) -> index in comp
// u = root[r], v = root[l-1]
int kth(int u, int v, int l, int r, int k) {
  if (l == r) return l;
  int mid = (l + r) / 2, left = cnt[lc[u]] - cnt[lc[v]];
  if (k <= left) return kth(lc[u], lc[v], l, mid, k);
  return kth(rc[u], rc[v], mid + 1, r, k - left);
}
// how many values with index <= pos
int countLE(int u, int v, int l, int r, int pos) {
  if (pos < l) return 0;
  if (r <= pos) return cnt[u] - cnt[v];
  int mid = (l + r) / 2;
  return countLE(lc[u], lc[v], l, mid, pos)
       + countLE(rc[u], rc[v], mid + 1, r, pos);
}
/* node 0 = empty tree (all zero). Usage:
comp = sorted unique a; sz = comp.size();
for i = 1..n: root[i] = update(root[i-1], 0, sz - 1,
                lower_bound(comp, a[i]) index);
k-th in [l,r]: comp[kth(root[r], root[l-1], 0, sz-1, k)]
#(<= x) in [l,r]: p = upper_bound(comp, x) - 1, (p < 0:
  answer 0) countLE(root[r], root[l-1], 0, sz-1, p)
*/
