#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int a[4]; for (int i = 0; i < 4; i ++) scanf("%d", &a[i]);
  int b[4]; memcpy(b, a, sizeof(b));
  sort(b, b+4);

  int ans = 0;
  for (int i = 0; i < 4; i ++)
    if (a[i] != b[i])
    {
      bool done = false;
      for (int j = 0; j < 4; j ++)
        if (a[j] == b[i] && a[i] == b[j])
        {
          ans ++, done = true;
          swap(a[i], a[j]);
          break;
        }
      if (!done)
        for (int j = 0; j < 4; j ++)
          if (a[j] == b[i])
          {
            ans ++, done = true;
            swap(a[i], a[j]);
            break;
          }
    }
  for (int i = 0; i < 4; i ++) printf("%d%c", a[i], i < 3 ? ' ' : '\n');
  printf("%d\n", ans);

  return(0);
}