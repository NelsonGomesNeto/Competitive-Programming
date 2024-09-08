#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int dists[6] = {3, 1, 4, 1, 5, 9};

int main()
{
  char l, r;
  while (~scanf(" %c %c", &l, &r))
  {
    if (l > r) swap(l, r);

    int ans = 0;
    char at = l;
    while (at != r)
    {
      ans += dists[at - 'A'];
      ++at;
    }
    printf("%d\n", ans);
  }
  return 0;
}
