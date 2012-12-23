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
namespace std {
  bool operator < (const P& a, const P& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}
double cross(const P& a, const P& b) {
  return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
  return real(conj(a)*b);
}

int ccw(P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

int main() {

  int T;
  scanf("%d", &T);

  REP(tc, T) {    
    int N, ID;
    scanf("%d %d", &ID, &N);
    vector<P> v;
    int max_y = -inf, min_y = inf;
    REP(i, N) {
      int x, y;
      scanf("%d%d", &x, &y);
      v.push_back(P(x, y));
      max_y = max(max_y, y);
      min_y = min(min_y, y);
    }
    v.push_back(v[0]);
 
    vector<pair<int, PII> > res;
    for(int y = max_y - 1, l = 1, r = N - 1; y >= min_y + 1; y--) {
      while(v[l].imag() > y) l++;
      while(v[r].imag() > y) r--;
      int lm = inf, rm = inf;
      assert(v[l].imag() <= y && y <= v[l - 1].imag());
      assert(v[r].imag() <= y && y <= v[r + 1].imag());

      // printf("%d (%d, %d) - (%d, %d) / (%d, %d) - (%d, %d)\n",
      //        y,
      //        v[l - 1].real(), v[l - 1].imag(),
      //        v[l].real(), v[l].imag(),
      //        v[r + 1].real(), v[r + 1].imag(),
      //        v[r].real(), v[r].imag()
      //        );

      for(int x = max(v[l].real(), v[l - 1].real());
          x >= min(v[l].real(), v[l - 1].real()); x--) {
        if(ccw(v[l - 1], v[l], P(x, y)) == -1) {
          rm = x;
          break;
        }
        if(ccw(v[l - 1], v[l], P(x, y)) != 1) {
          // printf("hello, %d %d\n", x, y);
          rm = x - 1;
          break;
        }
      }
      for(int x = min(v[r].real(), v[r + 1].real());
          x <= max(v[r].real(), v[r + 1].real()); x++) {
        if(ccw(v[r + 1], v[r], P(x, y)) == 1) {
          lm = x;
          break;
        }
        if(ccw(v[r + 1], v[r], P(x, y)) != -1) {
          // printf("goodbye, %d %d\n", x, y);
          lm = x + 1;
          break;
        }
      }
      if(lm <= rm) res.push_back(make_pair(y, PII(lm, rm)));
    }

    printf("%d %d\n", ID, (int)res.size());
    REP(i, res.size()) {
      printf("%d %d %d\n", res[i].first, res[i].second.first, res[i].second.second);
    }
  }

  return 0;
}
