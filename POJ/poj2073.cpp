#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()
typedef pair<int, int> PII;
typedef vector<int> VI;

const int dx[] = { 1, 0,-1, 0, 0};
const int dy[] = { 0, 1, 0,-1, 0};

int W, H, N, T;

bool out_of_range(int x, int y) {
  return x < 0 || y < 0 || x >= W || y >= H;
}

int main() {

  for(int tc = 1; ~scanf("%d%d%d%d", &W, &H, &N, &T) 
        && (W || H || N || T); tc++) {

    W++; H++;

    vector< vector<PII> > ter(N);
    REP(i, N) REP(j, T) {
      int x, y;
      scanf("%d%d", &x, &y);
      ter[i].push_back(PII(x, y));
    }

    vector<VI> field(W, VI(H, 1));

    REP(i, T) {
      REP(j, N) {
        int tx = ter[j][i].first, ty = ter[j][i].second;
        REP(k, 5) {
          int nx = tx + dx[k], ny = ty + dy[k];
          if(out_of_range(nx, ny)) continue;
          field[nx][ny] = 0;
        }
      }
      // if(i == T - 1) break;
      REP(x, W) REP(y, H) {
        if(field[x][y]) REP(k, 5) {
            int nx = x + dx[k], ny = y + dy[k];
            if(out_of_range(nx, ny)) continue;
            REP(j, N) {
              int tx = ter[j][i].first, ty = ter[j][i].second;
              REP(kk, 5) {
                int ntx = tx + dx[kk], nty = ty + dy[kk];
                if(ntx == nx && nty == ny) goto next;
              }
            }
            field[nx][ny] = 1;
          next:;
          }
      }
    }

    printf("Observation Set %d\n", tc);
    int c = 0;
    REP(y, H) REP(x, W) {
      if(field[x][y]) {
        if(c % 8) putchar(' ');
        printf("(%d,%d)", x, y);
        c++;
        if(c % 8 == 0) putchar('\n');
      }
    }
    if(c == 0) printf("No possible locations\n");
    if(c % 8) printf("\n");
  }

  return 0;
}
