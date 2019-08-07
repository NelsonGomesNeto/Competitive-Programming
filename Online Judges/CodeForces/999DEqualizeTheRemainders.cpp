#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
int n, m;

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%d%c", a[i], i < size - 1 ? ' ' : '\n');
}

int main()
{
  scanf("%d %d", &n, &m);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  int nm = n / m, c[m]; memset(c, 0, sizeof(c));
  vector<int> cNumbers[m]; int cAt[m]; memset(cAt, 0, sizeof(cAt));
  for (int i = 0; i < n; i ++)
  {
    int r = a[i] % m;
    c[r] ++;
    cNumbers[r].push_back(i);
  }

  DEBUG printf("%d\n", nm);
  DEBUG printArray(a, n);
  DEBUG printArray(c, m);

  set<int> missing;
  for (int i = 0; i < m; i ++) if (c[i] < nm) missing.insert(i);

  lli cost = 0;
  for (int i = 0; i < m; i ++)
  {
    // printf("\n%d\n", i);
    int at = i + 1;
    while (c[i] > nm)
    {
      int j = *missing.lower_bound(at);
      if (c[j] >= nm) j = *missing.lower_bound(0);
      // printf("%d %d %d %d\n", i, at, j, c[j]);

      int toFix = min(nm - c[j], c[i] - nm), distance = j - i < 0 ? j - i + m : j - i;
      cost += toFix * distance;
      for (int k = 0; k < toFix; k ++)
        a[cNumbers[i][cAt[i] ++]] += distance;
      c[i] -= toFix; c[j] += toFix;

      if (c[j] == nm) missing.erase(j);
      at ++;
    }
  }
  printf("%lld\n", cost);
  printArray(a, n);

  DEBUG {int newC[m]; memset(newC, 0, sizeof(newC));
  for (int i = 0; i < n; i ++) newC[a[i] % m] ++;
  printArray(newC, m);}

  return(0);
}