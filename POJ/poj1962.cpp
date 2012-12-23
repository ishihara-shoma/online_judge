#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

struct ExUnionFind {
  vector<int> d, ct, dist;
  ExUnionFind(int N): d(N, -1), dist(N, 0) {}
  int root(int x) {
    if(d[x] < 0) return x;
    int parent = d[x];
    int v = root(d[x]);
    if(parent >= 0) dist[x] += dist[parent];
    return d[x] = v;
  }
  bool unionSet(int x, int y) {
    root(y);
    int dd = abs(x - y) % 1000 + dist[y];
    x = root(x), y = root(y);
    if(x != y) {
      dist[x] += dd;
      d[y] += d[x];
      d[x] = y;
    }

    //    printf("[");
    //    REP(i, d.size()) printf("%d, ", dist[i]);
    //    printf("]\n");

    return x != y;
  }
  bool findSet(int x, int y) {
    return root(x) == root(y);
  }
};

int main() {

  int T;
  scanf("%d", &T);

  while(T--) {
    int N;
    scanf("%d", &N);

    ExUnionFind uf(N);

    char op;
    while(~scanf(" %c ", &op) && op != 'O') {
      if(op == 'E') {
        int v;
        scanf("%d", &v);
        uf.root(v - 1);
        printf("%d\n", uf.dist[v - 1]);
      } else {
        int u, v;
        scanf("%d%d", &u, &v);
        uf.unionSet(u - 1, v - 1);
      }
    }
  }

  return 0;
}
