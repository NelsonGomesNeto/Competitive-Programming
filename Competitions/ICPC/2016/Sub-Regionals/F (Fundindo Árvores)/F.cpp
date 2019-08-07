#include <iostream>
using namespace std;

int main()
{
  // First you will read the trees
  int vl, vr, i;
  cin >> vl;
  int lt[vl + 1][2], w, l, c;
  for (i = 1; i <= vl; i ++) // left one
  {
    cin >> w >> l >> c;
    lt[w][0] = l;
    lt[w][1] = c;
  }
  cin >> vr;
  int rt[vr + 1][2], r;
  for (i = 1; i <= vr; i ++) // right one
  {
    cin >> w >> c >> r;
    rt[w][0] = c;
    rt[w][1] = r;
  }

  // Then you will find the biggest sequence of central nodes in each tree
  int ml = 0, mr = 0, j, sum;
  for (i = 1; i <= vl; i ++) // left one
  {
    j = i; sum = 1;
    while (lt[j][1] != 0)
    {
      sum ++;
      j = lt[j][1];
    }
    ml = max(ml, sum);
  }
  for (i = 1; i <= vr; i ++) // right one
  {
    j = i; sum = 1;
    while(rt[j][0] != 0)
    {
      sum ++;
      j = rt[j][0];
    }
    mr = max(mr, sum);
  }

  // Then you will see how much of the biggest right fits on left's root
  j = 1; sum = 1;
  while (lt[j][1] != 0)
  {
    sum ++;
    j = lt[j][1];
  }
  mr = min(mr, sum);
  // Same here, find how much of the biggest left fits one right's root
  j = 1; sum = 1;
  while (rt[j][0] != 0)
  {
    sum ++;
    j = rt[j][0];
  }
  ml = min(ml, sum);

  // The ternary tree will have, vr + vl - maximum of the how much fitted
  int ans = vr + vl - max(mr, ml);
  cout << ans << '\n';

  return(0);
}
