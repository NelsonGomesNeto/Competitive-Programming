#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  lli totalSum = 0;
  lli arcs[n]; for (int i = 0; i < n; i ++) { scanf("%lld", &arcs[i]); totalSum += arcs[i]; }
  if (totalSum & 1) printf("N\n");
  else
  {
    int lo = 0, midPos = 0; lli mid = totalSum >> 1, s;
    for (s = 0; lo < n && !(s < mid && midPos == n);)
    {
      if (s > mid && lo < n) s -= arcs[lo ++];
      if (s < mid && midPos < n) s += arcs[midPos ++];
      if (s == mid) { midPos --; break; }
    }
    bool can = false;
    if (s == mid)
      for (lli i = lo, s1 = arcs[lo], j = midPos + 1, s2 = arcs[(midPos + 1) % n]; ((i + 1) % n) != midPos && ((j + 1) % n) != lo;)
      {
        if (s1 == s2) { can = true; break; }
        if (s1 > s2) s2 += arcs[(++ j) % n];
        if (s2 > s1) s1 += arcs[(++ i) % n];
      }
    printf("%s\n", can ? "Y" : "N");
  }
  return(0);
}