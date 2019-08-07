#include <bits/stdc++.h>
using namespace std;

int equal(int number, char now[])
{
  //if (number == atoi(now))
    //printf("%s %d\n", now, atoi(now));
  return(number == atoi(now));
}

int findNumber(int number, char now[], int i, int n, int cube[][6])
{
  if (i == n && equal(number, now)) return(1);
  if (i == n) return(0);

  if (findNumber(number, now, i + 1, n, cube)) return(1);
  int k, j; char newNow[n + 1]; memset(newNow, ' ', sizeof(newNow)); newNow[n] = '\0';
  strcpy(newNow, now);
  for (k = 0; k < 6; k ++)
    for (j = 0; j < n; j ++)
    {
      char prev = newNow[j];
      newNow[j] = cube[i][k] + '0';
      if (findNumber(number, newNow, i + 1, n, cube)) return(1);
      newNow[j] = prev;
    }
  return(0);
}

int main()
{
  int n; scanf("%d", &n);
  int cube[n][6], i, j;
  for (i = 0; i < n; i ++)
    for (j = 0; j < 6; j ++)
      scanf("%d", &cube[i][j]);

  int count = 0; char now[n + 1]; memset(now, ' ', sizeof(now)); now[n] = '\0';
  while (findNumber(count + 1, now, 0, n, cube)) count ++;

  printf("%d\n", count);

  return(0);
}