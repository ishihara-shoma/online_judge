#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int main() {

  const double eps = 10e-6;
 
  int T;
  scanf("%d", &T);
  vector<double> dice;
  REP(i, T) {
    int N, M;
    scanf("%d%d", &N, &M);
    double exp = 0.0;
    double p = 0.0;
    REP(j, M) {
      double v, r;
      scanf("%lf%lf", &v, &r);
      exp += v * r;
      p += r;
    }
    dice.push_back(exp / p);
  }

  int P, Q;
  scanf("%d%d", &P, &Q);
  double exp = 0.0;
  double p = 0.0;
  REP(j, Q) {
    double v, r;
    scanf("%lf%lf", &v, &r);
    exp += v * r;
    p += r;
  }
  exp = exp / p;
  
  REP(i, T) {
    if(exp + eps < dice[i]) {
      printf("YES\n");
      return 0;
    }
  }
  printf("NO\n");

  return 0;
}
