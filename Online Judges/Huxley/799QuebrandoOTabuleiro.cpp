#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxL = 36; int n, L, C;
int letterCount[256];
vector<pair<int, char>> cntChar;
vector<vector<pair<int, char>>> words;
vector<pair<int, pair<int, int>>> posCost;

int main()
{
  while (scanf("%d %d %d", &n, &L, &C) && n)
  {
    posCost.clear(), cntChar.clear(), words.clear();

    for (int i = 1; i <= L; i ++)
      for (int j = 1; j <= C; j ++)
        posCost.push_back({i + j, {i, j}});
    sort(posCost.begin(), posCost.end());

    for (int i = 0; i < n; i ++)
    {
      memset(letterCount, 0, sizeof(letterCount));
      char s[1000]; scanf(" %[^\n]", s);
      for (int j = 0; s[j]; j ++)
        if (s[j] != ' ')
          letterCount[s[j]] ++;
      words.push_back(vector<pair<int, char>>());
      for (int j = 0; j < 256; j ++)
        if (letterCount[j])
          words.back().push_back({letterCount[j], j});
      sort(words.back().begin(), words.back().end());
      reverse(words.back().begin(), words.back().end());
    }

    for (auto &w: words)
    {
      int ans = 0, j = 0;
      for (auto &i: w)
        ans += i.first * posCost[j ++].first;
      printf("%d\n", ans);
    }
  }
  return(0);
}