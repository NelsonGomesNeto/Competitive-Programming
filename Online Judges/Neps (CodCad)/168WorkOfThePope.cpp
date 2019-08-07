#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The optimal order is: b[i].weight + b[i].capacity <= b[i+1].weight + b[i+1].capacity
    Proof:
      Suppose a box A is at the bottom of the stack. So, the maximum weight of
      the stack is A.weight + A.capacity. Any other box that might be below A should
      have a maximum weight >= A.maximumWeight. Of couse, the box below A might not
      be chosen to achieve the maximum stack size, but every box below A will have
      a bigger maximum weight.

  So, we sort the boxes by the maximum weight.
  memo[i] will store the smallest weight of i-th sized stack
  ans = 0 // start with a 0 sized stack
  for each box b:
    for j in [ans + 1, 1]:
      if (b.capacity >= memo[j - 1] and memo[j - 1] + b.weight < memo[j])
        memo[j] = memo[j - 1] + b.weight, ans = max(ans, j)
        "b.capacity >= memo[j - 1]", box b supports the j-1 sized stack
        "memo[j - 1] + b.weight < memo[j]"
          j-1 sized stack weight + b weight is smaller than j sized stack,
          so we better swap the bottom of the j sized stack, since box b
          can support it and will lead to a smalled total weight, making
          it easier for other boxes to have enough capacity
*/

const int maxN = 1e3, maxP = 1e3, maxR = 1e6; int n;
lli inf = 1e18;
struct Box
{
  lli weight, resistance;
  bool operator<(const Box &b) const { return(weight + resistance < b.weight + b.resistance); }
};
Box boxes[maxN];

lli memo[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld %lld", &boxes[i].weight, &boxes[i].resistance);
      boxes[i].resistance -= boxes[i].weight;
    }
    sort(boxes, boxes+n);

    for (int i = 1; i <= n; i ++) memo[i] = inf;
    memo[0] = 0;
    
    int ans = 0;
    for (int i = 0; i < n; i ++)
      for (int j = ans + 1; j > 0; j --)
        if (boxes[i].resistance >= memo[j - 1] && memo[j - 1] + boxes[i].weight < memo[j])
          memo[j] = memo[j - 1] + boxes[i].weight, ans = max(ans, j);
    printf("%d\n", ans);
  }

  return(0);
}
