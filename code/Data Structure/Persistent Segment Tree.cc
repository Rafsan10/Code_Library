#include <bits/stdc++.h>
using namespace std;
#define i64 long long
#ifdef ONPC
#include "mydebug.h"
#else
#define debug(...) 1
#endif

const int N = 30000 + 5;
int arr[N];
struct Node {
	int val;
	Node* lc;
	Node* rc;
	Node() {
		lc = NULL;
		rc = NULL;
	}
};
Node* versions[N];

Node* build(int l, int r) {
	Node* node = new Node();
	if (l == r) {
		node->val = 0;
		return node;
	}
	int mid = (l + r) / 2;
	node->lc = build(l, mid);
	node->rc = build(mid + 1, r);
	node->val = node->lc->val + node->rc->val;
	return node;
}

int query(Node* node, int l, int r, int ql, int qr) {
	if (l > qr || r < ql) return 0;
	if (ql <= l && r <= qr) {
		return node->val;
	}
	int mid = (l + r) / 2;
	int left = query(node->lc, l, mid, ql, qr);
	int right = query(node->rc, mid + 1, r, ql, qr);
	return left + right;
}

Node* update(Node* node, int l, int r, int ind, int val) {
	Node* newnode = new Node();
	if (l == r) {
		newnode->val = node->val + val;
		return newnode;
	}
	int mid = (l + r) / 2;
	if (l <= ind && ind <= mid) {
		newnode->lc = update(node->lc, l, mid, ind, val);
		newnode->rc = node->rc;
	} else {
		newnode->lc = node->lc;
		newnode->rc = update(node->rc, mid + 1, r, ind, val);
	}
	newnode->val = newnode->lc->val + newnode->rc->val;
	return newnode;
}

void solve() {
	int n;
	cin >> n;
	vector<int> comp;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		comp.push_back(arr[i]);
	}

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	int sz = comp.size();

	for (int i = 1; i <= n; i++) {
		arr[i] = lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin();
	}

	versions[0] = build(0, sz - 1);

	for (int v = 1; v <= n; v++) {
		versions[v] = update(versions[v - 1], 0, sz - 1, arr[v], +1);
	}

	int q;
	cin >> q;
	vector<int> ans(q + 1);
	for (int i = 1; i <= q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		int l = a ^ ans[i - 1];
		int r = b ^ ans[i - 1];
		int k = c ^ ans[i - 1];
		l = max(1, l);
		r = min(n, r);
		if (l > r) {
			ans[i] = 0;
			continue;
		}
		k = upper_bound(comp.begin(), comp.end(), k) - comp.begin();
		if (k >= sz) {
			ans[i] = 0;
			continue;
		}
		ans[i] = query(versions[r], 0, sz - 1, k, sz - 1) - query(versions[l - 1], 0, sz - 1, k, sz - 1);
	}
	for (int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
}

