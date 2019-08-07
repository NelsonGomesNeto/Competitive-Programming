#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n;

string wordsStrings[maxN];

struct Word
{
  int id, vowels; char lastVowel;
  bool operator<(const Word &w) const
  {
    return(vowels < w.vowels || (vowels == w.vowels && lastVowel < w.lastVowel));
  }
  bool match(const Word &w)
  {
    return(vowels == w.vowels && lastVowel == w.lastVowel);
  }
};
Word words[maxN];
bool got[maxN];

bool isVowel(char a)
{
  return(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u');
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    cin >> wordsStrings[i];
    int vowels = 0; char last;
    for (int j = 0; j < wordsStrings[i].size(); j ++)
      if (isVowel(wordsStrings[i][j]))
        vowels ++, last = wordsStrings[i][j];
    words[i] = {i, vowels, last};
  }
  sort(words, words+n);

  vector<pair<pair<int, int>, pair<int, int>>> ans;

  for (int i = 0; i < n - 1; i ++)
    if (words[i].match(words[i + 1]))
    {
      ans.push_back({{-1, words[i].id}, {-1, words[i + 1].id}}), got[i] = got[i + 1] = true;
      i ++;
    }
  vector<Word> left; for (int i = 0; i < n; i ++) if (!got[i]) left.push_back(words[i]);

  int total = 0;
  for (int i = 0; i < (int) left.size() - 1 && total < ans.size(); i ++)
    if (left[i].vowels == left[i + 1].vowels)
    {
      ans[total].first.first = left[i].id, ans[total].second.first = left[i + 1].id;
      total ++, i ++;
    }
  for (int j = (int) ans.size() - 1; j > total; j --, total ++)
    ans[total].first.first = ans[j].first.second, ans[total].second.first = ans[j].second.second;

  printf("%d\n", total);
  for (int j = 0; j < total; j ++)
  {
    auto i = ans[j];
    cout << wordsStrings[i.first.first] << " " << wordsStrings[i.first.second] << endl;
    cout << wordsStrings[i.second.first] << " " << wordsStrings[i.second.second] << endl;
  }

  return(0);
}