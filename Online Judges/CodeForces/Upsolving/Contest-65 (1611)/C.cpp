#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];

deque<int> lol(deque<int> &arr, int lolSide)
{
  deque<int> hehe;
  for (int lo = 0, hi = n - 1; lo <= hi;)
  {
    if (lo == hi)
    {
      if (lolSide == 0) hehe.push_back(arr[lo++]);
      else hehe.push_back(arr[lo++]);
    }
    else
    {
      if (arr[lo] < arr[hi]) hehe.push_front(arr[lo++]);
      else hehe.push_back(arr[hi--]);
    }
  }
  return hehe;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    bool possible = false;
    deque<int> finalAns;
    for (int side = 0; side < 2; side++)
      for (int lolSide = 0; lolSide < 2; lolSide++)
      {
        deque<int> ans;
        for (int lo = 0, hi = n - 1; lo <= hi;)
        {
          if (lo == hi)
          {
            if (side == 0) ans.push_back(a[lo++]);
            else ans.push_front(a[lo++]);
          }
          else
          {
            if (a[lo] > a[hi]) ans.push_front(a[lo++]);
            else ans.push_back(a[hi--]);
          }
        }

        deque<int> rev = lol(ans, lolSide);
        bool valid = true;
        for (int i = 0; i < n; i++) if (rev[i] != a[i]) valid = false;

        if (valid) possible = true, finalAns = ans;
      }

    if (!possible) printf("-1\n");
    else
      for (int i = 0; i < n; i++)
        printf("%d%c", finalAns[i], i + 1 < n ? ' ' : '\n');
  }
  return 0;
}
