#include <bits/stdc++.h>
using namespace std;
int DEBUG = 1;

int dx[7] = {2, 2, 1, 2, 2, 2, 1};
int majorScale[12][13];
map<int, const char*> intToString = {{1, "do"}, {2, "do#"}, {3, "re"}, {4, "re#"}, {5, "mi"}, {6, "fa"}, {7, "fa#"}, {8, "sol"}, {9, "sol#"}, {10, "la"}, {11, "la#"}, {12, "si"}};

int main()
{
  int size; scanf("%d", &size);
  int notes[size];
  for (int i = 0; i < size; i ++)
    scanf("%d", &notes[i]);

  for (int i = 0; i < 12; i ++) for (int j = 0; j < 13; j ++)
    majorScale[i][j] = 0;

  for (int i = 0; i < 12; i ++)
  {
    int k = i + 1;
    for (int j = 0; j < 7; j ++)
    {
      majorScale[i][((k - 1) % 12) + 1] = 1;
      k += dx[j];
    }
  }
  if (DEBUG)
  {
    for (int i = 0; i < 12; i ++)
    {
      printf("%s", intToString[i + 1]);
      for (int k = strlen(intToString[i + 1]); k < 4; k ++) printf(" ");
      printf(" - ");

      for (int j = 0; j < 13; j ++)
        if (majorScale[i][j])
        {
          printf("%s ", intToString[j]);
          for (int k = strlen(intToString[j]); k < 4; k ++) printf(" ");
        }
      printf("\n");
    }
  }

  int actualScale, j;
  for (actualScale = 0; actualScale < 12; actualScale ++)
  {
    for (j = 0; j < size; j ++)
      if (!majorScale[actualScale][(notes[j] - 1) % 12 + 1])
        break;
    if (j == size)
      break;
  }

  if (actualScale == 12)
    printf("desafinado\n");
  else
    printf("%s\n", intToString[actualScale + 1]);

  return(0);
}