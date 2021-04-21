#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 11;
char ss[maxN + 1];
string s[3];
vector<int> sn[3];
string n[3];

vector<int> good;
bool check()
{
  lli nums[3];
  for (int i = 0; i < 3; i++)
  {
    DEBUG printf("\t%s\n", s[i].c_str());
    if (good[sn[i].back()] == 0) return false;
    nums[i] = 0;
    for (int j = s[i].size() - 1; j >= 0; j--)
      nums[i] = good[sn[i][j]] + nums[i]*10;
  }

  return nums[0] + nums[1] == nums[2];
}

int main()
{
  while (~scanf(" %s", ss))
  {
    s[0] = string(ss);
    scanf(" %s", ss);
    s[1] = string(ss);
    scanf(" %s", ss);
    s[2] = string(ss);

    for (int i = 0; i < 3; i++)
    {
      reverse(s[i].begin(), s[i].end());
      sn[i].resize(s[i].size());
      for (int j = 0; j < s[i].size(); j++)
        sn[i][j] = s[i][j] - 'a';
    }

    set<char> all;
    for (int i = 0; i < 3; i++)
      for (int c: s[i])
        all.insert(c);
    vector<int> toMap;
    for (char c: all) toMap.push_back(c - 'a');

    if (all.size() > 10) printf("UNSOLVABLE\n");
    else
    {
      vector<int> perm;
      for (int i = 0; i < 10; i++) perm.push_back(i);

      bool can = false;
      good.resize(26, -1);
      do
      {
        fill(good.begin(), good.end(), -1);
        int i = 0;
        for (int letter: toMap)
          good[letter] = perm[i++];
        if (check())
        {
          can = true;
          break;
        }
      } while (next_permutation(perm.begin(), perm.end()));

      if (!can) printf("UNSOLVABLE\n");
      else
        for (int i = 0; i < 3; i++)
        {
          n[i].clear();
          reverse(s[i].begin(), s[i].end());
          reverse(sn[i].begin(), sn[i].end());
          DEBUG printf("\t%s\n", s[i].c_str());
          for (int j = 0; j < s[i].size(); j++)
            n[i] += (char)(good[sn[i][j]] + '0');
          printf("%s\n", n[i].c_str());
        }
    }
  }
  return 0;
}