// It just counts the number of ways to place the order.
const int N = 32;
int mark[N][N];
char grid[N][N];
int n, cnt;
void fillup(int row, int col) {
  for (int i = 1; i < n - row + 1; i++) {
    mark[row + i][col]++;
    if (col - i >= 0) mark[row + i][col - i]++;
    if (col + i < n) mark[row + i][col + i]++;
  }
}
void fillout(int row, int col) {
  for (int i = 1; i < n - row + 1; i++) {
    mark[row + i][col]--;
    if (col - i >= 0) mark[row + i][col - i]--;
    if (col + i < n) mark[row + i][col + i]--;
  }
}
void find_way(int row) {
  if (row == n) {
    cnt++;
    return;
  }
  for (int j = 0; j < n; j++) {
    if (grid[row][j] == '*' or mark[row][j]) continue;
    fillup(row, j);
    find_way(row + 1);
    fillout(row, j);
  }
}
// input in grid. call find_way(0);
