#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxQ = 20; int n;
int queries = 0;
map<pair<int, int>, int> memo;
int query(int lo, int hi)
{
  if (lo == hi)
    return -1;

  auto q = make_pair(lo, hi);
  if (memo.count(q)) return memo[q];

  assert(++queries <= maxQ);
  printf("? %d %d\n", lo, hi); fflush(stdout);
  int pos; scanf("%d", &pos); pos;
  return memo[q] = pos;
}

/*

a[lo : hi]

second max is at i
i isn't the maximum element

so the maximum element must be at: a[lo : i - 1] or a[i + 1 : hi]

all numbers are different

*/

int main()
{
  while (~scanf("%d", &n))
  {
    queries = 0;
    int secondMaxPos = query(1, n);
    int onSecondMaxSidePos = query(1, secondMaxPos);
    
    int lo, hi; bool maximize = false;
    if (onSecondMaxSidePos == secondMaxPos)
      lo = 1, hi = secondMaxPos, maximize = true;
    else
      lo = secondMaxPos + 1, hi = n;

    while (lo < hi)
    {
      int mid = (lo + hi + maximize) >> 1;
      if (maximize)
      {
        if (query(mid, secondMaxPos) == secondMaxPos) lo = mid;
        else hi = mid - 1;
      }
      else
      {
        if (query(secondMaxPos, mid) == secondMaxPos) hi = mid;
        else lo = mid + 1;
      }
    }

    printf("! %d\n", lo); fflush(stdout);

    return 0;
  }
}
