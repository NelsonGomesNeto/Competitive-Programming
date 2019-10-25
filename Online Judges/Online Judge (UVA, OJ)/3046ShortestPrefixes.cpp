#include <stdio.h>
#include <string.h>
using namespace std;

const int maxN = 10000; int n;
char dataset[maxN][21]; int datasetSize[maxN], minPrefix[maxN];

bool readLine(int id)
{
  char letter; int i = 0;
  while (scanf("%c", &letter) != EOF && letter != '\n') if (letter != '\r') dataset[id][i ++] = letter;
  return(datasetSize[id] = i);
}

int getPrefix(int id)
{
  int end = 0;
  for (int i = 0; i < n; i ++)
  {
    if (i == id) continue;
    bool match = true;
    for (int j = 0; j <= end && j < datasetSize[i] && j < datasetSize[id]; j ++)
      if (dataset[i][j] != dataset[id][j])
        match = false;
    if (!match) continue;
    while (end < datasetSize[i] && end + 1 < datasetSize[id] && dataset[i][end] == dataset[id][end])
      end ++;
  }
  return(end);
}

int main()
{
  int t = 1; scanf("%d ", &t);
  while (t --)
  {
    memset(dataset, '\0', sizeof(dataset));
    for (n = 0; readLine(n); n ++);

    for (int i = 0; i < n; i ++)
      minPrefix[i] = getPrefix(i);

    for (int i = 0; i < n; i ++)
    {
      printf("%s ", dataset[i]);
      for (int j = 0; j <= minPrefix[i]; j ++) printf("%c", dataset[i][j]);
      printf("\n");
    }
    if (t) printf("\n");
  }
  return(0);
}