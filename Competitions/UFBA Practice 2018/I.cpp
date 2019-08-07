#include <bits/stdc++.h>
using namespace std;
int segtree[2][(int) 4e5], *leftDiff, *rightDiff, *heights, n, q;

void printArray(int array[])
{
  for (int i = 0; i < n; i ++) printf("%d%c", array[i], i < n - 1 ? ' ' : '\n');
}

void build(int lo, int hi, int i = 1)
{
  if (lo >= hi)
  {
    segtree[0][i] = leftDiff[lo], segtree[1][i] = rightDiff[lo];
    return;
  }
  int mid = (lo + hi) >> 1;
  build(lo, mid, 2*i); build(mid + 1, hi, 2*i + 1);
  segtree[0][i] = max(segtree[0][2*i], segtree[0][2*i + 1]);
  segtree[1][i] = max(segtree[1][2*i], segtree[1][2*i + 1]);
}

void update(int pos, int value, int lo, int hi, int i = 1)
{
  if (lo > pos || hi < pos) return;
  if (lo >= hi)
  {
    leftDiff[lo] = abs(value - (lo > 0 ? heights[lo - 1] : 0));
    rightDiff[lo] = abs(value - (lo < n - 1 ? heights[lo + 1] : 0));
    heights[lo] = value;
    segtree[0][i] = leftDiff[lo], segtree[1][i] = rightDiff[lo];
    return;
  }
  int mid = (lo + hi) >> 1;
  update(pos, value, lo, mid, 2*i); update(pos, value, mid + 1, hi, 2*i + 1);
  segtree[0][i] = max(segtree[0][2*i], segtree[0][2*i + 1]);
  segtree[1][i] = max(segtree[1][2*i], segtree[1][2*i + 1]);
}

int query(int seg, int qlo, int qhi, int lo, int hi, int i = 1)
{
  if (lo > qhi || hi < qlo) return(0);
  if (lo >= qlo && hi <= qhi) return(segtree[seg][i]);
  int mid = (lo + hi) >> 1;
  return(max(query(seg, qlo, qhi, lo, mid, 2*i), query(seg, qlo, qhi, mid + 1, hi, 2*i + 1)));
}

int binSearch(int lo, int hi, int i, int h, int upper)
{
  // printf("LOL %d %d\n", lo, hi);
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + upper * ((lo + hi) & 1);
  int qans = query(!upper, upper ? i : mid, upper ? mid : i, 0, n - 1);
  // printf("(%d, %d) - %d = %d\n", i, h, mid, qans);
  if (qans > h) return(upper ? binSearch(lo, mid - 1, i, h, upper) : binSearch(mid + 1, hi, i, h, upper));
  return(upper ? binSearch(mid, hi, i, h, upper) : binSearch(lo, mid, i, h, upper));
}

int main()
{
  scanf("%d %d", &n, &q);
  int hhh[n]; for (int i = 0; i < n; i ++) scanf("%d", &hhh[i]);
  int ldiff[n], rdiff[n]; ldiff[0] = rdiff[n - 1] = 0;
  for (int i = 1; i < n; i ++)
  {
    ldiff[i] = abs(hhh[i] - hhh[i - 1]);
    rdiff[n - i - 1] = abs(hhh[n - i - 1] - hhh[n - i]);
  }
  leftDiff = ldiff, rightDiff = rdiff, heights = hhh;
  build(0, n - 1);

  while (q --)
  {
    int op, i, h; scanf("%d %d %d", &op, &i, &h); i --;
    if (op == 1)
    {
      update(i, h, 0, n - 1);
      if (i > 0) update(i - 1, heights[i - 1], 0, n - 1);
      if (i < n - 1) update(i + 1, heights[i + 1], 0, n - 1);
    }
    else
    {
      // printArray(leftDiff);
      // printArray(rightDiff);
      int left = binSearch(0, max(0, i - 1), max(0, i - 1), h, 0);
      int right = binSearch(min(n - 1, i + 1), n - 1, min(n - 1, i + 1), h, 1);
      if (rightDiff[left] > h && i > 0) left ++;
      if (leftDiff[right] > h && i < n - 1) right --;
      // printf("--%d %d %d | %d %d\n", i, left, right, rightDiff[left], leftDiff[right]);
      printf("%d\n", right - left + 1);
    }
  }

  return(0);
}
