struct Node {
    ll sum;
    Node() { sum = 0;} 
};

struct ST {
    int n; vector<Node> seg;
    ST(int _n) : n(_n), seg(4*_n+5) {}

    Node combine(Node l, Node r) {
        Node res; res.sum = l.sum + r.sum;
        return res;
    }
    void build(int node, int l, int r, const vector<ll>& a) {
        if (l == r) { seg[node].sum = a[l]; return; }
        int mid = (l + r) >> 1;
        build(node<<1, l, mid, a); build(node<<1|1, mid+1, r, a);
        seg[node] = combine(seg[node<<1], seg[node<<1|1]);
    }
    void update(int node, int l, int r, int pos, ll v) {
        if (l == r) { seg[node].sum = v; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(node<<1, l, mid, pos, v);
        else update(node<<1|1, mid+1, r, pos, v);
        seg[node] = combine(seg[node<<1], seg[node<<1|1]);
    }
    Node query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return Node();
        if (ql <= l && r <= qr) return seg[node];
        int mid = (l + r) >> 1;
        return combine(query(node<<1, l, mid, ql, qr), query(node<<1|1, mid+1, r, ql, qr));
    }
};
