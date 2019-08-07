#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;
int t[maxN + 1];

int binarySearch(int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (target < t[mid]) return(binarySearch(lo, mid - 1, target));
  return(binarySearch(mid, hi, target));
}

int memo[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%d", &t[i]);

  for (int i = 1; i <= n; i ++)
    memo[i] = min({memo[i - 1] + 20,
                   memo[binarySearch(0, i - 1, t[i] - 90)] + 50,
                   memo[binarySearch(0, i - 1, t[i] - 1440)] + 120});

  for (int i = 1; i <= n; i ++) printf("%d\n", memo[i] - memo[i - 1]);

  return(0);
}