#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 4*100; int q, n;
int a[maxN];
map<int, int> sticks;

int main()
{
  scanf("%d", &q);
  while (q --)
  {
    sticks.clear();
    scanf("%d", &n); n *= 4;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      if (!sticks.count(a[i]))
        sticks[a[i]] = 0;
      sticks[a[i]] ++;
    }
    map<int, int>::iterator lo = sticks.begin(), hi = prev(sticks.end());
    int done = 0, area = lo->first * hi->first;
    while (lo->first <= hi->first)
    {
      if ((lo->second & 1) || (hi->second & 1) || lo->second != hi->second || lo->first * hi->first != area)
        break;
      done += lo == hi ? lo->second >> 2: lo->second >> 1;
      lo ++, hi --;
    }
    printf("%s\n", done == (n >> 2) ? "YES" : "NO");
  }
  return(0);
}
