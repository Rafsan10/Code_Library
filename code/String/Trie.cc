const int N = 26;
char BASE = 'A';
class Node {
 public:
  int EoW;
  Node* child[N];
  Node() {
    EoW = 0;
    for (int i = 0; i < N; i++) child[i] = NULL;
  }
};
Node* root = new Node();

void insert(Node* node, string s) {
  for (size_t i = 0; i < s.size(); i++) {
    int r = s[i] - BASE;
    if (node->child[r] == NULL) node->child[r] = new Node();
    node = node->child[r];
  }
  node->EoW += 1;
}  // insert(root, s);

int search(Node* node, string s) {
  for (size_t i = 0; i < s.size(); i++) {
    int r = s[i] - BASE;
    if (node->child[r] == NULL) return 0;
    node = node->child[r];
  }
  return node->EoW;
}  // search(root, s);

void print(Node* node, string s = "") {
  if (node->EoW) cout << s << "\n";
  for (int i = 0; i < N; i++) {
    if (node->child[i] != NULL) {
      char c = i + BASE;
      print(node->child[i], s + c);
    }
  }
}  // print whole trie

void remove(Node* node, string s) {
  for (size_t i = 0; i < s.size(); i++) {
    int r = s[i] - base;
    if (node->child[r] == NULL) return;
    node = node->child[r];
  }
  node->EoW--;
}  // remove(root, s)

void delete_trie(Node* node) {
  for (int i = 0; i < N; i++) {
    if (node->child[i] != NULL) delete_trie(node->child[i]);
  }
  delete node;
}  // delete full trie
