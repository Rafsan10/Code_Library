//1. LIS Length(Change lower_bound to upper_bound to allow EQUAL elements)
int LIS(vector<int>& v) {
  vector<int> seq;
  for (int x:v) { auto it = lower_bound(seq.begin(),seq.end(),x);
    if(it==seq.end()) seq.push_back(x); else *it=x; } return seq.size();
}

//2. LIS with Reconstruction
vector<int> getLIS(vector<int>& v) {
  int n=v.size(); vector<int> seq, id, p(n,-1), ans;
  for(int i=0;i<n;i++) {
    int pos = lower_bound(seq.begin(),seq.end(),v[i])-seq.begin();
    if(pos>0) p[i]=id[pos-1]; // Link current element to previous best
    if(pos==seq.size()) {seq.push_back(v[i]); id.push_back(i);}
    else {seq[pos]=v[i]; id[pos]=i;}
  }
  // Backtrack using parent array `p`
  for(int c=id.empty()?-1:id.back(); c!=-1; c=p[c]) ans.push_back(v[c]);
  reverse(ans.begin(),ans.end()); return ans;
}

//3. SEGTREE LIS WRAPPER: For Weights, Counts, and Restrictions. O(N log N)
//Assumes you have a Point Update, Range Max Query SegTree ready.
ll getLIS_SegTree(vector<int>& a, vector<ll>& w) {
  vector<int> b=a; ll ans=0;
  // Coordinate Compression: SegTree leaves [1..M] represent the SORTED VALUES
  sort(b.begin(),b.end()); b.erase(unique(b.begin(),b.end()),b.end());
  int M = b.size(); 
  //Call build(1, 1, M) here to initialize SegTree leaves to 0
  for(int i=0;i<a.size();i++) {
    // x is the 1-based compressed index of value a[i]
    int x = lower_bound(b.begin(),b.end(),a[i])-b.begin()+1;
    // 1. Strictly Increasing: query(1, 1, M, 1, x - 1)
    // 2. Non-Decreasing (equal allowed): query(1, 1, M, 1, x)
    // 3. Condition (e.g. diff >= K): Find pos of (a[i]-K) in 'b' and query up to pos
    ll mx = (x==1) ? 0 : query(1, 1, M, 1, x-1); 
    mx += w[i]; ans = max(ans, mx);
    // Update the max value ending exactly at compressed value 'x'
    update(1, 1, M, x, mx); 
  } return ans;
}