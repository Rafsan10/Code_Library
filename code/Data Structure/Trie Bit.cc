const int BT = 32;
class Node {
	public:
		Node* child[2];
		int cnt;
		Node() {
			cnt = 0;
			for (int i = 0; i < 2; i++) child[i] = NULL;
		}
};
Node *root = new Node();

void insert(Node* node, int x) {
	for (int i = BT - 1; i >= 0; i--) {
		int r = (x >> i) & 1LL;
		if (node->child[r] == NULL) node->child[r] = new Node();
		node = node->child[r];
		node->cnt++;
	}
} // insert(root, x);

int query(Node* node, int x) {
	int mx = 0;
	for (int i = BT - 1; i >= 0; i--) {
		int r = (x >> i) & 1LL;
		if (node->child[r ^ 1] == NULL || node->child[r ^ 1]->cnt == 0) {
			if (node->child[r] == NULL) return mx;
			node = node->child[r];
		} else {
			mx |= (1 << i);
			node = node->child[r ^ 1];
		}
	}
	return mx;
} // query(root, x), get max xor

void remove(Node* node, int x) {
	for (int i = BT - 1; i >= 0; i--) {
		int r = (x >> i) & 1LL;
		if (node->child[r] == NULL) return;
		node = node->child[r];
		node->cnt--;
	}
} // remove(root, x)

void clearTrie(Node* node) {
    if (node == nullptr) return;
    clearTrie(node->child[0]);
    clearTrie(node->child[1]);
    delete node;
}
// clearTrie(root), delete full trie
// root = new Node()
