#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  D[i] == integers Dora bought on day i
  Suppose the following:
    intersection(D[i], D[j]) = {}, for some i and j
    But Swiper buys the complement of Dora, than:
    lcm(D[i]) > lcm(S[i]) must be true
      But, S[i] is the complement of D[i], so it must have
      all integers (and maybe more) from D[j]:
    lcm(S[i]) >= lcm(D[j]) is true
    lcm(D[j]) > lcm(S[j]) must be true
      But again, S[j] is the complement of D[j], so:
    lcm(S[j] >= lcm(D[i])) is true
    Contradicion:
    lcm(D[i]) > lcm(S[i]) >= lcm(D[j]) > lcm(S[j]) >= lcm(D[i])

  So, we just need to check whether there's a pair of days with
  no intersection.
*/

const int maxM = 50; int m, n;
set<int> days[maxM];

bool noCommon(set<int> &a, set<int> &b)
{
  for (int i: a) if (b.count(i)) return(false);
  return(true);
}

int main()
{
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i ++)
  {
    int s; scanf("%d", &s);
    for (int j = 0, a; j < s; j ++)
    {
      scanf("%d", &a);
      days[i].insert(a);
    }
  }

  bool can = true;
  for (int i = 0; i < m; i ++)
    for (int j = i + 1; j < m; j ++)
      if (noCommon(days[i], days[j]))
        can = false;
  printf("%s\n", can ? "possible" : "impossible");

  return(0);
}
