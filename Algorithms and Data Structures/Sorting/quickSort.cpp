#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> arr;

pair<int, int> quickSortPartition(vector<int> &a, int lo, int hi)
{
  // int pivot = a[rand() % (hi - lo + 1) + lo];
  int pivot = a[(lo + hi) >> 1];
  lo--, hi++;
  do
  {
    do lo++; while (a[lo] < pivot);
    do hi--; while (a[hi] > pivot);
    if (lo < hi) swap(a[lo], a[hi]);
  } while (lo < hi);
  while (lo >= 0 && a[lo] == pivot) lo--;
  while (hi < a.size() - 1 && a[hi] == pivot) hi++;
  return make_pair(lo, hi);
}
void quickSortRec(vector<int> &a, int lo, int hi)
{
  // printf("here %d %d\n", lo, hi); fflush(stdout);
  if (lo >= hi) return;
  pair<int, int> split = quickSortPartition(a, lo, hi);
  quickSortRec(a, lo, split.first);
  quickSortRec(a, split.second, hi);
}
void quickSort(vector<int> &a) { quickSortRec(a, 0, a.size() - 1); }

int main()
{
  srand(time(NULL));

  while (~scanf("%d", &n))
  {
    arr.resize(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &arr[i]);

    quickSort(arr);
    for (int i = 0; i < n; i++)
      printf("%d%c", arr[i], i < n - 1 ? ' ' : '\n');
    for (int i = 1; i < n; i++)
      assert(arr[i - 1] <= arr[i]);
    break;
  }
  return 0;
}