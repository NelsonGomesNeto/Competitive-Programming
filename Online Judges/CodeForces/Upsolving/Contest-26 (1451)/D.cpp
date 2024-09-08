#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial
  Notice that what happens at position base = (i * k, i * k):
  Let's call up = (i * k, (i + 1) * k), and right = ((i + 1) * k, i * k)
  if up is inside the circle:
    right is also inside the circle
  if up is a winning position, right is also a winning position:
    it means that base is a losing position

  Player two can always force that player one will be at a base
  position (i * k, i * k) [By doing the oposite of what player one does]

  With that said, we just need to know if the last base position is a losing
  position.
*/

lli d, k;

bool valid(lli x, lli y)
{
  return x*x + y*y <= d*d;
}
int solve(lli x = 0, lli y = 0, bool ashish = true)
{
  bool up = valid(x, y + k), right = valid(x + k, y);

  if (ashish)
    return up ? solve(x, y + k, !ashish) : !ashish;
  else
    return right ? solve(x + k, y, !ashish) : !ashish;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld", &d, &k);
    int ans = solve();
    printf("%s\n", ans ? "Ashish" : "Utkarsh");
  }
  return 0;
}
