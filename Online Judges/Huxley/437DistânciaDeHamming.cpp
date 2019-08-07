#include <bits/stdc++.h>
int size, distance;
char bit[(int) 1e6 + 1];

void generate(int i, int ones)
{
  if (i == size)
  {
    bit[i] = '\0';
    printf("%s\n", bit);
    return;
  }
  if (size - i + ones > distance)
  {
    bit[i] = '0';
    generate(i + 1, ones);
  }
  if (ones + 1 <= distance)
  {
    bit[i] = '1';
    generate(i + 1, ones + 1);
  }
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    scanf("%d %d", &size, &distance);
    generate(0, 0);
    if (tests > 0) printf("\n");
  }
  return(0);
}