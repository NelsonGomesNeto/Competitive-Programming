#include <bits/stdc++.h>
int a[(int) 2e5], n, m;

int eval(int k)
{
  int videos = 0;
  for (int i = 0; i < n; i ++)
  {
    if (k && videos < a[i]) k --, videos ++;
    else if (videos >= a[i]) videos ++;
  }
  return(videos);
}

int binSearch(int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) >> 1;
  if (eval(mid) >= target) return(binSearch(lo, mid, target));
  return(binSearch(mid + 1, hi, target));
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  int ans = binSearch(0, 2e5, m);
  printf("%d\n", ans);
  return(0);
}