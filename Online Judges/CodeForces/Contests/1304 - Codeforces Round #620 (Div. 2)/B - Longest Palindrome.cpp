#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxM = 50; int n, m;
char ss[maxM + 1];
string strings[maxN];
bool done[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(done, false, sizeof(done));
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      strings[i] = string(ss);
    }

    vector<string> hasPair;
    string mid = "";
    for (int i = 0; i < n; i++)
    {
      if (done[i]) continue;
      string aux = strings[i];
      reverse(aux.begin(), aux.end());
      bool has = false;
      for (int j = i + 1; j < n; j++)
        if (!done[j] && aux == strings[j])
        {
          done[i] = done[j] = true, hasPair.push_back(strings[i]);
          break;
        }
      if (!done[i])
      {
        bool isPal = true;
        for (int ii = 0, jj = strings[i].size() - 1; ii < jj; ii++, jj--)
          if (strings[i][ii] != strings[i][jj])
            isPal = false;
        if (isPal)
          mid = strings[i];
      }
    }

    string ans = "";
    for (int i = 0; i < hasPair.size(); i++) ans += hasPair[i];
    ans += mid;
    for (int i = hasPair.size() - 1; i >= 0; i--)
    {
      reverse(hasPair[i].begin(), hasPair[i].end());
      ans += hasPair[i];
    }
    printf("%d\n%s\n", (int)ans.size(), ans.c_str());
  }
  return 0;
}