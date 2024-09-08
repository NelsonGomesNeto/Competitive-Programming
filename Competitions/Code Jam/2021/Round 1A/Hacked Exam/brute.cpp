#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3, maxQ = 40; int n, q;
char answers[maxN][maxQ + 1]; int scores[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &q);
    memset(scores, 0, sizeof(scores));
    for (int i = 0; i < n; i++)
      scanf(" %s %d", answers[i], &scores[i]);

    pair<lli, lli> ans = solve();
    printf("Case #%d: ", tt);
    print(ans.first);
    printf("/");
    print(ans.second);
    printf("\n");
  }
  return 0;
}