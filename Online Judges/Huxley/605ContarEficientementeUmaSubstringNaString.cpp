#include <bits/stdc++.h>
using namespace std;

void preProcess(string subString, vector<int>& backTable)
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

int kmpSearch(string text, string subString, vector<int> backTable, vector<int>& occurrence)
{
  int i = 0, j = 0, count = 0;
  while (text[i])
  {
    while (j >= 0 && text[i] != subString[j])
      j = backTable[j];

    i ++; j ++;
    if (!subString[j])
    {
      occurrence.push_back(i - j);
      j = backTable[j];
      count ++;
    }
  }
  return(count);
}

int main()
{
  string text, subString;
  getline(cin, text);
  getline(cin, subString);
  //cout << text << endl << subString << endl;

  vector<int> backTable(subString.size() + 1);
  preProcess(subString, backTable);

  vector<int> occurrence;
  int found = kmpSearch(text, subString, backTable, occurrence);

  for (int i = 0; i < found; i ++)
    printf("%d\n", occurrence[i]);
  if (!found)
    printf("-1\n");

  return(0);
}