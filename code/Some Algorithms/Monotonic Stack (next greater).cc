for (int i = n - 1; i >= 0; i--) {
  while (!stk.empty() && v[i] >= v[stk.top()]) stk.pop();
  ind[i] = stk.empty() ? -1 : stk.top();
  stk.push(i);
}
// 3 1 5 4 10
// 2 2 4 4 -1