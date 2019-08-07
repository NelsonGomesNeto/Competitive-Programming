#include <bits/stdc++.h>
using namespace std;
int a[5]; // op[3] = +, -, *

bool isBitSet(int bit, int shift)
{
  return(bit & (1 << shift));
}

int verify(int i, int done, int value)
{
  //printf("%d %d %d\n", i, done, value);
  if (i == 5) return(value == 23);
  for (int j = 0; j < 5; j ++)
    if (!isBitSet(done, j))
    {
      if (verify(i + 1, done | (1 << j), value + a[j])) return(1);
      if (verify(i + 1, done | (1 << j), value - a[j])) return(1);
      if (verify(i + 1, done | (1 << j), value * a[j])) return(1);
    }
  return(0);
}

int testAll(int i, int value)
{
  if (i == 5) return(value == 23);
  if (testAll(i + 1, value + a[i])) return(1);
  if (testAll(i + 1, value - a[i])) return(1);
  if (testAll(i + 1, value * a[i])) return(1);
  return(0);
}

int verifyPermutation()
{
  int can = 0;
  sort(a, a+5);
  do
  {
    can = testAll(1, a[0]);
  } while(!can && next_permutation(a, a+5));
  return(can);
}

int read()
{
  int sum = 0;
  for (int i = 0; i < 5; i ++)
  {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  return(sum);
}

int main()
{
  while (read())
  {
    int can = verifyPermutation();
    // for (int i = 0; !can && i < 5; i ++)
    //   if (verify(1, 1 << i, a[i]))
    //     can = 1;
    printf("%s\n", can ? "Possible" : "Impossible");
  }
  return(0);
}