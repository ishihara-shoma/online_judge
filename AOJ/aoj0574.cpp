#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>
using namespace std;

typedef pair<int, int> PII;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()

int dp[5010][2];

int main() {

  int N, M;
  scanf("%d%d", &N, &M);

  vector< pair<PII, int> > g;
  REP(i, M) {
    int x, y, s;
    scanf("%d%d%d", &x, &y, &s);
    g.push_back(make_pair(PII(--x, --y), s + 1));
  }

  sort(ALL(g));
  memset(dp, 0, sizeof(dp));

  int res = 0;
  int p = 0;
  REP(i, N) {
    for(; p < (int)g.size() && g[p].first.first == i; p++) {
      int x = g[p].first.first;
      int y = g[p].first.second;
      dp[y][x % 2] = max(dp[y][x % 2], g[p].second);
      // printf("p = %d\n", p);
    }
    REP(j, i + 1) {
      dp[j][i % 2] = max(dp[j][i % 2], dp[j][(i + 1) % 2] - 1);
      if(j > 0) dp[j][i % 2] = max(dp[j][i % 2], dp[j - 1][(i + 1) % 2] - 1);
      if(dp[j][i % 2] > 0) res++;
    }    
    REP(j, N) dp[j][(i + 1) % 2] = 0;
  }

  printf("%d\n", res);

  return 0;
}
