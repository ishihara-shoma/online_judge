#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <string>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define FOR(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define ALL(c) (c).begin(), (c).end()
typedef pair<int, int> PII;
typedef vector<int> VI;

int main() {

  char op[32];
  double balance0, balance;
  map<int, double> check, deposit;
  map<int, bool> check_used, deposit_used;
  scanf("%*s %lf", &balance0);
  int n; double val;
  while(~scanf("%s", op) && strcmp(op, "balance")) {
    scanf("%d %lf", &n, &val);
    (strcmp(op, "check") == 0 ? check : deposit)[n] = val;    
    (strcmp(op, "check") == 0 ? check_used : deposit_used)[n] = false;    
  }
  scanf("%lf", &balance);

  double B0, B;
  double BK0 = balance0, BK;
  scanf("%lf", &B0);
  while(~scanf("%s %d %lf %lf", op, &n, &val, &B)) {

    // printf("%s %d %lf %lf-%lf\n", op, n, val, B0, B);

    bool is_check = strcmp(op, "check") == 0;
    printf("%s %d", is_check ? "check" : "deposit", n);

    bool correct = true;
    if((is_check ? check : deposit).find(n) ==
       (is_check ? check : deposit).end()) {
      printf(" is not in statement");
      correct = false;
      if((is_check ? check_used : deposit_used)[n]) {
        printf(" repeated transaction");      
        correct = false;
      }
      goto next;
    }

    if((is_check ? check_used : deposit_used)[n]) {
      printf(" repeated transaction");      
      correct = false;
    }

    BK = (is_check ? BK0 - check[n] : BK0 + deposit[n]);

    if((is_check ? check : deposit)[n] != val) {
      printf(" incorrect amount");
      if(::abs(B0 - B) == (is_check ? check : deposit)[n]) {
        printf(" math uses correct value");
      }
      correct = false;
    }
    if(::abs(B0 - B) != val && ::abs(B0 - B) != (is_check ? check : deposit)[n]) {
    // if((is_check ? B0 - val : B0 + val) != B || B != BK) {    
      printf(" math mistake");
      correct = false;
    }
    if(correct) printf(" is correct");

  next:;
    (is_check ? check_used : deposit_used)[n] = true;
    printf("\n");

    B0 = B;
    BK0 = BK;
  }

  FOR(i, check_used) if(!i->second) printf("missed check %d\n", i->first);
  FOR(i, deposit_used) if(!i->second) printf("missed deposit %d\n", i->first);

  return 0;
}
