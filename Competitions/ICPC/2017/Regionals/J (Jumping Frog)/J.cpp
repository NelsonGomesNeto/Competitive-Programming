#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;
char s[(int) 1e5 + 1];

/* Explanation:
gcd(k, n) = d
  it means that with k, we will only visit (i % d) == 0 places
  d will have to be a divisor of n, so there will be at most 2*sqrt(n) of them

when gcd(k, n) == 1
  it will visit every cell before returning to the starting one
when gcd(k, n) != 1
  it won't loop more then once, it will only visit ((i % gcd(k, d)) == 0) places
  and then return to the starting one

so, we only need to find all d, and precalculate for each of them if they can
go back to the starting one without reaching a 'P'; for each d, the range to test will be (0, d - 1)

then we run through all possible k and add 1 to ans if gcd(k, n) is valid (according to our precalculation)
O(sqrt(n)*n)
*/

int gcd(int a, int b)
{
  if (!b) return(a);
  return(gcd(b, a % b));
}

int main()
{
  scanf("%s", s); int n = 0; while (s[n]) n ++;
  set<int> d;
  for (int i = 1; i < n; i ++) d.insert(gcd(i, n));

  DEBUG
  {
    printf("n: %d, d size: %d\n", n, (int) d.size());
    for (int i: d) printf("%d ", i); printf("\n");
    // int k = 3;
    // for (int i = 0; i < k; i ++)
    // {
    //   int pos = i;
    //   do
    //   {
    //     // printf("%d ", pos);
    //     if (pos < i) printf("LOL\n");
    //     // if (s[pos] == 'P') break;
    //     pos = (pos + k) % n;
    //   } while (pos != i);
    // }
  }

  bool works[n]; memset(works, false, sizeof(works));
  for (int k: d)
  {
    bool can = false;
    for (int i = 0; i < k && !can; i ++)
    {
      can = true; int pos = i;
      do
      {
        if (s[pos] == 'P') { can = false; break; }
        pos = (pos + k) % n;
      } while (pos != i);
    }
    works[k] = can;
  }

  int ans = 0; for (int i = 1; i < n; i ++) ans += works[gcd(i, n)];
  printf("%d\n", ans);

  return(0);
}
