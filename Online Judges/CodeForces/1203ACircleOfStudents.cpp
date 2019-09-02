#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 200; int q, n;
int a[maxN];

int main()
{
  scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      a[i] --;
    }
    bool can = false;
    for (int i = 0; i < n && !can; i ++)
      if (a[i] == 0)
      {
        bool valid = true;
        for (int j = i, aa = 0; aa < n && valid; aa ++, j = (j + 1) % n)
          if (aa != a[j])
            valid = false;
        if (valid)
        {
          can = true;
          break;
        }
        valid = true;
        for (int j = i, aa = 0; aa < n && valid; aa ++, j = (((j - 1) % n + n) % n))
          if (aa != a[j])
            valid = false;
        can = valid;
        break;
      }
    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}
