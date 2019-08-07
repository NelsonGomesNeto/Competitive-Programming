#include <bits/stdc++.h>
int a[3] = {-1, 0, 1};

int createSegmentTree(int segmentTree[], int array[], int i, int lo, int hi)
{
  if (lo == hi)
  {
    segmentTree[i] = array[lo];
    return(segmentTree[i]);
  }
  else if (lo > hi) return(0);
  int mid = (lo + hi) / 2;
  segmentTree[i] = createSegmentTree(segmentTree, array, 2*i + 1, lo, mid) + createSegmentTree(segmentTree, array, 2*i + 2, mid + 1, hi);
  return(segmentTree[i]);
}

int gs(int segmentTree[], int i, int lo, int hi, int qlo, int qhi)
{
  if (lo >= qlo && hi <= qhi) return(segmentTree[i]);
  else if (hi < qlo || lo > qhi) return(0);
  int mid = (lo + hi) / 2;
  return(gs(segmentTree, 2*i + 1, lo, mid, qlo, qhi) + gs(segmentTree, 2*i + 2, mid + 1, hi, qlo, qhi));
}

int getSum(int segmentTree[], int size, int lo, int hi)
{
  if (lo < 0 || hi > size - 1 || lo > hi) return(-1);
  return(gs(segmentTree, 0, 0, size - 1, lo, hi));
}

void uv(int segmentTree[], int i, int diff, int lo, int hi, int pos)
{
  if (lo > pos || hi < pos) return;
  segmentTree[i] += diff;
  if (lo != hi)
  {
    int mid = (lo + hi) / 2;
    uv(segmentTree, 2*i + 1, diff, lo, mid, pos);
    uv(segmentTree, 2*i + 2, diff, mid + 1, hi, pos);
  }
}

// void updateValue(int segmentTree[][], int array[][], int size, int value, int pos)
// {
//   if (pos < 0 || pos > size - 1) return;
//   value = value > 0 ? 1 : value < 0 ? -1 : 0;
//   for (int i = 0; i < 3; i ++)
//   {
//     int prev = array[i][pos];
//     array[i][pos] = a[i] == value;
//     int diff = array[i][pos] - prev;
//     uv(segmentTree[i], 0, diff, 0, size - 1, pos);
//   }
// }

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    int array[3][n], num; memset(array, 0, sizeof(array));
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &num);
      if (num < 0) array[0][i] = 1;
      else if (num > 0) array[2][i] = 1;
      else array[1][i] = 1;
    }
    int segmentTree[3][(int) 3e5];
    for (int i = 0; i < 3; i ++)
      createSegmentTree(segmentTree[i], array[i], 0, 0, n - 1);

    while (k -- > 0)
    {
      char command; int i, j;
      getchar(); scanf("%c %d %d", &command, &i, &j);
      if (command == 'C')
      {
        int value = j > 0 ? 1 : j < 0 ? -1 : 0, pos = i - 1;
        for (int k = 0; k < 3; k ++)
        {
          int prev = array[k][pos];
          array[k][pos] = a[k] == value;
          int diff = array[k][pos] - prev;
          uv(segmentTree[k], 0, diff, 0, n - 1, pos);
        }
        //updateValue(segmentTree, array, n, j, i - 1);
      }
      else
      {
        int res[3];
        for (int k = 0; k < 3; k ++)
          res[k] = getSum(segmentTree[k], n, i - 1, j - 1);
        //printf("%d %d %d\n", res[0], res[1], res[2]);
        printf("%c", res[1] > 0 ? '0' : res[0] & 1 ? '-' : '+');
      }
    }
    printf("\n");
  }
  return(0);
}