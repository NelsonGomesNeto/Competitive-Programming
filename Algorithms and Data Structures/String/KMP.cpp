#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
char s[maxN + 1], t[maxN + 1];
int pi[maxN + 1];

void prefixFunction(char str[], int strSize)
{
  pi[0] = -1;
  for (int i = 0, j = -1; i < strSize;)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++ i] = ++ j;
  }
}
vector<int> kmpSearch(char str[], int strSize, char subStr[], int subStrSize)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < strSize;)
  {
    while (j >= 0 && str[i] != subStr[j]) j = pi[j];
    i ++, j ++;
    if (j == subStrSize)
    {
      occurrences.push_back(i - j);
      j = pi[j];
    }
  }
  return occurrences;
}

int main()
{
  scanf("%s\n%s", s, t);
  n = strlen(s), m = strlen(t);

  prefixFunction(t, m);

  vector<int> occurrences = kmpSearch(s, n, t, m);
  printf("%d occurrences\n", (int) occurrences.size());
  for (int i = 0; i < occurrences.size(); i ++)
    printf("%d%c", occurrences[i], i < occurrences.size() - 1 ? ' ' : '\n');

  return(0);
}