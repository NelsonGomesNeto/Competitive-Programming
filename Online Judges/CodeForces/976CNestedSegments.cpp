#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int lowerBound(vector<int> a[], int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) / 2;
  if (a[mid][0] >= target) return(lowerBound(a, lo, mid, target));
  else return(lowerBound(a, mid + 1, hi, target));
}

int main()
{
  int n; scanf("%d", &n);
  vector<int> seg[n]; int a, b;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &a, &b);
    seg[i] = {a, b, i};
  }
  sort(seg, seg+n);

  DEBUG for (int i = 0; i < n; i ++) printf("%d %d\n", seg[i][0], seg[i][1]);

  int l = -1, r = -1;
  for (int i = 0; i < n - 1; i ++)
  {
    if (seg[i][0] <= seg[i + 1][0] && seg[i][1] >= seg[i + 1][1] && l == -1)
    {
      l = seg[i + 1][2]; r = seg[i][2];
    }
    if (seg[i][0] >= seg[i + 1][0] && seg[i][1] <= seg[i + 1][1] && l == -1)
    {
      l = seg[i][2]; r = seg[i + 1][2];
    }
  }

  if (l == -1) printf("-1 -1\n");
  else printf("%d %d\n", l + 1, r + 1);

  return(0);
}