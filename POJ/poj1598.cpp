#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

#define REP(i, N) for(int i = 0; i < (int)(N); i++)
#define ALL(c) (c).begin(), (c).end()

char Tolower(char c) { return tolower(c); }

int main() {

  ios::sync_with_stdio(false);

  int K, E;
  for(int tc = 1; cin >> K >> E; tc++) {
  
    vector<string> dic(K);
    REP(i, K) cin >> dic[i];

    cin.clear(); cin.ignore();

    vector<string> sentence(E);
    vector<int> excuse(E, 0);
    int res = 0;
    REP(i, E) {
      getline(cin, sentence[i]);
      string s(sentence[i]);
      transform(ALL(s), s.begin(), Tolower);
      REP(j, K) {
        int p = 0;
        while((p = s.find(dic[j], p)) != string::npos) {
          if((p == 0 || !isalpha(s[p - 1])) &&
             (p + dic[j].length() >= s.length() || !isalpha(s[p + dic[j].length()]))) {
            excuse[i]++;
          }
          p++;
        }
      }
      res = max(res, excuse[i]);
    }
    
    cout << "Excuse Set #" << tc << endl;
    REP(i, E) if(excuse[i] == res) cout << sentence[i] << endl;

    cout << endl;
  }

  return 0;
}
