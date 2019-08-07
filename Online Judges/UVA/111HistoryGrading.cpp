#include <bits/stdc++.h>
using namespace std;

const int maxN = 20; int n;

void printArray(int array[])
{
  for (int i = 0; i < n; i ++) printf("%3d%c", array[i] + 1, i < n - 1 ? ' ' : '\n');
}

bool readArray(int array[])
{
  for (int i = 0, a; i < n; i ++)
  {
    if (scanf("%d", &a) == EOF) return(false);
    array[a - 1] = i;
  }
  return(true);
}

int memo[maxN];
int solve(int array[], int i, int event)
{
  if (i == n) return(0);
  if (memo[event] == -1)
  {
    int score = solve(array, i + 1, event);
    if (array[i] >= event) score = max(score, 1 + solve(array, i + 1, array[i]));
    memo[event] = score;
  }
  return(memo[event]);
}

int bottomUp(int array[])
{
  memset(memo, 0, sizeof(memo));
  for (int i = n - 1; i >= 0; i --)
    for (int j = i; j < n; j ++)
      if (array[i] <= array[j])
        memo[array[i]] = max(memo[array[i]], 1 + memo[array[j]]);
  int best = 0; for (int i = 0; i < n; i ++) best = max(best, memo[i]);
  return(best);
}

int main()
{
  scanf("%d", &n);
  int correctOrder[n]; readArray(correctOrder);
  int mapCorrect[n]; for (int i = 0; i < n; i ++) mapCorrect[correctOrder[i]] = i;
  int studentOrder[n];
  while (readArray(studentOrder))
  {
    int mappedStudent[n]; for (int i = 0; i < n; i ++) mappedStudent[i] = mapCorrect[studentOrder[i]];
    memset(memo, -1, sizeof(memo));
    // int score = solve(mappedStudent, 0, 0);
    int score = bottomUp(mappedStudent);
    printf("%d\n", score);
  }
  return (0);
}