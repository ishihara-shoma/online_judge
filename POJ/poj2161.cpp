#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
#include <cassert>
using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()

typedef pair<int, int> PII;

char buf[100010];
int depth[100010] = {0};

PII dfs(int p) {
  if(p < 0) return PII(-1, -1);

  int end = p;

  assert(isdigit(buf[p]));

  int c = buf[p--] - '0';
  // printf("size = %d\n", c);
  int depth[16] = {0};
  int pos[16] = {0};  

  for(int i = c - 1; i >= 0; i--) {
    if(isdigit(buf[p])) {
      PII res = dfs(p);
      int pp = res.first, d = res.second;
      depth[i] = d;
      p = pp;
    } else {
      depth[i] = 1;
      p--;
    }
    pos[i] = p + 1;
  }

  int begin = p + 1;
  // printf("(%d,%d)\n", begin, end);
  // puts(buf);
  // REP(i, end + 1) putchar(i == begin || i == end ? '^' : ' ');
  // putchar('\n');

  int res = (1<<25), idx = 0;
  REP(i, c) {
    int s = 0, r = 0;
    REP(j, c) {
      r = max(r, s + depth[(i + j) % c]);
      s = s + 1;
    }
    // printf("idx = %d, pos = %d, maxdepth = %d\n", i, pos[i], r);
    if(r < res) {
      res = r;
      idx = i;
    }
  }

  int shift = pos[idx] - begin;
  // if(depth[idx] > 1) shift ++;
  // printf("shift = %d\n", shift);

  rotate(buf + begin, buf + begin + shift, buf + end);
  
  return PII(begin - 1, res);
}

int main() {

  gets(buf);
  int len = strlen(buf);

  int res = dfs(len - 1).second;

  printf("%d\n", res);
  puts(buf);

  return 0;
}
