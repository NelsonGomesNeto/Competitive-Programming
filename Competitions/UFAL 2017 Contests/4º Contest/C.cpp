#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
vector<int> nullSet;

vector<int> createSegmentTree(vector<int> segmentTree[], int array[], int i, int lo, int hi)
{
  if (lo == hi)
  {
    segmentTree[i] = {array[lo]};
    return(segmentTree[i]);
  }
  else if (lo > hi) return(nullSet);
  int mid = (lo + hi) / 2;
  vector<int> left = createSegmentTree(segmentTree, array, 2*i + 1, lo, mid);
  vector<int> right = createSegmentTree(segmentTree, array, 2*i + 2, mid + 1, hi);
  segmentTree[i].resize(left.size() + right.size());
  merge(left.begin(), left.end(), right.begin(), right.end(), segmentTree[i].begin());
  return(segmentTree[i]);
}

int gs(vector<int> segmentTree[], int i, int lo, int hi, int qlo, int qhi, int k)
{
  if (lo >= qlo && hi <= qhi) return((int) (segmentTree[i].end() - upper_bound(segmentTree[i].begin(), segmentTree[i].end(), k)));
  else if (lo > qhi || hi < qlo) return(0);
  int mid = (lo + hi) / 2;
  return(gs(segmentTree, 2*i + 1, lo, mid, qlo, qhi, k) + gs(segmentTree, 2*i + 2, mid + 1, hi, qlo, qhi, k));
}

int getSum(vector<int> segmentTree[], int size, int lo, int hi, int k)
{
  //if (lo < 0 || hi > size - 1 || lo > hi) return(0);
  return(gs(segmentTree, 0, 0, size - 1, lo, hi, k));
}

int main()
{
  int n; scanf("%d", &n);
  int array[n];
  for (int i = 0; i < n; i ++)
    scanf("%d", &array[i]);

  vector<int> segmentTree[(int) 1e5];
  createSegmentTree(segmentTree, array, 0, 0, n - 1);

  int q, lastAns = 0; scanf("%d", &q);
  while (q -- > 0)
  {
    int lo, hi, k; scanf("%d %d %d", &lo, &hi, &k);
    lo ^= lastAns; hi ^= lastAns; k ^= lastAns;
    lastAns = getSum(segmentTree, n, lo - 1, hi - 1, k);
    printf("%d\n", lastAns);
  }
  return(0);
}