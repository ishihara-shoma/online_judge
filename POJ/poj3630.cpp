#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()

int main() {

  ios::sync_with_stdio(false);

  int T;
  cin >> T;

  while(T--) {
    int N;
    cin >> N;

    vector<string> pn(N);
    REP(i, N) cin >> pn[i];

    sort(ALL(pn));

    bool flag = true;
    REP(i, N - 1) {

      if(pn[i].length() >= pn[i + 1].length()) continue;

      bool f = true;
      REP(j, pn[i].length()) f &= pn[i][j] == pn[i + 1][j];

      flag &= !f;
      if(!flag) break;
    }

    cout << (flag ? "YES" : "NO") << endl;
  }

  return 0;
}
