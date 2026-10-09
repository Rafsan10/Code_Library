/*INITIALIZATION & INSERTION RULES:
- Max Query: `CHT cht(true);`  --> Slopes MUST be added INCREASING  (m1 <= m2 <= m3)
- Min Query: `CHT cht(false);` --> Slopes MUST be added DECREASING  (m1 >= m2 >= m3)
 *QUERY RULES:
- `query(x)`: O(log N) for ANY x. -> USE THIS BY DEFAULT TO AVOID BUGS.
- `query_monotonic(x)`: O(1).     -> ONLY use if queries 'x' are INCREASING!
*(If queries 'x' are decreasing, just use query(x) or reverse the offline queries)*
 */
struct CHT {
    struct Line {
        long long m, c;
        long long eval(long long x) const { return m * x + c; }
    };
    vector<Line> lines; bool is_max; int ptr = 0;
    CHT(bool is_max = true) : is_max(is_max) {}
    bool bad(const Line& l1, const Line& l2, const Line& l3) {
        return (__int128)(l1.c - l2.c) * (l3.m - l2.m) >= (__int128)(l2.c - l3.c) * (l2.m - l1.m);
    }
    void add(long long m, long long c) {
        if (!is_max) { m = -m; c = -c; }
        Line l = {m, c};
        while (!lines.empty() && lines.back().m == l.m) {
            if (lines.back().c >= l.c) return;
            lines.pop_back();
        }
        while (lines.size() >= 2 && bad(lines[lines.size() - 2], lines.back(), l))
            lines.pop_back();
        lines.push_back(l);
    }
    long long query(long long x) const {
        assert(!lines.empty());
        int l = 0, r = lines.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (lines[mid].eval(x) < lines[mid + 1].eval(x)) l = mid + 1;
            else r = mid;
        }
        return is_max ? lines[l].eval(x) : -lines[l].eval(x);
    }
    long long query_monotonic(long long x) {
        assert(!lines.empty());
        ptr = min(ptr, (int)lines.size() - 1);
        while (ptr + 1 < lines.size() && lines[ptr].eval(x) < lines[ptr + 1].eval(x)) ptr++;
        return is_max ? lines[ptr].eval(x) : -lines[ptr].eval(x);
    }
};