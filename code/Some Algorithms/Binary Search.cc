// Pattern 1: Finding roots
// Find x where f(x) = target
while (high - low > precision) {
  double mid = low + (high - low) / 2.0;
  if (f(mid) <= target) {
    low = mid;
  } else {
    high = mid;
  }
}

// Pattern 2: Maximizing a function
// Find x that maximizes f(x)
while (high - low > precision) {
  double mid1 = low + (high - low) / 3.0;
  double mid2 = high - (high - low) / 3.0;
  if (f(mid1) < f(mid2)) {
    low = mid1;
  } else {
    high = mid2;
  }
}

// Pattern 3: Search using fixed iterations
// Find x that satisfies condition check(x)
double low = 0.0, high = 1e9;
for (int i = 0; i < 100; i++) {
  double mid = (low + high) / 2.0;
  if (check(mid))
    low = mid;
  else
    high = mid;
}