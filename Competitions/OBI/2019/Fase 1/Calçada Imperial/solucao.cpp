#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e2; int n;
int a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int ans = 1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        if (a[i] == a[j]) continue;
        int curr = 0;
        for (int k = 0, turn = 0; k < n; k++)
          if (turn == 0 && a[k] == a[i])
            curr++, turn = !turn;
          else if (turn == 1 && a[k] == a[j])
            curr++, turn = !turn;
        ans = max(ans, curr);
      }
    printf("%d\n", ans);
  }
  return 0;
}