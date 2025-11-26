// https://www.spoj.com/problems/GIVEAWAY/
// 0 l r k : count of numbers >= k in [l,r]
// 1 idx val : update a[idx] = val

const int N = 5e5 + 5, BLK = 700;
vector<int> block[N / BLK + 5];
int get_block(int idx) { return idx / BLK; }

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        block[get_block(i)].push_back(a[i]);
    }
    int last_blk = get_block(n - 1);
    for (int i = 0; i <= last_blk; i++) {
        sort(block[i].begin(), block[i].end());
    }
    int q;
    cin >> q;
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 0) {  
            // query
            // O(sqrt(n) log(sqrt(n)))
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            int bl = get_block(l);
            int br = get_block(r);
            int ans = 0;
            if (bl == br) {  
                // just brute force
                for (int i = l; i <= r; i++) {
                    if (a[i] >= k) ans++;
                }
            } else {
                for (int i = l; get_block(i) < (bl + 1); i++) {
                    if (a[i] >= k) ans++;
                }
                for (int i = r; get_block(i) > (br - 1); i--) {
                    if (a[i] >= k) ans++;
                }
                for (int b = bl + 1; b < br; b++) {
                    // sorted vector, [1, 5, 10, 20], k = 6, ans += 2
                    auto it = lower_bound(block[b].begin(), block[b].end(), k);
                    ans += block[b].end() - it;
                }
            }
            cout << ans << '\n';
        } else {  
            // update
            // O(sqrt(n) log(sqrt(n)))
            int idx, val;
            cin >> idx >> val;
            idx--;
            int old = a[idx];
            int b = get_block(idx);
            auto it = lower_bound(block[b].begin(), block[b].end(), old);
            *it = val;
            sort(block[b].begin(), block[b].end());
            a[idx] = val;
        }
    }
}

