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
#define rev(s) string((s).rbegin(), (s).rend())

typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;

const int inf = INT_MAX / 3;
const double eps = 1e-8;

string B[10];
int memo[10], dir[10];

// place, board, direction
bool check(int p, int k, int d) {
  bool res = true;
  REP(i, 10) if(memo[i] != -1) {
    if((p % 2) ^ (memo[i] % 2)) {
      int c1 = dir[i] > 0 ? p / 2 : 4 - p / 2;
      int c2 = d > 0 ? memo[i] / 2 : 4 - memo[i] / 2;
      res &= (B[i][c1] - '0') ^ (B[k][c2] - '0');
    }
  }
  return res;
}

int dfs(int p) {
  if(p == 10) return 1;

  int res = 0;
  REP(i, 10) if(memo[i] == -1) {
    if(check(p, i, 1)) {
      memo[i] = p; dir[i] = 1;
      res += dfs(p + 1);
      memo[i] = -1; dir[i] = 0;
    }
    if(B[i] != rev(B[i]) && check(p, i, -1)) {
      memo[i] = p; dir[i] = -1;
      res += dfs(p + 1);
      memo[i] = -1; dir[i] = 0;
    }
  }
  return res;
}

int main() {

  string buf;
  while(getline(cin, buf) && buf != "END") {
    stringstream ss(buf);
    memset(memo, -1, sizeof(memo));
    memset(dir, 0, sizeof(dir));
    REP(i, 10) ss >> B[i];
    printf("%d\n", dfs(0) / 8);
  }

  return 0;
}
