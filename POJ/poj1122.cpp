#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define ALL(c) (c).begin(), (c).end()

typedef pair<int, int> PII;

const int inf = INT_MAX / 3;

vector<PII> G[30];

int main() {

  int N;
  scanf("%d", &N);
  REP(i, N) REP(j, N) {
    int t;
    scanf("%d", &t);
    if(t < 0 || i == j) continue;
    G[j].push_back(PII(i, t));
  }

  // REP(i, N) {
  //   FOR(e, G[i]) printf("(%d, %d) ", e->first, e->second);
  //  printf("\n");
  // }

  int loc;
  vector<int> sta;
  scanf("%d", &loc);
  --loc;
  REP(i, N) {
    int t;
    if(scanf("%d", &t) != 1) break;
    sta.push_back(--t);
  }

  // REP(i, sta.size()) printf("%d ", sta[i]);
  // printf("\n");

  priority_queue<PII> q;
  vector<int> memo(N, inf);
  vector<int> memo2(N, -1);
  q.push(PII(0, loc));
  memo[loc] = 0;
  while(!q.empty()) {    
    int cpos = q.top().second;
    int ccost = -q.top().first;
    q.pop();

    // printf("%d %d\n", cpos, ccost);

    if(memo[cpos] != ccost) continue;

    FOR(n, G[cpos]) {
      int npos = n->first;
      int ncost = n->second + ccost;
      if(memo[npos] > ncost) {
        q.push(PII(-ncost, npos));
        memo[npos] = ncost;
        memo2[npos] = cpos;
      }
    }
  }

  vector<PII> v;
  FOR(s, sta) v.push_back(PII(memo[*s], *s));
  sort(ALL(v));

  printf("Org\tDest\tTime\tPath\n");
  FOR(e, v) {
    printf("%d\t%d\t%d\t", e->second + 1, loc + 1, e->first);
    for(int pos = e->second; pos != -1; pos = memo2[pos]) {
      printf("%d\t", pos + 1);
    }
    printf("\n");
  }

  return 0;
}
