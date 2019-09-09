#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
char s[maxN + 1], t[maxN + 1];
int backTable[maxN + 1];

void preProcess(char subStr[])
{
  memset(backTable, -1, sizeof(backTable));
  for (int i = 0, j = -1; subStr[i];)
  {
    while (j >= 0 && subStr[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    backTable[i] = j;
  }
}
vector<int> kmpSearch(char str[], char subStr[])
{
  vector<int> occurrences;
  for (int i = 0, j = 0; str[i];)
  {
    while (j >= 0 && str[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    if (!subStr[j])
    {
      occurrences.push_back(i - j);
      j = backTable[j];
    }
  }
  return occurrences;
}

int main()
{
  scanf("%s\n%s", s, t);

  preProcess(t);

  vector<int> occurrences = kmpSearch(s, t);
  printf("%d occurrences\n", (int) occurrences.size());
  for (int i = 0; i < occurrences.size(); i ++)
    printf("%d%c", occurrences[i], i < occurrences.size() - 1 ? ' ' : '\n');

  return(0);
}