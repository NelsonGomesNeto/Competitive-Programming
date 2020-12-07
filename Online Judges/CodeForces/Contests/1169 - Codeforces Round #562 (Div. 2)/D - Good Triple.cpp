#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  This problem reminds you to try hard and a least try bruteforcing haha
  The thing is that for any string >= 9, it's guaranteed to exist some (x, k)
  With that being said, you just need to count the pairs
*/

const int maxN = 3e5; int n;
char s[maxN + 1];
int prv[maxN + 1];

int main()
{
  scanf("%s", s); n = strlen(s);

  lli ans = 0;
  prv[n] = n;
  for (int i = n - 1; i >= 0; i --)
  {
    prv[i] = prv[i + 1];
    for (int k = 1; i+2*k < n && k < 5; k ++)
      if (s[i] == s[i + k] && s[i] == s[i + 2*k])
      {
        prv[i] = min(prv[i], i + 2*k);
        break;
      }
    ans += n - prv[i];
  }
  printf("%lld\n", ans);

  return(0);
}
