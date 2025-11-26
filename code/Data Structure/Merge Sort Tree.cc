constexpr int N = 100005;
struct Node {
    vector<int> nums;
};
int arr[N];
Node seg[4 * N];

// Combine: Merge two sorted vectors
Node combine(Node& left, Node& right) {
    Node res;
    res.nums.resize(left.nums.size() + right.nums.size());
    merge(left.nums.begin(), left.nums.end(), right.nums.begin(),
          right.nums.end(), res.nums.begin());
    return res;
}
// O(n log n)
void build(int ind, int low, int high) {
    if (low == high) {
        seg[ind].nums = {arr[low]};  // Single element
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind, low, mid);
    build(2 * ind + 1, mid + 1, high);
    seg[ind] = combine(seg[2 * ind], seg[2 * ind + 1]);
}
// Query: Count elements <= k in range [l, r]
// O(log^2 n)
int query(int ind, int low, int high, int l, int r, int k) {
    if (low > r || high < l) return 0;  // No overlap
    if (low >= l && high <= r) {
        // Entire segment is in query range
        // Count elements <= k in this sorted segment
        auto it = upper_bound(seg[ind].nums.begin(), seg[ind].nums.end(), k);
        return it - seg[ind].nums.begin();
    }
    int mid = (low + high) / 2;
    int left = query(2 * ind, low, mid, l, r, k);
    int right = query(2 * ind + 1, mid + 1, high, l, r, k);
    return left + right;
}
