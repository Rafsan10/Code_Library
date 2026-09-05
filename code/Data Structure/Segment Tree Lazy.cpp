/* 1. TO ADAPT FOR ANY PROBLEM, ONLY EDIT THESE 4 THINGS:
      - `Node` struct : Add your variables (sum, mx, pref, suff). Ensure Node() is a neutral/identity element!
      - `combine()`   : How to merge the left and right children.
      - `applySet()`  : How setting a range to `v` changes a Node. (Updates lzSet, clears lzAdd).
      - `applyAdd()`  : How adding `v` to a range changes a Node. (Updates lzAdd).
   2. NEVER TOUCH `push()`, `update()`, OR `query()`! They are mathematically bug-proof.
   3. WHY applySet CLEARS lzAdd? Overwriting a range completely destroys its previous history (adds).
   4. WHY push SET BEFORE ADD? "Set this to X, then add Y" implies Set happened first.
   5. FOR TOGGLE/XOR/INVERSION: Change `lzAdd` to `lzXor`, delete `Set` logic, update `applyAdd`.
   6. 1-BASED INDEXING: Use `seg.build(a)`, `seg.add(l, r, v)`, `seg.query(l, r)`.
*/

struct Node {
    ll sum;
    Node(ll _sum = 0) { sum = _sum; } 
};

struct LazySegTree {
    int n; vector<Node> seg; vector<ll> lzAdd, lzSet; vector<bool> hasSet;
    LazySegTree(int _n) : n(_n), seg(4*_n+5), lzAdd(4*_n+5, 0), lzSet(4*_n+5, 0), hasSet(4*_n+5, 0) {}

    Node combine(Node l, Node r) {
        Node res; res.sum = l.sum + r.sum; 
        return res;
    }
    void applySet(int node, int l, int r, ll v) {
        seg[node].sum = (ll)(r - l + 1) * v;
        lzSet[node] = v; hasSet[node] = 1; lzAdd[node] = 0;
    }
    void applyAdd(int node, int l, int r, ll v) {
        seg[node].sum += (ll)(r - l + 1) * v;
        lzAdd[node] += v;
    }
    void push(int node, int l, int r) {
        if (l == r) return;
        int mid = (l + r) >> 1, lc = node << 1, rc = node << 1 | 1;
        if (hasSet[node]) {
            applySet(lc, l, mid, lzSet[node]); applySet(rc, mid + 1, r, lzSet[node]);
            hasSet[node] = 0; 
        }
        if (lzAdd[node] != 0) {
            applyAdd(lc, l, mid, lzAdd[node]); applyAdd(rc, mid + 1, r, lzAdd[node]);
            lzAdd[node] = 0;
        }
    }
    void build(int node, int l, int r, const vector<ll>& a) {
        if (l == r) { seg[node] = Node(a[l]); return; }
        int mid = (l + r) >> 1;
        build(node<<1, l, mid, a); build(node<<1|1, mid+1, r, a);
        seg[node] = combine(seg[node<<1], seg[node<<1|1]);
    }
    void update(int node, int l, int r, int ql, int qr, ll v, int type) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) { type == 1 ? applyAdd(node, l, r, v) : applySet(node, l, r, v); return; }
        push(node, l, r);
        int mid = (l + r) >> 1;
        update(node<<1, l, mid, ql, qr, v, type); update(node<<1|1, mid+1, r, ql, qr, v, type);
        seg[node] = combine(seg[node<<1], seg[node<<1|1]);
    }
    Node query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return Node();
        if (ql <= l && r <= qr) return seg[node];
        push(node, l, r);
        int mid = (l + r) >> 1;
        return combine(query(node<<1, l, mid, ql, qr), query(node<<1|1, mid+1, r, ql, qr));
    }

    void build(const vector<ll>& a) { build(1, 1, n, a); } // Assuming 'a' is 1-indexed up to n
    void add(int l, int r, ll v) { update(1, 1, n, l, r, v, 1); }
    void set(int l, int r, ll v) { update(1, 1, n, l, r, v, 2); }
    Node query(int l, int r) { return query(1, 1, n, l, r); }
};