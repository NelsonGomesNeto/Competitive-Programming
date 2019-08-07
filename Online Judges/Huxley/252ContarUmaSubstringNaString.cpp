#include <bits/stdc++.h>

void preProcess(char subString[], int backTable[])
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

int kmpSearch(char string[], char subString[], int backTable[])
{
  int i = 0, j = 0, occurences = 0;
  while (string[i])
  {
    while (j >= 0 && string[i] != subString[j])
      j = backTable[j];
    i ++; j ++;
    if (!subString[j])
    {
      j = backTable[j];
      occurences ++;
    }
  }
  return(occurences);
}

int main()
{
  char string[1000000], subString[1000000];
  scanf("%[^\n]\n%[^\n]", string, subString);
  int sizeString = strlen(string), sizeSubString = strlen(subString);

  int backTable[sizeSubString + 1];
  preProcess(subString, backTable);

  int occurrences = kmpSearch(string, subString, backTable);
  printf("%d\n", occurrences);

  return(0);
}