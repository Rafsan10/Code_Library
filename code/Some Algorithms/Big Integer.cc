// Non-negative big integers as decimal strings
struct BigInteger {
  string str;
  // Constructor to initialize
  // BigInteger with a string
  BigInteger(string s) { str = s; }
  // Overload + operator to add
  // two BigInteger objects
  BigInteger operator+(const BigInteger& b) {
    string a = str, c = b.str;
    int alen = a.length(), clen = c.length();
    int n = max(alen, clen);
    if (alen > clen)
      c.insert(0, alen - clen, '0');
    else if (alen < clen)
      a.insert(0, clen - alen, '0');
    string res(n + 1, '0');
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
      int digit = (a[i] - '0') + (c[i] - '0') + carry;
      carry = digit / 10;
      res[i + 1] = digit % 10 + '0';
    }
    if (carry == 1) {
      res[0] = '1';
      return BigInteger(res);
    } else
      return BigInteger(res.substr(1));
  }
  // returns |a - b|
  BigInteger operator-(const BigInteger& b) {
    string a = str;
    string c = b.str;
    int alen = a.length(), clen = c.length();
    int n = max(alen, clen);
    if (alen > clen)
      c.insert(0, alen - clen, '0');
    else if (alen < clen)
      a.insert(0, clen - alen, '0');
    if (a < c) {
      swap(a, c);
      swap(alen, clen);
    }
    string res(n, '0');
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
      int digit = (a[i] - '0') - (c[i] - '0') - carry;
      if (digit < 0)
        digit += 10, carry = 1;
      else
        carry = 0;
      res[i] = digit + '0';
    }
    // remove leading zeros
    int i = 0;
    while (i < n && res[i] == '0') i++;
    if (i == n) return BigInteger("0");
    return BigInteger(res.substr(i));
  }
  // Overload * operator to multiply
  // two BigInteger objects
  BigInteger operator*(const BigInteger& b) {
    string a = str, c = b.str;
    int alen = a.length(), clen = c.length();
    int n = alen + clen;
    string res(n, '0');
    for (int i = alen - 1; i >= 0; i--) {
      int carry = 0;
      for (int j = clen - 1; j >= 0; j--) {
        int digit = (a[i] - '0') * (c[j] - '0')
                    + (res[i + j + 1] - '0') + carry;
        carry = digit / 10;
        res[i + j + 1] = digit % 10 + '0';
      }
      res[i] += carry;
    }
    int i = 0;
    while (i < n && res[i] == '0') i++;
    if (i == n) return BigInteger("0");
    return BigInteger(res.substr(i));
  }
  // divide by small d > 0, r = remainder
  BigInteger divSmall(ll d, ll& r) const {
    string q; r = 0;
    for (char ch : str) {
      r = r * 10 + (ch - '0');
      q += char('0' + r / d); r %= d;
    }
    size_t k = q.find_first_not_of('0');
    return BigInteger(k == string::npos ? "0" : q.substr(k));
  }
  // Overload << operator to output
  // BigInteger object
  friend ostream& operator<<(ostream& out,
                             const BigInteger& b) {
    out << b.str;
    return out;
  }
};