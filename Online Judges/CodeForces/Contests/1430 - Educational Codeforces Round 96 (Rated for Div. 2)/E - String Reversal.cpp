#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char ss[maxN + 1];
string s, rev;

map<pair<char, int>, int> idx;
int cnt[256];

int arr[maxN], aux[maxN];
lli merge(int lo, int hi)
{
  int mid = (lo + hi) >> 1;
  lli inversions = 0;
  for (int i = lo, j = mid + 1, k = 0; i <= mid || j <= hi; k++)
  {
    if (i == mid + 1) aux[k] = arr[j++];
    else if (j > hi || arr[i] < arr[j]) aux[k] = arr[i++];
    else aux[k] = arr[j++], inversions += mid - i + 1;
  }
  for (int k = 0, sz = hi - lo + 1; k < sz; k++)
    arr[lo + k] = aux[k];
  return inversions;
}
lli mergeSort(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return 0;
  int mid = (lo + hi) >> 1;
  lli inversions = mergeSort(lo, mid) + mergeSort(mid + 1, hi);
  return inversions + merge(lo, hi);
}
void printArr()
{
  for (int i = 0; i < n; i++)
    printf("%d%c", arr[i], i < n - 1 ? ' ' : '\n');
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", ss);
    s = string(ss);
    rev = s;
    reverse(rev.begin(), rev.end());

    idx.clear();
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      idx[{s[i], cnt[s[i]]}] = i;
      cnt[s[i]]++;
    }

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      arr[i] = idx[{rev[i], cnt[rev[i]]}];
      cnt[rev[i]]++;
    }
    DEBUG printArr();

    lli ans = mergeSort();
    DEBUG printArr();
    printf("%lld\n", ans);
  }
  return 0;
}