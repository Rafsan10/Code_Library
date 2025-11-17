// Returns largest power of p that divides n! 
int largestPower(int n, int p)  { 
    int res = 0; 

    // Calculate res = n/p + n/(p^2) + n/(p^3) + .... 
    while (n > 0) { 
        n /= p; 
        res += n; 
    } 
    return res; 
} 