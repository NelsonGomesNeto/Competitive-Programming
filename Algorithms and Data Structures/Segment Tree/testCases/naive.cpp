#include <bits/stdc++.h>
int a[(int) 1e6];

int query(int lo, int hi)
{
  int sum = 0; for (int i = lo; i <= hi; i ++) sum += a[i];
  return(sum);
}

void updateRange(int lo, int hi, int x, int kind)
{
  for (int i = lo; i <= hi; i ++) a[i] = x + (kind - 1) * a[i];
}

void update(int position, int value)
{
  a[position] = value;
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &a[i]);

  char kind;
  while (scanf("\n%c", &kind) != EOF)
  {
    int lo, hi, x; scanf("%d %d", &lo, &hi);

    if (kind == 'Q') printf("Sum(%d, %d) = %d\n", lo, hi, query(lo, hi));
    else update(lo, hi); //updateRange(lo, hi, x, kind == 'S' ? 1 : 2);
  }
  return(0);
}
