#include <bits/stdc++.h>
using namespace std;

void preProcess(string subString, int backTable[])
{
  int i = 0, j = -1; backTable[0] = -1;
  while (subString[i])
  {
    while (j >= 0 && subString[i] != subString[j])
      j = backTable[j];
    i ++; j ++;
    backTable[i] = j;
  }
}

int kmpSearch(string subString, string text, int backTable[])
{
  int i = 0, j = 0, count = 0;
  while (text[i])
  {
    while (j >= 0 && text[i] != subString[j])
      j = backTable[j];
    i ++; j ++;
    if (!subString[j])
    {
      count += 1;
      j = backTable[j];
    }
  }
  return(count);
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    getchar();
    string subString, text, aux;
    cin >> subString >> text;

    int backTable[subString.size() + 1];
    preProcess(subString, backTable);

    aux = text;
    while (text.size() < subString.size())
      text += aux;
    text += aux;
    aux = text;
    reverse(aux.begin(), aux.end());
    text += aux;

    printf("%c\n", kmpSearch(subString, text, backTable) ? 'S' : 'N');
  }
  return(0);
}