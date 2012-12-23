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

VI G[1000];

int main() {

  int N, K;
  scanf("%d%d", &N, &K);

  REP(i, N) {
    int s, d;
    scanf("%d%d", &s, &d);
    s--; d--;
    G[s].push_back(d);
    // G[d].push_back(s);
  }

  queue<int> q;
  VI memo(K, inf);
  VI bk(K, inf);
  memo[0] = 0;
  q.push(0);
  while(true) {
    if(q.empty()) {
      printf("-1\n");
      break;
    }

    int cur = q.front();
    q.pop();

    if(cur == K - 1) {
      VI res;
      for(int p = cur; p != inf; p = bk[p]) {
        res.push_back(p);
      }
      reverse(ALL(res));
      printf("%d\n", (int)res.size());
      REP(i, res.size()) printf("%d\n", res[i] + 1);
      break;
    }

    REP(i, G[cur].size()) {
      if(memo[G[cur][i]] > memo[cur] + 1) {
        q.push(G[cur][i]);
        memo[G[cur][i]] = memo[cur] + 1;
        bk[G[cur][i]] = cur;
      }
    }
  }

  return 0;
}
