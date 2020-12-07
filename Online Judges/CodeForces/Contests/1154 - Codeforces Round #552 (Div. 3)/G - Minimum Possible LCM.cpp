#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/*
Explanation:
G = gcd(A, B)
A = G * R
B = G * S
lcm(A, B) = A * B / gcd(A, B) = A * B / G = G * R * S
we want to minimize G * R * S, which coincides with
finding the smallest A and B

for every gcd in (1 to 1e7):
  find the first two multiples of gcd in the array
  if lcm(a[first], a[second]) < current minimum LCM
    save first, second and it's lcm

Handle the trivial case where there are two repeated numbers
*/

const int maxN = 1e6, maxGCD = 1e7; int n;
lli a[maxN];
bool hasNumber[maxGCD + 1]; int numberPosition[maxGCD + 1];

int main()
{
  scanf("%d", &n);
  lli minLCM = 1e18; int first, second;
  for (int i = 0; i < n; i ++) 
  {
    scanf("%lld", &a[i]);
    if (hasNumber[a[i]] && a[i] < minLCM)
      minLCM = a[i], first = numberPosition[a[i]], second = i;
    hasNumber[a[i]] = true, numberPosition[a[i]] = i;
  }

  for (lli i = 1; i <= maxGCD; i ++)
  {
    int f = -1, s = -1;
    for (lli g = i; g <= maxGCD; g += i)
      if (hasNumber[g] && f == -1) f = numberPosition[g];
      else if (hasNumber[g] && s == -1) { s = numberPosition[g]; break; }
    if (f != -1 && s != -1)
    {
      lli nowLCM = lcm(a[f], a[s]);
      if (nowLCM < minLCM)
        minLCM = nowLCM, first = min(f, s), second = max(f, s);
    }
  }
  printf("%d %d\n", first + 1, second + 1);
  return(0);
}