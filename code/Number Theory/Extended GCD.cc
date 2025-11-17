// return {x,y} such that ax+by=gcd(a,b)
int exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
    	x = 1; y = 0;  	return a;	}
	int g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
} // bezout's identity: a.x +b.y = gcd(a,b)
