#include <bits/stdc++.h>
using namespace std;
vector<int> segmentTree[(int) 3e5], null;

vector<int> createSegmentTree(int array[], int i, int lo, int hi)
{
  if (lo == hi)
  {
    segmentTree[i] = {array[lo]};
    return(segmentTree[i]);
  }
  else if (lo > hi) return(null);
  int mid = (lo + hi) / 2;
  vector<int> left = createSegmentTree(array, 2*i + 1, lo, mid);
  vector<int> right = createSegmentTree(array, 2*i + 2, mid + 1, hi);
  segmentTree[i].resize(left.size() + right.size());
  merge(left.begin(), left.end(), right.begin(), right.end(), segmentTree[i].begin());
  return(segmentTree[i]);
}

int gs(int i, int lo, int hi, int qlo, int qhi, int k)
{
  if (lo >= qlo && hi <= qhi) return(upper_bound(segmentTree[i].begin(), segmentTree[i].end(), k) - segmentTree[i].begin());
  else if (lo > qhi || hi < qlo) return(0);
  int mid = (lo + hi) / 2;
  return(gs(2*i + 1, lo, mid, qlo, qhi, k) +  gs(2*i + 2, mid + 1, hi, qlo, qhi, k));
}

int getSum(int size, int lo, int hi, int k)
{
  return(gs(0, 0, size - 1, lo, hi, k));
}

int main()
{
  int size, queries; scanf("%d %d", &size, &queries);
  int array[size], backUp[size], pos[size];
  for (int i = 0; i < size; i ++)
  {
    scanf("%d", &array[i]);
    backUp[i] = array[i];
  }
  sort(array, array+size);
  for (int i = 0; i < size; i ++)
  {
    pos[i] = lower_bound(array, array+size, backUp[i]) - array;
    //printf("%d -> %d\n", backUp[i], pos[i]);
  }

  createSegmentTree(pos, 0, 0, size - 1);

  while (queries -- > 0)
  {
    int i, j, k, lo = 0, hi = size - 1, mid, ans;
    scanf("%d %d %d", &i, &j, &k); i --; j --;
    while (lo <= hi)
    {
      mid = (lo + hi) / 2;
      int q = getSum(size, i, j, mid);
      printf("%d %d %d\n", lo, hi, q);
      if (q >= k)
      {
        ans = mid;
        hi = mid - 1;
      }
      else lo = mid + 1;
    }
    printf("%d\n", array[ans]);
  }
  return(0);
}