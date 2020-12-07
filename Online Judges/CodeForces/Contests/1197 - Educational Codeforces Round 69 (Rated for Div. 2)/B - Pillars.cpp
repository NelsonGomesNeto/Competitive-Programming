#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
list<int>::iterator at;
list<int> all;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    all.clear();
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]); a[i] --;
      all.push_back(a[i]);
    }
    for (at = all.begin(); at != all.end(); at ++)
      if (*at == n - 1)
        break;
    bool can = true;
    for (int i = n - 1; i > 0; i --)
    {
      // printf("%d - %d\n", (*at) + 1, i + 1);
      if (at != all.begin() && *prev(at) == i - 1)
        at = prev(all.erase(at));
      else if (at != prev(all.end()) && *next(at) == i - 1)
        at = all.erase(at);
      else
      {
        can = false;
        break;
      }
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}
