#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int w, l;

int main()
{
  scanf("%d %d", &w, &l);
  lli bank[w], have[w]; have[0] = 0;
  for (int i = 1; i < w; i ++)
  {
    scanf("%lld", &bank[i]);
    have[i] = have[i - 1] + bank[i];
  }

  lli total = 1<<31 - 1, i;
  for (int j = 0; j < l; j ++)
    for (i = l + j; i < w; i += l)
      total = min(total, have[i] - (i > l ? have[i - l] : 0));

  printf("%lld\n", total);

  return(0);
}