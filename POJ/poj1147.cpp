#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define REP(i, N) for(int i = 0; i < (int)(N); i++)

int main() {
  int N;
  scanf("%d", &N);

  int x[3030];
  REP(i, N) scanf("%d", &x[i]);

  vector<pair<int, int> > v;
  REP(i, N) v.push_back(make_pair(x[i], i));

  stable_sort(v.begin(), v.end());

  int p = 0;
  REP(i, N) { 
    printf("%d ", v[p].first);
    p = v[p].second;
  }
  printf("\n");

  return 0;
}
