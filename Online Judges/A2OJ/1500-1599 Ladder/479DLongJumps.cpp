#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n; lli l, x, y;
lli marks[maxN]; set<lli> marksSet;

bool hasDistance(lli d)
{
  lli nowDistance;
  for (int i = 0, j = 1; j < n;)
  {
    nowDistance = marks[j] - marks[i];
    if (nowDistance == d) return(true);
    if (nowDistance < d) j ++;
    else i ++;
  }
  return(false);
}

int main()
{
  scanf("%d %lld %lld %lld", &n, &l, &x, &y);
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &marks[i]);
    marksSet.insert(marks[i]);
  }

  bool hasX = hasDistance(x), hasY = hasDistance(y);
  
  if (hasX && hasY) printf("0\n");
  else
  {
    if (hasX && !hasY) printf("1\n%lld\n", marks[0] + y);
    else if (!hasX && hasY) printf("1\n%lld\n", marks[0] + x);
    else
    {
      lli position = -1;
      for (int i = 0; i < n; i ++)
        if (marks[i] + x <= l && (marksSet.count(marks[i] + x - y) || marksSet.count(marks[i] + x + y)))
          position = marks[i] + x;
        else if (marks[i] - x >= 0 && (marksSet.count(marks[i] - x - y) || marksSet.count(marks[i] - x + y)))
          position = marks[i] - x;
      if (position != -1) printf("1\n%lld\n", position);
      else printf("2\n%lld %lld\n", marks[0] + x, marks[0] + y);
    }
    
  }

  return(0);
}