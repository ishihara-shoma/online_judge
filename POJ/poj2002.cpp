#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <complex>
using namespace std;

#define REPN(i, a, b) for(int i = (int)(a); i < (int)(b); i++)
#define RREPN(i, a, b) for(int i = (int)(b); i >= (int)(a); i--)
#define REP(i, n) REPN(i, 0, n)
#define FOR(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define ALL(c) (c).begin(), (c).end()

typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;

const int inf = INT_MAX / 3;
const double eps = 1e-8;

typedef complex<int> P;
bool cmp(const P& a, const P& b) {
  return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag());
}

P rot90(P vec) {
  return vec * P(0, 1);
}

int main() {

  int N;
  while(~scanf("%d", &N) && N) {

    vector<P> v;

    REP(i, N) {
      int x, y;
      scanf("%d%d", &x, &y);
      v.push_back(P(x, y));
    }

    sort(ALL(v), cmp);

    int res = 0;
    REP(i, N) REPN(j, i + 1, N) {
      P dir = v[j] - v[i];
      P dir2 = rot90(dir);
      if(binary_search(ALL(v), v[i] + dir2, cmp) && 
         binary_search(ALL(v), v[j] + dir2, cmp)) {
        res++;
      }
    }

    printf("%d\n", res / 2);
  }

  return 0;
}
