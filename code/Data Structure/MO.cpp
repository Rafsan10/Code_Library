const int N = 1e6 + 5;
int arr[N], freq[N], cnt = 0;

void remove(int idx) {
	int v = arr[idx];
	freq[v]--;
	if (freq[v] == 0) cnt--;
}
void add(int idx) {
	int v = arr[idx];
	freq[v]++;
	if (freq[v] == 1) cnt++;
}
int get_answer() {
	return cnt;
}

int block_size = 700;

struct Query {
	int l, r, idx;
	bool operator<(Query other) const {
		if (l / block_size != other.l / block_size) return l / block_size < other.l / block_size;
		return r < other.r;
	}
};

vector<int> mo_s_algorithm(vector<Query> queries) {
	vector<int> answers(queries.size());
	sort(queries.begin(), queries.end());

	// TODO: initialize data structure

	int cur_l = 0;
	int cur_r = -1;
	// invariant: data structure will always reflect the range [cur_l, cur_r]
	for (Query q : queries) {
		while (cur_l > q.l) {
			cur_l--;
			add(cur_l);
		}
		while (cur_r < q.r) {
			cur_r++;
			add(cur_r);
		}
		while (cur_l < q.l) {
			remove(cur_l);
			cur_l++;
		}
		while (cur_r > q.r) {
			remove(cur_r);
			cur_r--;
		}
		answers[q.idx] = get_answer();
	}
	return answers;
}

