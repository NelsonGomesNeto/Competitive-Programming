#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char s[maxN], aux[maxN], aux2[maxN];

int main()
{
  int n; scanf("%d", &n);
  char ans[n + 1]; ans[n] = '\0';
  for (int i = 0; i < n; i ++) ans[i] = '0';
  for (int t = 0; t < n; t ++)
  {
    scanf(" %s", s);
    int wrong = 0;
    vector<int> points;
    for (int i = 0, end = strlen(s) - 1; i < end; i ++)
    {
      wrong += s[i] > s[i + 1];
      if (s[i] > s[i + 1])
        points.push_back(i);
    }
    DEBUG printf("-----%d %d-----\n", t, wrong);
    if (wrong == 0)
      ans[t] = '1';
    else if (wrong >= 1)
    {
      points.push_back(strlen(s) - 1);

      bool allValid = true;
      int i, k;
      for (i = 0, k = 0; i <= points[0]; i ++, k ++)
        aux[k] = s[i];
      aux[k] = '\0';
      for (int j = 0; j < points.size() - 1; j ++)
      {
        for (i = points[j] + 1, k = 0; i <= points[j + 1]; i ++, k ++)
          aux2[k] = s[i];
        aux2[k] = '\0';
        DEBUG printf("%s %s\n", aux, aux2);
        if (strcmp(aux, aux2) > 0)
          allValid = false;

        for (k = 0; aux2[k]; k ++)
          aux[k] = aux2[k];
        aux[k] = '\0';
      }
      if (allValid)
        ans[t] = '1';
    }
  }
  printf("%s\n", ans);

  return 0;
}