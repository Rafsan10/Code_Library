bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_first()<<endl; // prints 1
bs._Find_next(idx): first set bit after idx. e.g.:
bitset<17>BS;
BS[1] = BS[7] = 1;
// prints 7,7
cout<<BS._Find_next(1)<<','<<BS._Find_next(3)<<endl;
So this code will print all of the set bits of BS:
for(int i = BS._Find_first(); i < BS.size();
    i = BS._Find_next(i))
    cout<<i<<endl;
// If no set bit after idx, BS._Find_next(idx) returns
// BS.size(); same for BS._Find_first() if BS is clear