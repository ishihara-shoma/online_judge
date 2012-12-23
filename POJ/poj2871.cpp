#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int main() {

  double x0, x;
  scanf("%lf", &x0);
  while(~scanf("%lf", &x) && x < 999) {
    printf("%.2f\n", x - x0);
    x0 = x;
  }
  printf("End of Output\n");

  return 0;
}
