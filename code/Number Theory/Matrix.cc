// Matrix mod MOD (for real matrices / inverse use Gauss)
const ll MOD = 1e9 + 7; // change if necessary
struct Matrix {
  int R, C;
  vector<vector<ll>> mat;
  Matrix(int R, int C, bool identity = false)
      : R(R), C(C), mat(R, vector<ll>(C, 0)) {
    if (identity) for (int i = 0; i < R; i++) mat[i][i] = 1;
  }
  Matrix operator+(const Matrix& o) const {
    Matrix res(R, C);
    for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
        res.mat[i][j] = (mat[i][j] + o.mat[i][j]) % MOD;
    return res;
  }
  Matrix operator-(const Matrix& o) const {
    Matrix res(R, C);
    for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
        res.mat[i][j] = (mat[i][j] - o.mat[i][j] + MOD) % MOD;
    return res;
  }
  Matrix operator*(const Matrix& o) const {
    Matrix res(R, o.C);
    for (int i = 0; i < R; i++)
      for (int k = 0; k < C; k++) {
        if (mat[i][k] == 0) continue;
        for (int j = 0; j < o.C; j++)
          res.mat[i][j] =
              (res.mat[i][j] + mat[i][k] * o.mat[k][j]) % MOD;
      }
    return res;
  }
  Matrix pow(ll e) const { // square matrix only
    Matrix res(R, R, true), b = *this;
    for (; e > 0; e >>= 1, b = b * b)
      if (e & 1) res = res * b;
    return res;
  }
};
// Fibonacci: Matrix base(2, 2); base.mat = {{1, 1}, {1, 0}};
// F(n) = base.pow(n).mat[0][1]   (F(0) = 0, F(1) = 1)
