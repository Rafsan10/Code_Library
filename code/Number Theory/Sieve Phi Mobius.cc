const int N = 5000005;
int phi[N];
unsigned long long phiSum[N];
void phiCalc() {
  for (int i = 1; i < N; i++) phi[i] = i;
  for (int i = 2; i < N; i++) {
	if (phi[i] == i) {
  	for (int j = i; j < N; j += i) {
    	phi[j] -= phi[j] / i;  	}	}  }
  for (int i = 2; i < N; i++) {
	phiSum[i] = (unsigned long long)phi[i] * (unsigned long long)phi[i] + phiSum[i - 1];
  }
}
