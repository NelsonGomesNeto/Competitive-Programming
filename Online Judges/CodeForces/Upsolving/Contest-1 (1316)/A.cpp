#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
int scores[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &m);
    int sum = 0, others = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &scores[i]);
      sum += scores[i];
    }
    others = sum - scores[0];

    int ans = min(m, scores[0] + others);
    printf("%d\n", ans);
  }
  return 0;
}
