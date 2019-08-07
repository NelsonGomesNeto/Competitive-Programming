#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  set<int> now; int l = 0, r = -1, size = 0;
  int app[100001]; memset(app, 0, sizeof(app));
  for (int i = 0; i < n; i ++)
  {
    now.insert(a[i]); app[a[i]] ++;
    if (now.size() == k)
    {
      r = i;
      DEBUG printf("%d %d\n", l, r);
      while (l < n && now.size() == k)
      {
        app[a[l]] --;
        if (!app[a[l]]) now.erase(a[l]);
        l ++;
      }
      l = min(l, r);
      DEBUG printf("%d %d\n", l, r);
    }
  }

  if (r == -1) printf("-1 -1\n");
  else if (k == 1) printf("1 1\n");
  else printf("%d %d\n", l, r + 1);

  return(0);
}
