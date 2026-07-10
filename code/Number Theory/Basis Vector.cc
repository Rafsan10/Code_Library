// T: Data type (int or long long), B: Max bits (31 for int, 62 for long long)
template<typename T = long long, int B = 62>
struct Basis {
    T basis[B]; 
    int sz, n; //sz: Number of independent basis vectors (rank)
    Basis() {
        memset(basis, 0, sizeof(basis));
        sz = 0; n = 0;
    }
    // Inserts x into the basis. Returns true if x expanded the basis, false if it was redundant.
    bool insert(T x) {
        n++;
        for (int i = B - 1; i >= 0; i--) {
            if (x >> i & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    sz++;
                    return true;
                }
                x ^= basis[i];
            }
        }
        return false;
    }
    // Checks if there is any subset whose XOR sum equals exactly x
    bool can(T x) {
        for (int i = B - 1; i >= 0; i--) {
            x = min(x, x ^ basis[i]);
        }
        return x == 0;
    }
    // Returns the maximum subset XOR sum (can provide an initial value x)
    T max_xor(T x = 0) { 
        for (int i = B - 1; i >= 0; i--) {
            x = max(x, x ^ basis[i]);
            //x = min(x, x ^ basis[i]); //For minimum subset XOR sum
        }
        return x;
    }
    // Finds the k-th DISTINCT subset XOR sum (1-based, k=1 returns 0)
    T kth(unsigned long long k) {
        if (k < 1 || k > (1ULL << sz)) return -1;
        T x = 0;
        unsigned long long cnt = (1ULL << sz);
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                cnt >>= 1;
                if (k > cnt) { 
                    if (!(x >> i & 1)) x ^= basis[i]; // Force the bit ON
                    k -= cnt;
                } else { 
                    if (x >> i & 1) x ^= basis[i];    // Force the bit OFF
                }
            }
        }
        return x;
    }
    // Returns the number of DISTINCT subset XOR sums strictly less than x
    unsigned long long count_lt(T x) {
        if (x < 0) return 0;
        unsigned long long ans = 0, cnt = (1ULL << sz);
        T mask = 0;
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                cnt >>= 1;
                if (x >> i & 1) {
                    ans += cnt;
                    if(!(mask >> i & 1))mask^=basis[i];
                } else {
                    if (mask >> i & 1) mask ^= basis[i];
                }
            } else {
                if ((x >> i & 1) != (mask >> i & 1)) {
                    return (x >> i & 1)?ans+cnt:ans;
                }
            }
        }
        return ans;
    }
};
/* 1. SUBSET COUNTING MATH:
  - Valid combinations that XOR to 0: 2^(n - sz)
  - Valid non-empty combinations XOR to 0: (2^(n - sz)) - 1
  - If can(X) is true, ways to form X: 2^(n - sz)
  2. DISTINCT VS TOTAL SUBSETS:
  - This struct works with DISTINCT XOR sums! 
  - There are exactly (1ULL << sz) distinct XOR sums.
  - Every distinct XOR sum is formed by exactly 2^(n - sz) identical subsets.
  - If question asks for K-th out of ALL subsets:
  Pass: K = ceil(K / 2^(n - sz)) into kth() */