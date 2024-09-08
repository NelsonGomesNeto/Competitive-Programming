#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*

higher than that of the student,

i < k, a[k] + 300 >= a[i]
i = k, todo mundo zera
i > k, a[i] + 300 >= a[k]

*/

const int maxN = 1e5; int n, k;
int p[3][maxN];
pair<int, int> s[maxN];
bool ans[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    k--;

    for (int i = 0; i < n; i++)
    {
      s[i] = make_pair(0, i);
      for (int j = 0; j < 3; j++)
      {
        scanf("%d", &p[j][i]);
        s[i].first += p[j][i];
      }
    }
    sort(s, s+n, greater<pair<int, int>>());

    DEBUG {
      printf("scores:");
      for (int i = 0; i < n; i++)
        printf(" (%d, %d)", s[i].second, s[i].first);
      printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
      bool can = false;
      if (i < k) can = true;
      // {
      //   can = s[k].first + 300 > s[i].first;
      // }
      else if (i == k) can = true;
      else
      {
        can = s[i].first + 300 >= s[k].first;
      }
      ans[s[i].second] = can;
    }

    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i] ? "Yes" : "No");
  }
  return 0;
}