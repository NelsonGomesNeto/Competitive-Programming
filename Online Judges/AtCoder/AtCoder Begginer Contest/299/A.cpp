#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf("%d", &n))
  {
    scanf(" %s", ss);
    s = string(ss);

    vector<int> pipePos;
    for (int i = 0; i < n; ++i)
      if (s[i] == '|')
        pipePos.push_back(i);

    bool ans = false;
    for (int i = 0; i < n; ++i)
      if (s[i] == '*')
        ans = pipePos[0] < i && i < pipePos[1];
    printf("%s\n", ans ? "in" : "out");
  }
  return 0;
}
