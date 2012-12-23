#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>
using namespace std;

int check(int* cn) {
  if(cn['O' - 'A'] <= cn['J' - 'A'] &&
     cn['O' - 'A'] <= cn['I' - 'A']) {
    return cn['O' - 'A'];
  }
  return -1;
}

int main() {

  char buf[1000010];

  scanf("%s", buf);
  int len = strlen(buf);

  int res = 0;
  int cn[30] = {0};
  bool valid = false;
  for(int i = 0; i < len; i++) {
    switch(buf[i]) {
    case 'J':
      if(i == 0 || buf[i - 1] != 'J') {
        if(valid) res = max(res, check(cn));
        memset(cn, 0, sizeof(cn));
        valid = true;
        // printf("restart p = %d\n", i);
      }
      cn['J' - 'A']++;
      break;
    case 'O':
      if(i > 0 && buf[i - 1] != 'I') {
        cn['O' - 'A']++;
      } else {
        if(valid) res = max(res, check(cn));
        valid = false;
      }
      break;
    case 'I':
      if(i > 0 && buf[i - 1] != 'J') {
        cn['I' - 'A']++;
      } else {
        if(valid) res = max(res, check(cn));
        valid = false;
      }
      break;
    default:
      assert(false);
      break;
    }
  }
  if(valid) res = max(res, check(cn));

  printf("%d\n", res);

  return 0;
}
