#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];

int sum[2], op[2];

int main()
{
  while (scanf("%d\n%s", &n, s) != EOF)
  {
    sum[0] = sum[1] = op[0] = op[1] = 0;
    for (int i = 0; i < n; i ++)
    {
      if (s[i] == '?')
        op[i / (n >> 1)] ++;
      else
        sum[i / (n >> 1)] += s[i] - '0';
    }

    bool monocarp = true;
    while (op[0] + op[1])
    {
      if (sum[1] > sum[0] || (sum[1] == sum[0] && op[1] > op[0]))
        swap(sum[0], sum[1]), swap(op[0], op[1]);
      DEBUG printf("%d - %d %d - %d %d\n", monocarp, sum[0], sum[1], op[0], op[1]);
      if (monocarp)
      {
        if (sum[0] >= sum[1] && op[0])
          sum[0] += 9, op[0] --;
        else
          sum[1] += (sum[1] + 9 > sum[0]) ? 9 : 0, op[1] --;
      }
      else
      {
        if (sum[0] >= sum[1] && op[1])
          sum[1] += min(9, sum[0] - sum[1]), op[1] --;
        else
          op[0] --;
      }
      monocarp = !monocarp;
    }
    printf("%s\n", sum[0] == sum[1] ? "Bicarp" : "Monocarp");
  }

  return 0;
}