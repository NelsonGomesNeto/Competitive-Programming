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
  set<int> had;
  for (int i = 0; i < 26; i++)
    if (good[i] != -1)
    {
      if (had.count(good[i])) return false;
      had.insert(good[i]);
    }

  lli nums[3];
  for (int i = 0; i < 3; i++)
  {
    DEBUG printf("\t%s\n", s[i].c_str());
    if (good[sn[i].back()] == 0) return false;
    nums[i] = 0;
    for (int j = s[i].size() - 1; j >= 0; j--)
      nums[i] = good[sn[i][j]] + nums[i]*10;
    if (to_string(nums[i]).size() != s[i].size())
      return false;
  }

  return nums[0] + nums[1] == nums[2];
}

int solve(int i = 0, int carry = 0, vector<int> numToLetter = vector<int>(10, -1), vector<int> letterToNum = vector<int>(26, -1))
{
  if (i == s[1].size())
  {
    if (i == s[2].size() && carry == 0)
    {
      good = letterToNum;
      return check();
    }

    if (carry == 0)
      return 0;

    if (numToLetter[carry] != -1)
    {
      if (numToLetter[carry] == sn[2][i])
      {
        good = letterToNum;
        return check();
      }
      return 0;
    }

    if (letterToNum[sn[2][i]] == -1 || letterToNum[sn[2][i]] == carry)
    {
      numToLetter[carry] = sn[2][i];
      letterToNum[sn[2][i]] = carry;
      good = letterToNum;
      return check();
    }
    return 0;
  }
  int ans = 0;

  if (i >= s[0].size())
  {
    for (int d1 = i == s[1].size() - 1; d1 <= 9; d1++)
    {
      if (letterToNum[sn[1][i]] != -1 && letterToNum[sn[1][i]] != d1) continue;
      if (numToLetter[d1] != -1 && numToLetter[d1] != sn[1][i]) continue;

      bool hadNumToLetter1 = numToLetter[d1] != -1;
      bool hadLetterToNum1 = letterToNum[sn[1][i]] != -1;
      numToLetter[d1] = sn[1][i];
      letterToNum[sn[1][i]] = d1;

      int sum = d1 + carry;
      if ((numToLetter[sum % 10] == -1 || numToLetter[sum % 10] == sn[2][i]) && (letterToNum[sn[2][i]] == -1 || letterToNum[sn[2][i]] == sum % 10))
      {
        bool hadNumToLetter2 = numToLetter[sum % 10] != -1;
        bool hadLetterToNum2 = letterToNum[sn[2][i]] != -1;
        numToLetter[sum % 10] = sn[2][i];
        letterToNum[sn[2][i]] = sum % 10;
        ans = max(ans, solve(i + 1, sum / 10, numToLetter, letterToNum));
        if (ans == 1) return ans;
        if (!hadNumToLetter2) numToLetter[sum % 10] = -1;
        if (!hadLetterToNum2) letterToNum[sn[2][i]] = -1;
      }

      if (!hadNumToLetter1) numToLetter[d1] = -1;
      if (!hadLetterToNum1) letterToNum[sn[1][i]] = -1;
    }
    return ans;
  }

  for (int d0 = i == s[0].size() - 1; d0 <= 9; d0++)
    for (int d1 = i == s[1].size() - 1; d1 <= 9; d1++)
    {
      if (d0 == d1 && sn[0][i] != sn[1][i]) continue;
      if (letterToNum[sn[0][i]] != -1 && letterToNum[sn[0][i]] != d0) continue;
      if (letterToNum[sn[1][i]] != -1 && letterToNum[sn[1][i]] != d1) continue;
      if (numToLetter[d0] != -1 && numToLetter[d0] != sn[0][i]) continue;
      if (numToLetter[d1] != -1 && numToLetter[d1] != sn[1][i]) continue;

      bool hadNumToLetter0 = numToLetter[d0] != -1;
      bool hadLetterToNum0 = letterToNum[sn[0][i]] != -1;
      bool hadNumToLetter1 = numToLetter[d1] != -1;
      bool hadLetterToNum1 = letterToNum[sn[1][i]] != -1;
      numToLetter[d0] = sn[0][i];
      letterToNum[sn[0][i]] = d0;
      numToLetter[d1] = sn[1][i];
      letterToNum[sn[1][i]] = d1;

      int sum = d0 + d1 + carry;
      if ((numToLetter[sum % 10] == -1 || numToLetter[sum % 10] == sn[2][i]) && (letterToNum[sn[2][i]] == -1 || letterToNum[sn[2][i]] == sum % 10))
      {
        bool hadNumToLetter2 = numToLetter[sum % 10] != -1;
        bool hadLetterToNum2 = letterToNum[sn[2][i]] != -1;
        numToLetter[sum % 10] = sn[2][i];
        letterToNum[sn[2][i]] = sum % 10;
        ans = max(ans, solve(i + 1, sum / 10, numToLetter, letterToNum));
        if (ans == 1) return ans;
        if (!hadNumToLetter2) numToLetter[sum % 10] = -1;
        if (!hadLetterToNum2) letterToNum[sn[2][i]] = -1;
      }

      if (!hadNumToLetter0) numToLetter[d0] = -1;
      if (!hadLetterToNum0) letterToNum[sn[0][i]] = -1;
      if (!hadNumToLetter1) numToLetter[d1] = -1;
      if (!hadLetterToNum1) letterToNum[sn[1][i]] = -1;
    }
  
  return ans;
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

    bool swapped = false;
    if (s[0].size() > s[1].size())
    {
      swap(s[0], s[1]);
      swapped = true;
    }

    for (int i = 0; i < 3; i++)
    {
      reverse(s[i].begin(), s[i].end());

      sn[i] = vector<int>(s[i].size());
      for (int j = 0; j < s[i].size(); j++)
        sn[i][j] = s[i][j] - 'a';
    }

    if (s[1].size() < s[2].size() - 1 || s[1].size() > s[2].size())
      printf("UNSOLVABLE\n");
    else
    {
      int can = solve();
      if (!can) printf("UNSOLVABLE\n");
      else
      {
        DEBUG printf("BOYAH\n");

        if (swapped)
          swap(sn[0], sn[1]), swap(s[0], s[1]);
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
  }
  return 0;
}