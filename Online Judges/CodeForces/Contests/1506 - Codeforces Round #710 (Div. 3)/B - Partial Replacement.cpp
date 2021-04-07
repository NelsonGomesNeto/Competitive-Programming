#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k;
char s[maxN + 1];

// int memo[maxN][maxN + 1];
// int last;
// int solve(int i = 0, int d = 0)
// {
//   if (d >= k)
//     return 2*maxN;
//   if (i == last)
//     return 0;
//   int &ans = memo[i][d];
//   if (ans != -1)
//     return ans;

//   ans = (s[i] == 'x') + solve(i + 1, s[i] == 'x' ? 0 : d + 1);
//   if (s[i] == '*')
//     ans = min(ans, 1 + solve(i + 1, 0));

//   return ans;
// }

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", s);

    int start;
    for (int i = 0; i < n; i++)
      if (s[i] == '*')
      {
        s[i] = 'x';
        start = i;
        break;
      }
    for (int i = n - 1; i >= 0; i--)
      if (s[i] == '*')
      {
        s[i] = 'x';
        // last = i;
        break;
      }

    for (int i = 0; i < n; i++)
      if (s[i] == 'x')
      {
        bool has = false;
        for (int j = min(n - 1, i + k); j > i; j--)
          if (s[j] == 'x')
            has = true;
        if (has) continue;
        for (int j = min(n - 1, i + k); j > i; j--)
          if (s[j] == '*')
          {
            s[j] = 'x';
            break;
          }
      }

    int ans = 0;
    for (int i = 0; i < n; i++)
      ans += s[i] == 'x';
    
    printf("%d\n", ans);
  }
  return 0;
}