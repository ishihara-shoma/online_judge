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

int main() {

  int N;
  for(int tc = 1; ~scanf(" %d ", &N) && N; tc++) {

    vector<double> x(N), y(N);
    REP(i, N) scanf("%lf%lf", &x[i], &y[i]);
    REPN(i, 1,  N) x[i] -= x[0], y[i] -= y[0];
  
    double res = 0;
    REPN(i, 1, N - 1) res += -(x[i] * y[i + 1] - y[i] * x[i + 1]) / 2.0;

    printf("%d %.1lf\n", tc, res);
  }

  return 0;
}
