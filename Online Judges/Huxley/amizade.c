#include <stdio.h>

int root(int dj[], int p)
{
  while(p != dj[p])
  {
    dj[p] = dj[dj[p]];
    p = dj[p];
  }
  return(p);
}

int find(int dj[], int p, int q)
{
  return(root(dj, p) == root(dj, q));
}

void unite(int dj[], int size[], int p, int q)
{
  int i = root(dj, p);
  int j = root(dj, q);
  if (i != j)
  {
    if (size[i] < size[j])
    {
      dj[i] = j;
      size[j] += size[i];
    }
    else
    {
      dj[j] = i;
      size[i] += size[j];
    }
  }
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int people, pairs; scanf("%d %d", &people, &pairs); people ++;
    int dj[people], size[people], i, A, B, biggest = 0;
    for (i = 0; i < people; i ++)
    {
      dj[i] = i;
      size[i] = 1;
    }

    for (i = 0; i < pairs; i ++)
    {
      scanf("%d %d", &A, &B);
      unite(dj, size, A, B);

      A = size[root(dj, A)];
      B = size[root(dj, B)];
      if (A > biggest) biggest = A;
      if (B > biggest) biggest = B;
    }

    // for (i = 0; i < people; i ++)
    // {
    //   if (size[i] > biggest)
    //     biggest = size[i];
    // }

    printf("%d\n", biggest);

    tests --;
  }
  return(0);
}
