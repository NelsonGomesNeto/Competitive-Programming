#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
int a[maxN];

int main()
{
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    sort(a, a+n);

    int curr = a[0];
    int ans = -1;
    for (int i = 0; i < n; ++i) {
      if (a[i] != curr) {
        ans = curr;
        break;
      }
      ++curr;
    }

    printf("%d\n", ans);
  }
  return 0;
}
