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

struct Event {
  int iid, bid, tm;
  double val;
  Event(int item_id, int bidder_id, double amount, int bidtime):
    iid(item_id), bid(bidder_id), tm(bidtime), val(amount) {}
  Event(){}
  bool operator < (const Event& rhs) const {
    return tm > rhs.tm || tm == rhs.tm && bid <= rhs.bid;
  }
};

bool comp(const Event& lhs, const Event& rhs) {
  return lhs.val < rhs.val || lhs.val == rhs.val && lhs.tm < rhs.tm;
}

int main() {

  priority_queue<Event> eq;

  int N;
  scanf("%d", &N);
  map<int, vector<Event> > bid_stack;
  REP(i, N) {
    double x;
    int id, h, m, s;
    scanf("%d %lf %d:%d:%d", &id, &x, &h, &m, &s);
    eq.push(Event(id, -1, x, h * 60 * 60 + m * 60 + s));
    bid_stack[id] = vector<Event>();
  }

  int B;
  scanf("%d", &B);
  map<int, double> bidders;
  REP(i, B) {
    int id;
    double x;
    scanf("%d %lf", &id, &x);
    bidders[id] = x;
  }

  int A;
  scanf("%d", &A);
  REP(i, A) {
    double x;
    int iid, bid, h, m, s;
    scanf("%d %d %lf %d:%d:%d", &iid, &bid, &x, &h, &m, &s);
    eq.push(Event(iid, bid, x, h * 60 * 60 + m * 60 + s));
  }
  
  while(!eq.empty()) {

    Event e = eq.top(); eq.pop();

    // printf("item-id=%d bidder-id=%d price=%f time=%d:%d:%d\n",  e.iid, e.bid, e.val, e.tm / (60 * 60), e.tm % (60 * 60) / 60, e.tm % 60);

    if(e.bid < 0) { // bid-end

      sort(ALL(bid_stack[e.iid]), comp);

      bool f = false;
      while(!bid_stack[e.iid].empty()) {
        Event bid = bid_stack[e.iid].back();
        if(bid.val >= e.val &&
           bidders[bid.bid] >= bid.val) {
          printf("Item %d Bidder %d Price %.02f\n", bid.iid, bid.bid, bid.val);
          bidders[bid.bid] -= bid.val;
          f = true;
          break;
        }
        bid_stack[e.iid].pop_back();
      }

      if(!f) {
        printf("Item %d Reserve not met.\n", e.iid);
      }

    } else { // bid
      bid_stack[e.iid].push_back(e);
    }
  }

  return 0;
}
