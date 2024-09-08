#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
char s[maxN + 1];
char ans[maxN][maxN + 1];
int wins[maxN], loses[maxN];

char opposite(char result)
{
  return result == '+' ? '-' : result == '-' ? '+' : result;
}

bool eval()
{
  memset(wins, 0, sizeof(wins));
  memset(loses, 0, sizeof(loses));
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (ans[i][j] == '+')
        wins[i]++, loses[j]++;
      else if (ans[i][j] == '-')
        wins[j]++, loses[i]++;

  for (int i = 0; i < n; i++)
    if (s[i] == '1' && loses[i])
      return false;
    else if (s[i] == '2' && !wins[i])
      return false;

  return true;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    memset(wins, 0, sizeof(wins));
    memset(loses, 0, sizeof(loses));
    for (int i = 0; i < n; i++)
    {
      ans[i][n] = '\0';
      for (int j = i; j < n; j++)
      {
        if (i == j)
          ans[i][j] = 'X';
        else
        {
          char result;
          if (s[i] == '1' && s[j] == '1')
            result = '=';
          else if (s[i] == '1')
            result = '+';
          else if (s[j] == '1')
            result = '-';
          else
          {
            if (!wins[i])
              result = '+';
            else
              result = '-';
          }

          if (result == '+')
            wins[i]++, loses[j]++;
          else if (result == '-')
            wins[j]++, loses[i]++;

          ans[i][j] = result;
          ans[j][i] = opposite(result);
        }
      }
    }

    bool valid = eval();

    if (valid)
    {
      printf("YES\n");
      for (int i = 0; i < n; i++)
        printf("%s\n", ans[i]);
    }
    else
    {
      printf("NO\n");
    }
  }
  return 0;
}
