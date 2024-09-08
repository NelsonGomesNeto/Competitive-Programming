#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n, q;
int c[kMaxN];
set<int> boxes[kMaxN];

int main() {
  int pudding = 0;
  while (~scanf("%d %d", &n, &q)) {
    if (pudding++) printf("------------\n");

    for (int i = 0; i < n; ++i) {
      scanf("%d", &c[i]);
      boxes[i].clear();
      boxes[i].insert(c[i]);
    }

    for (int i = 0; i < q; ++i) {
      int a, b;
      scanf("%d %d", &a, &b);
      --a, --b;

      if (boxes[b].size() > boxes[a].size()) {
        boxes[b].merge(boxes[a]);
        boxes[a].clear();
      } else {
        boxes[a].merge(boxes[b]);
        boxes[b].clear();
        swap(boxes[a], boxes[b]);
      }

      printf("%d\n", (int)boxes[b].size());
    }
  }
  return 0;
}
