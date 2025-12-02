template <typename T>
struct Gauss {
    int bits;
    vector<T> table;
    int rank = 0;  // track number of basis/independent vectors
    Gauss() : bits(60) { table = vector<T>(bits, 0); }
    Gauss(int _bits) : bits(_bits) { table = vector<T>(bits, 0); }
    // Return rank/size of basis
    int basis_size() { return rank; }
    // Check if x can be obtained from the basis
    bool can(T x) {
        for (int i = bits - 1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (!table[i]) return false;
            x ^= table[i];
        }
        return true;
    }
    void add(T x) {
        for (int i = bits - 1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;  // Skip if bit i is 0
            if (!table[i]) {
                table[i] = x;
                rank++;
                return;
            }
            x ^= table[i];  // Eliminate this bit using XOR
        }
        // x became 0 (linearly dependent)
    }
    T get_max_xor() {
        T ans = 0;
        for (int i = bits - 1; i >= 0; i--) {
            if ((ans ^ table[i]) > ans) {
                ans ^= table[i];
            }
        }
        return ans;
    }
};
// Gauss<long long> g(60);
// g.add(x);
// g.get_max_xor();