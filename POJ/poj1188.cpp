#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()

int main() {

  int N;

  while(~scanf("%d", &N) && N) {
    int p[3], l[3];
    scanf("%d%d%d%d", &p[0], &p[1], &p[2], &l[2]);
    l[0] = l[1] = l[2];
    REP(i, N - 1) {
      int pp[3], ll;
      scanf("%d%d%d%d", &pp[0], &pp[1], &pp[2], &ll);
      REP(j, 3) {
        l[j] = min(pp[j] + ll, p[j] + l[j]) - max(p[j], pp[j]);
        l[j] = max(l[j], 0);
        p[j] = max(p[j], pp[j]);
      }
    }
    printf("%d\n", l[0] * l[1] * l[2]);
  }

  return 0;
}
