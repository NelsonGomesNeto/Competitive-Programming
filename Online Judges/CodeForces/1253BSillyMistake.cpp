#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxX = 1e6 + 1; int n;
int cnt[maxX], today[maxX];
int a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    memset(today, 0, sizeof(today));
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    bool can = true; int start = 0, inside = 0;
    vector<int> partitions;
    for (int i = 0; i < n; i ++)
    {
      DEBUG printf("\t%d %d %d - %d %d\n", i, (int) partitions.size(), inside, today[abs(a[i])], cnt[abs(a[i])]);
      if (a[i] < 0)
      {
        if (cnt[-a[i]] == 0) can = false;
        cnt[-a[i]] --, inside --;
        if (inside == 0)
        {
          partitions.push_back(i - start + 1);
          for (int j = start; j <= i; j ++)
            today[abs(a[j])] = 0;
          start = i + 1;
        }
      } 
      if (a[i] > 0)
      {
        if (today[a[i]] > 0)
        {
          if (inside != 0) can = false;
          partitions.push_back(i - start);
          for (int j = start; j <= i; j ++)
            today[abs(a[j])] = 0;
          start = i;
        }
        cnt[a[i]] ++, today[a[i]] ++, inside ++;
      }
    }
    if (inside) can = false;
    if (start != n)
      partitions.push_back(n - 1 - start + 1);

    if (!can) printf("-1\n");
    else
    {
      printf("%d\n", (int) partitions.size());
      for (int i = 0; i < partitions.size(); i ++)
        printf("%d%c", partitions[i], i < partitions.size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
