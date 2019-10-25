#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, w;
int a[maxN], da[maxN], b[maxN], db[maxN];

int backTable[maxN + 1];
void preProcess(int subStr[], int subStrSize)
{
  memset(backTable, -1, sizeof(backTable));
  for (int i = 0, j = -1; i < subStrSize;)
  {
    while (j >= 0 && subStr[i] != subStr[j]) j = backTable[j];
    backTable[++ i] = ++ j;
  }
}
vector<int> kmp(int str[], int strSize, int subStr[], int subStrSize)
{
  vector<int> occurrences;
  for (int i = 0, j = 0; i < strSize;)
  {
    while (j >= 0 && str[i] != subStr[j]) j = backTable[j];
    i ++, j ++;
    if (j == subStrSize)
    {
      occurrences.push_back(i - j);
      j = backTable[j];
    }
  }
  return occurrences;
}

int main()
{
  scanf("%d %d", &n, &w);
  if (w == 1)
  {
    printf("%d\n", n);
    return 0;
  }
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    if (i) da[i - 1] = a[i] - a[i - 1];
  }
  for (int i = 0; i < w; i ++)
  {
    scanf("%d", &b[i]);
    if (i) db[i - 1] = b[i] - b[i - 1];
  }

  preProcess(db, w - 1);
  vector<int> occurrences = kmp(da, n - 1, db, w - 1);
  printf("%d\n", (int) occurrences.size());

  return 0;
}