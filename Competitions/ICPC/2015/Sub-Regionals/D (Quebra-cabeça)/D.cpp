#include <bits/stdc++.h>
using namespace std;

const int maxL = 100, maxC = 100, inf = 1e6 + 1; int L, C;

set<pair<char, char>> variables;
int values[26*26], missing;
int table[maxL + 1][maxC + 1];

int main()
{
  scanf("%d %d", &L, &C);
  char s[3];
  for (int i = 0; i < L; i ++)
  {
    for (int j = 0; j < C; j ++)
    {
      scanf(" %s", s);
      int id = (s[0] - 'a')*26 + (s[1] - 'a');
      variables.insert({s[0], s[1]}), values[id] = inf;
      table[i][j] = id;
    }
    scanf("%d", &table[i][C]);
  }
  for (int j = 0; j < C; j ++) scanf("%d", &table[L][j]);
  missing = variables.size();

  while (missing)
  {
    for (int i = 0; i < L && missing; i ++)
    {
      int m = -1, c = 0, sum = 0; bool unique = true;
      for (int j = 0; j < C && unique; j ++)
      {
        if (values[table[i][j]] == inf)
        {
          if (m != -1 && m != table[i][j]) unique = false;
          m = table[i][j], c ++;
        }
        else
          sum += values[table[i][j]];
      }
      if (unique && m != -1) values[m] = (table[i][C] - sum) / c, missing --;
    }
    for (int j = 0; j < C && missing; j ++)
    {
      int m = -1, c = 0, sum = 0; bool unique = true;
      for (int i = 0; i < L && unique; i ++)
      {
        if (values[table[i][j]] == inf)
        {
          if (m != -1 && m != table[i][j]) unique = false;
          m = table[i][j], c ++;
        }
        else
          sum += values[table[i][j]];
      }
      if (unique && m != -1) values[m] = (table[L][j] - sum) / c, missing --;
    }
  }

  for (auto i: variables)
    printf("%c%c %d\n", i.first, i.second, values[(i.first - 'a')*26 + (i.second - 'a')]);

  return(0);
}