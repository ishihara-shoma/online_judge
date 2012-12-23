#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-7;

#define ALL(c) (c).begin(), (c).end()
#define REP(i, n) for(int i = 0; i < (int)(n); i++)

typedef pair<int, int> PII;
typedef pair<double, PII> E;

struct UnionFind {
  vector<int> d;
  UnionFind(int n): d(n, -1){}
  int root(int x) {
    return d[x] < 0 ? x : d[x] = root(d[x]);
  }
  bool unionSet(int x, int y) {
    x = root(x); y = root(y);
    if(x != y) {
      if(d[x] > d[y]) swap(x, y);
      d[x] += d[y];
      d[y] = x;
    }
    return x != y;
  }
  bool findSet(int x, int y) {
    return root(x) == root(y); 
  }
};

int main() {

  int T;
  scanf("%d", &T);
  REP(tc, T) {
    int S, D;
    scanf("%d%d", &S, &D);
    vector<PII> p;
    REP(i, D) {
      int x, y;
      scanf("%d%d", &x, &y);
      p.push_back(PII(x, y));
    }
    vector<E> edges;
    REP(i, D) REP(j, D) {
      if(i == j) continue;
      double dx = p[i].first - p[j].first;
      double dy = p[i].second - p[j].second;
      double d = sqrt(dx * dx + dy * dy);
      edges.push_back(E(d, PII(i, j)));
    }
    sort(ALL(edges));
    UnionFind uf(D);
    double res = 0;
    int c = 0;
    REP(i, edges.size()) {
      if(uf.unionSet(edges[i].second.first, edges[i].second.second)) {
        res = edges[i].first;
        c++;
        if(c == D - S) break;
      }
    }

    printf("%.2f\n", res);
  }

  return 0;
}
