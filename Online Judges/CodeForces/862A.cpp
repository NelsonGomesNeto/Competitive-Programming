#include <bits/stdc++.h>
using namespace std;
int DEBUG = 0;

int main()
{
  int size, x; scanf("%d %d", &size, &x);
  int set[size], operations = 0;
  for (int i = 0; i < size; i ++)
  {
    int k;
    scanf("%d", &k);
    if (k == x)
    {
      operations ++;
      i --;
      size --;
    }
    else
      set[i] = k;
  }

  sort(set, set + size);
  if (DEBUG)
  {
    for (int i = 0; i < size; i ++)
      printf("%d ", set[i]);
    printf("\n");
  }

  if (size > 0)
  {
    int prev = set[0];
    if (prev <= x)
      operations += prev;
    else if (prev > x)
      operations += x - prev - 1;
    for (int i = 1; i < size && prev <= x; i ++)
    {
      if (DEBUG) printf("%d %d\n", prev, set[i]);

      if (prev <= x && set[i] >= x)
        operations += x - prev - 1;
      else if (set[i] - prev > 1)
        operations += set[i] - prev - 1;

      prev = set[i];
    }
  }

  printf("%d\n", operations);

  return(0);
}