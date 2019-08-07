#include <bits/stdc++.h>
using namespace std;

char digits[7 + 1]; int n;
int d[10];
bool isPrime(int number)
{
  if (number == 0 || number == 1) return(false);
  if (number == 2) return(true);
  for (int i = 2, end = sqrt(number); i <= end; i ++)
    if (number % i == 0)
      return(false);
  return(true);
}
bool took[7];
int solve(int i = 0, int number = 0)
{
  if (i == n) return(isPrime(number));
  int ans = isPrime(number);
  for (int j = number == 0; j < 10; j ++)
    if (d[j])
    {
      d[j] --;
      ans += solve(i + 1, 10*number + j);
      d[j] ++;
    }
  return(ans);
}

int main()
{
  int c; scanf("%d", &c);
  while (c --)
  {
    scanf(" %s", digits); n = strlen(digits);
    memset(d, 0, sizeof(d));
    for (int i = 0; digits[i]; i ++)
      d[digits[i] - '0'] ++;
    int ans = solve();
    printf("%d\n", ans);
  }
  return(0);
}