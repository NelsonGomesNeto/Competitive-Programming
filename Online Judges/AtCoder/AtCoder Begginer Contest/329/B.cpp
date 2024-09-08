#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n;
int a[kMaxN];

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }

    set<int> all;
    for (int i = 0; i < n; ++i)
      all.insert(a[i]);

    printf("%d\n", *prev(all.end(), 2));
  }
  return 0;
}
