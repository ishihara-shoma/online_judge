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
#include <cmath>
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

struct UnionFind {
  vector<int> v;
  int root(int x) {
    return v[x] < 0 ? x : v[x] = root(v[x]);
  }
  bool union_set(int x, int y) {
    x = root(x); y = root(y);
    if(x == y) return false;
    if(v[y] < v[x]) swap(x, y);
    v[x] += v[y];
    v[y] = x;
    return true;
  }
  bool find_set(int x, int y) {
    return root(x) == root(y);
  }
  UnionFind(int n): v(n, -1){}
};

int main() {

  int T;
  scanf("%d", &T);

  while(T--) {
    int N;
    scanf("%d", &N);
    
    vector<PII> islands(N);
    REP(i, N) scanf("%d%d", &islands[i].first, &islands[i].second);

    double res = 1e10;

    REP(k, N) {

      priority_queue< pair<double, PII> > q;
      REP(i, N) REPN(j, i + 1, N) {
        if(i == k || j == k) continue;
        const double dx = islands[i].first - islands[j].first;
        const double dy = islands[i].second - islands[j].second;
        const double cost = sqrt(dx * dx + dy * dy);
        q.push(make_pair(-cost, PII(i, j)));
      }

      UnionFind u(N);
      double sum = 0;

      while(!q.empty()) {
        const double ccost = -q.top().first;
        const PII e = q.top().second;
        // printf("%d--%d %f\n", e.first, e.second, ccost);
        q.pop();
        if(u.union_set(e.first, e.second)) sum += ccost;
      }

      res = min(res, sum);
      // printf("sum = %f ----------------\n", sum);
    }

    printf("%.2f\n", res);
  }

  return 0;
}
