// Offline range queries, O((n + q) sqrt n * add cost)
// Edit add / del / answer. Queries 0-indexed [l, r]
struct Query { int l, r, idx; };
const int BLK = 450; // ~ n / sqrt(q)
int cnt[1000005], cur = 0; // example: # distinct
vector<int> a;
void add(int i) { if (cnt[a[i]]++ == 0) cur++; }
void del(int i) { if (--cnt[a[i]] == 0) cur--; }
vector<int> mo(vector<Query> qs) {
  sort(qs.begin(), qs.end(), [](Query& x, Query& y) {
    if (x.l / BLK != y.l / BLK) return x.l < y.l;
    // odd-even trick: alternate r direction
    return (x.l / BLK & 1) ? x.r > y.r : x.r < y.r;
  });
  vector<int> ans(qs.size());
  int L = 0, R = -1;
  for (auto& q : qs) {
    while (R < q.r) add(++R);
    while (L > q.l) add(--L);
    while (R > q.r) del(R--);
    while (L < q.l) del(L++);
    ans[q.idx] = cur;
  }
  return ans;
}
