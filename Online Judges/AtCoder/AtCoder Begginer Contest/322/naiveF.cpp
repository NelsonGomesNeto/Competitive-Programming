#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 5e5;
int n, q;
char ss[kMaxN + 1];
string s;

void update(int lo, int hi) {
  for (int i = lo; i <= hi; ++i)
    s[i] = s[i] == '1' ? '0' : '1';
}

int query(int lo, int hi) {
  int ans = 0;
  for (int i = lo; i <= hi; ++i) {
    char now = s[i];
    int j = i;
    while (j + 1 <= hi && s[j + 1] == now) ++j;

    if (now == '1') ans = max(ans, j - i + 1);

    i = j;
  }
  return ans;
}

int main() {
  int tests = 0;
  while (~scanf("%d %d", &n, &q)) {
    if (tests++) printf("--------------------------\n");
    scanf(" %s", ss);
    s = string(ss);

    for (int i = 0; i < q; ++i) {
      int op, lo, hi;
      scanf("%d %d %d", &op, &lo, &hi);
      --lo, --hi;
      if (op == 1) {
        update(lo, hi);
      } else {
        int ans = query(lo, hi);
        printf("%d\n", ans);
      }
    }
  }
  return 0;
}
