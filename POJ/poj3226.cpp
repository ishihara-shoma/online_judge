#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

typedef long long Int;
const Int B = 10000;      // base (power of 10)
const int BW = 4;         // log B
const int MAXDIGIT = 100; // it can represent 4*MAXDIGIT digits (in base 10)
struct BigNum {
  Int digit[MAXDIGIT];
  int size;
  BigNum(int size = 1, Int a = 0) : size(size) {
    memset(digit, 0, sizeof(digit));
    digit[0] = a;
  }
};
const BigNum ZERO(1, 0), ONE(1, 1);

// Comparators
bool operator<(BigNum x, BigNum y) {
  if (x.size != y.size) return x.size < y.size;
  for (int i = x.size-1; i >= 0; --i)
    if (x.digit[i] != y.digit[i]) return x.digit[i] < y.digit[i];
  return false;
}
bool operator >(BigNum x, BigNum y) { return y < x; }
bool operator<=(BigNum x, BigNum y) { return !(y < x); }
bool operator>=(BigNum x, BigNum y) { return !(x < y); }
bool operator!=(BigNum x, BigNum y) { return x < y || y < x; }
bool operator==(BigNum x, BigNum y) { return !(x < y) && !(y < x); }

// Utilities
BigNum normal(BigNum x) {
  Int c = 0;
  for (int i = 0; i < x.size; ++i) {
    while (x.digit[i] < 0)
      x.digit[i+1] -= 1, x.digit[i] += B;
    Int a = x.digit[i] + c;
    x.digit[i] = a % B;
    c          = a / B;
  }
  for (; c > 0; c /= B) x.digit[x.size++] = c % B;
  while (x.size > 1 && x.digit[x.size-1] == 0) --x.size;
  return x;
}
BigNum convert(Int a) {
  return normal(BigNum(1, a));
}
BigNum convert(const string &s) {
  BigNum x;
  int i = s.size() % BW;
  if (i > 0) i -= BW;
  for (; i < (int)s.size(); i += BW) {
    Int a = 0;
    for (int j = 0; j < BW; ++j)
      a = 10 * a + (i + j >= 0 ? s[i+j] - '0' : 0);
    x.digit[x.size++] = a;
  }
  reverse(x.digit, x.digit+x.size);
  return normal(x);
}
// Input/Output
ostream &operator<<(ostream &os, BigNum x) {
  os << x.digit[x.size-1];
  for (int i = x.size-2; i >= 0; --i)
    os << setw(BW) << setfill('0') << x.digit[i];
  return os;
}
istream &operator>>(istream &is, BigNum &x) {
  string s; is >> s;
  x = convert(s);
  return is;
}

// Basic Operations 
BigNum operator+(BigNum x, BigNum y) {
  if (x.size < y.size) x.size = y.size;
  for (int i = 0; i < y.size; ++i)
    x.digit[i] += y.digit[i];
  return normal(x);
}
BigNum operator-(BigNum x, BigNum y) {
  assert(x >= y);
  for (int i = 0; i < y.size; ++i)
    x.digit[i] -= y.digit[i];
  return normal(x);
}
BigNum operator*(BigNum x, BigNum y) {
  BigNum z(x.size + y.size);
  for (int i = 0; i < x.size; ++i)
    for (int j = 0; j < y.size; ++j)
      z.digit[i+j] += x.digit[i] * y.digit[j];
  return normal(z);
}
BigNum operator*(BigNum x, Int a) {
  for (int i = 0; i < x.size; ++i)
    x.digit[i] *= a;
  return normal(x);
}
pair<BigNum, Int> divmod(BigNum x, Int a) {
  Int c = 0, t;
  for (int i = x.size-1; i >= 0; --i) {
    t          = B * c + x.digit[i];
    x.digit[i] = t / a;
    c          = t % a;
  }
  return pair<BigNum, Int>(normal(x), c);
}
BigNum operator/(BigNum x, Int a) {
  return divmod(x, a).first;
}
Int operator%(BigNum x, Int a) {
  return divmod(x, a).second;
}
pair<BigNum, BigNum> divmod(BigNum x, BigNum y) {
  if (x.size < y.size) return pair<BigNum, BigNum>(ZERO, x);
  int F = B / (y.digit[y.size-1] + 1); // multiplying good-factor
  x = x * F; y = y * F;
  BigNum z(x.size - y.size + 1);
  for (int k = z.size-1, i = x.size-1; k >= 0; --k, --i) {
    z.digit[k]  = (i+1 < x.size ? x.digit[i+1] : 0) * B + x.digit[i];
    z.digit[k] /= y.digit[y.size-1];
    BigNum t(k + y.size);
    for (int m = 0; m < y.size; ++m)
      t.digit[k+m] = z.digit[k] * y.digit[m];
    t = normal(t);
    while (x < t) {
      z.digit[k] -= 1;
      for (int m = 0; m < y.size; ++m)
        t.digit[k+m] -= y.digit[m];
      t = normal(t);
    }
    x = x - t;
  }
  return pair<BigNum, BigNum>(normal(z), x / F);
}
BigNum operator/(BigNum x, BigNum y) {
  return divmod(x, y).first;
}
BigNum operator%(BigNum x, BigNum y) {
  return divmod(x, y).second;
}

#include<iostream>
#include<algorithm>
using namespace std;

int main(){

  int N;
  while(cin >> N && N){
    bool used[32];
    memset(used, false, sizeof(used));

    char buf[32];
    BigNum res(1, 0);
    cin >> buf;

    for(int i = 0, j = 26; i < N; i++, j--){

      res = res * j;

      int c = 0;
      REP(k, buf[i] - 'A') if(used[k]) c++;

      res = res + BigNum(1, (int)(buf[i] - 'A') - c);
      used[buf[i] - 'A'] = true;
    }
    cout << res << endl;
  }

  return 0;
}

