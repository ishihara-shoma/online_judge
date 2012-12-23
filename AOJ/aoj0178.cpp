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

bool field[5010][5];

void put(int dir, int len, int col) {
  if(dir == 2) {
    int p = 5000;
    while(!field[p][col] && p >= 0) p--;
    p++;
    REP(i, len) field[p + i][col] = true;
  } else {
    int p = -1;
    REP(i, len) {
      int t = 5000;
      while(!field[t][col + i] && t >= 0) t--;
      p = max(p, ++t);
    }
    REP(i, len) field[p][col + i] = true;
  }
}

bool filled(int row) {
  bool res = true;
  REP(i, 5) res &= field[row][i];
  return res;
}

bool empty(int row) {
  bool res = true;
  REP(i, 5) res &= !field[row][i];
  return res;
}

void update(int row) {
  int p;
  for(p = row + 1; !empty(p); p++) {
    REP(i, 5) field[p - 1][i] = field[p][i];
  }
  // REP(i, 5) field[p][i] = false;
}

int main() {

  int N;
  while(~scanf("%d", &N) && N) {

    memset(field, false, sizeof(field));

    REP(i, N) {
      int d, p ,q;
      scanf("%d%d%d", &d, &p, &q);
      put(d, p, q - 1);
      REP(j, 5000) {
        if(empty(j)) break;
        while(filled(j)) update(j);
      }
    }

    int res = 0;
    REP(i, 5000) REP(j, 5) if(field[i][j]) res++;
    printf("%d\n", res);
  }

  return 0;
}
