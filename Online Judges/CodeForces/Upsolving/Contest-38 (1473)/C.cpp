#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
int a[maxN]; lli inva;
int b[maxN];
int p[maxN];

int copyaux[maxN];
int aux[maxN];
lli merge(int array[], int lo, int mid, int hi)
{
  int i = lo, j = mid + 1, at = 0; lli inversions = 0;
  while (i <= mid || j <= hi)
  {
    if (i == mid + 1) copyaux[at ++] = array[j ++];
    else if (j == hi + 1) copyaux[at ++] = array[i ++];
    else if (array[i] > array[j])
    {
      copyaux[at ++] = array[j ++]; inversions += (mid - i + 1);
    }
    else copyaux[at ++] = array[i ++];
  }
  for (i = 0; i <= (hi - lo); i ++)
    array[lo + i] = copyaux[i];
  return(inversions);
}
lli mergeSort(int array[], int lo, int hi)
{
  if (lo >= hi) return(0);

  lli inversions = 0, mid = (lo + hi) / 2;
  inversions += mergeSort(array, lo, mid);
  inversions += mergeSort(array, mid + 1, hi);
  inversions += merge(array, lo, mid, hi);
  return(inversions);
}
lli inversionCount(int arr[])
{
  for (int i = 0; i < n; i++)
    aux[i] = arr[i];
  return mergeSort(aux, 0, n - 1);
}

bool can(int pos)
{
  swap(p[pos], p[k - 1]);
  for (int i = 0; i < n; i++)
    b[i] = p[a[i]];

  lli inversions = inversionCount(b);

  swap(p[pos], p[k - 1]);
  
  return inversions <= inva;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
    {
      if (i >= k)
        a[i] = k - (i - k) - 2;
      else
        a[i] = i;
    }
    inva = inversionCount(a);

    for (int i = 0; i < k; i++)
      p[i] = i;

    // for (int hehe = k - 1, lo = 0; hehe >= 0; hehe--)
    // {
    //   int hi = hehe - 1;
    //   while (lo < hi)
    //   {
    //     int mid = (lo + hi) >> 1;
    //     if (can(mid)) hi = mid;
    //     else lo = mid + 1;
    //   }

    //   DEBUG printf("\t\t%d %d\n", lo, hehe);
    //   if (lo >= hehe) break;
    //   swap(p[lo], p[hehe]);
    //   // break;
    //   lo++;
    // }

    int delta = 2*k - n - 1;
    for (int i = 0; i < delta; i++)
      p[i] = i;
    for (int i = delta, hehe = k - 1; i < k; i++, hehe--)
      p[i] = hehe;

    if (n == k)
      for (int i = 0; i < k; i++)
        p[i] = i;

    for (int i = 0; i < n; i++)
      b[i] = p[a[i]];

    DEBUG {
      int inva = 0;
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
          inva += a[i] > a[j];
      printf("a (%d): ", inva);
      for (int i = 0; i < n; i++)
        printf("%d%c", a[i] + 1, i < n - 1 ? ' ' : '\n');
      int invb = 0;
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
          invb += b[i] > b[j];
      printf("b (%d): ", invb);
      for (int i = 0; i < n; i++)
        printf("%d%c", b[i] + 1, i < n - 1 ? ' ' : '\n');
    }

    for (int i = 0; i < k; i++)
      printf("%d%c", p[i] + 1, i < k - 1 ? ' ' : '\n');
  }
  return 0;
}
/*
1 2 3 2 1
1 3 2 3 1
*/
