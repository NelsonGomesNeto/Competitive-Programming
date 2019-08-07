#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxP = 1e3;
int cnt[maxP + 1];

int main()
{
  int p, n; scanf("%d %d", &p, &n);
  for (int i = 0, a; i < n; i ++)
  {
    scanf("%d", &a);
    cnt[a] ++;
  }

  bool can = true;
  for (int i = 1, all = 0; can && all < n; i = i % p + 1, all ++)
  {
    if (!cnt[i]) can = false;
    cnt[i] -= 1;
  }
  printf("%c\n", can ? 'S' : 'N');

  return(0);
}