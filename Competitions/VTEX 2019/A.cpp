#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3, maxT = 4e4; int n;
pair<int, int> t[maxN];
int in[maxT + 1], out[maxT + 1];

bool can(int x)
{
  int people = 0, on = 0;
  for (int tt = 0; tt <= maxT; tt ++)
  {
    people -= out[tt];
    if (in[tt]) people += in[tt], on = tt + x;
    if (people && on <= tt) return(false);
  }
  return(true);
}

int binarySearch(int lo, int hi)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) >> 1;
  if (can(mid)) return(binarySearch(lo, mid));
  return(binarySearch(mid + 1, hi));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d", &t[i].first, &t[i].second);
    in[t[i].first] ++, out[t[i].second] ++;
  }
  sort(t, t+n);

  printf("%d\n", binarySearch(0, 1e5));

  return(0);
}