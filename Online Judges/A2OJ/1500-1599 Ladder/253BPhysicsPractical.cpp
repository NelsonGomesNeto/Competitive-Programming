#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
int c[maxN];

int binarySearch(int lo, int hi, int target)
{
  if (lo >= hi) return(lo);
  int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (c[mid] <= target) return(binarySearch(mid, hi, target));
  return(binarySearch(lo, mid - 1, target));
}

int main()
{
  FILE *input = fopen("input.txt", "rb");
  FILE *output = fopen("output.txt", "wb");
  int n; fscanf(input, "%d", &n);
  for (int i = 0; i < n; i ++) fscanf(input, "%d", &c[i]);
  sort(c, c+n);
  int best = 0;
  for (int i = 0; i < n; i ++)
  {
    int pos = binarySearch(i, n - 1, 2*c[i]);
    best = max(best, pos - i + 1);
  }
  fprintf(output, "%d\n", n - best);
  fclose(input);
  fclose(output);
  return(0);
}