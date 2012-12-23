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

string strip(string s) {
  int b = 0, e = s.length() - 1;
  while(s[b] == ' ') b++;
  while(s[e] == ' ') e--;
  return s.substr(b, e - b + 1);
}

int main() {

  int N;
  scanf(" %d ", &N);
  while(N--) {

    char line[2000] = {0};
    scanf("%[^\n]", line + 1);
    line[0] = '^';

    int M;
    scanf(" %d ", &M);

    int cursor = 0;
    REP(i, M) {

      string op, v; cin >> op;
      getline(cin, v); v = strip(v);

      if(op == "forward") {
        if(v == "char") {
          if(!line[cursor + 1]) continue;
          swap(line[cursor], line[cursor + 1]);
          cursor++;
        } else if(v == "word") {
          while(line[cursor + 1] == ' ') {
            swap(line[cursor], line[cursor + 1]);
            cursor++;
          }
          while(!(line[cursor + 1] == '\0' || line[cursor + 1] == ' ')) {
            swap(line[cursor], line[cursor + 1]);
            cursor++;
          }
        }
      } else if(op == "backward") {
        if(v == "char") {
          if(cursor == 0) continue;
          swap(line[cursor], line[cursor - 1]);
          cursor--;
        } else if(v == "word") {
          while(line[cursor - 1] == ' ') {
            swap(line[cursor], line[cursor - 1]);
            cursor--;
          }
          while(!(cursor == 0 || line[cursor - 1] == ' ')) {
            swap(line[cursor], line[cursor - 1]);
            cursor--;
          }
        }        
      } else if(op == "delete") {
        if(v == "char") {
          if(!line[cursor + 1]) continue;
          for(int i = cursor + 1; line[i] != '\0'; i++) line[i] = line[i + 1];
        } else if(v == "word") {
          int p = cursor + 1;
          while(line[p] == ' ') p++;
          if(!line[p]) continue;
          while(line[p] != ' ' && line[p] != '\0') p++;
          for(int i = cursor + 1; line[p - 1] != '\0'; i++, p++) line[i] = line[p];
        }
      } else if(op == "insert") {
        v = v.substr(1, v.length() - 2);
        int l = v.length();
        for(int i = strlen(line); i > cursor; i--) line[i + l] = line[i];
        REP(i, l) line[cursor + i] = v[i];
        line[cursor + l] = '^'; cursor += l;
      }
    }

    puts(line);
  }

  return 0;
}
