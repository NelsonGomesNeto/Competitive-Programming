#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char ss[15];
string strings[maxN];

unordered_map<string, int> all;

int main()
{
  string available = "";
  for (char i = 'A'; i <= 'Z'; i++)
    available += i;
  for (char i = '0'; i <= '9'; i++)
    available += i;

  vector<int> modifiables = {0, 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13};
  while (scanf("%d", &n) != EOF)
  {
    all.clear();

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      strings[i] = string(ss);
      string a = "";
      for (int j = 0; j < strings[i].size(); j++)
        if (strings[i][j] != '-')
          a += strings[i][j];
      strings[i] = a;
      all[strings[i]]++;
    }

    for (int i = 0; i < n; i++)
      for (int j: modifiables)
        for (char c: available)
          if (strings[i][j] != c)
          {
            char prv = strings[i][j];
            strings[i][j] = c;
            ans += all.count(strings[i]);
            strings[i][j] = prv;
          }
    printf("%d\n", ans);
  }
  return 0;
}