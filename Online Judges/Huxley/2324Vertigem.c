#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 0 - up, 1 - down, 2 - left, 3 - right, 4 - hole
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

typedef struct map_tt
{
  char name[101]; int isPalindrome;
  int **next, **score, r, c, scored;
} map_t;

void printMap(map_t map)
{
  printf("%s %dx%d - scored: %d\n", map.name, map.r, map.c, map.scored);
  for (int i = 0; i < map.r; i ++)
    for (int j = 0; j < map.c; j ++)
      printf("(%d, %d)%c", map.next[i][j], map.score[i][j], j < map.c - 1 ? ' ' : '\n');
}

int isPalindrome(char s[])
{
  for (int i = 0, j = strlen(s) - 1; i <= j; i ++, j --)
    if (s[i] != s[j]) return(0);
  return(1);
}

int circular(int i, int n)
{
  return(((i % n) + n) % n);
}

int go(map_t maps[], int mi, int i, int j)
{
  int totalScore = 0;
  while (!(i == maps[mi].r - 1 && j == maps[mi].c - 1))
  {
    // printf("%d %d %d (%d, %d, dy %d, dx %d) - %d\n", mi, i, j, maps[mi].next[i][j], maps[mi].score[i][j], dy[maps[mi].next[i][j]], dx[maps[mi].next[i][j]], totalScore);
    if (maps[mi].next[i][j] == 4)
    {
      mi = maps[mi].score[i][j]; i = (totalScore / maps[mi].c) % maps[mi].r; j = totalScore % maps[mi].c;
      // printf("%d %d %d - %d %d\n", mi, maps[mi].r, maps[mi].c, i, j);
    }
    else
    {
      totalScore += maps[mi].score[i][j] * (1 + maps[mi].isPalindrome);
      maps[mi].scored += maps[mi].score[i][j] * (1 + maps[mi].isPalindrome);
      int nextI = circular(i + dy[maps[mi].next[i][j]], maps[mi].r), nextJ = circular(j + dx[maps[mi].next[i][j]], maps[mi].c);
      i = nextI; j = nextJ;
    }
  }
  totalScore += maps[mi].score[i][j] * (1 + maps[mi].isPalindrome);
  maps[mi].scored += maps[mi].score[i][j] * (1 + maps[mi].isPalindrome);
  return(totalScore);
}

int main()
{
  int n; scanf("%d", &n);
  map_t maps[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%d %d\n%s", &maps[i].r, &maps[i].c, maps[i].name); maps[i].scored = 0; maps[i].isPalindrome = isPalindrome(maps[i].name);
    printf("%s %d\n", maps[i].name, maps[i].isPalindrome);
    maps[i].next = (int**) malloc(maps[i].r * sizeof(int*));
    maps[i].score = (int**) malloc(maps[i].r * sizeof(int*));
    for (int j = 0; j < maps[i].r; j ++)
    {
      maps[i].next[j] = (int*) malloc(maps[i].c * sizeof(int));
      maps[i].score[j] = (int*) malloc(maps[i].c * sizeof(int));
      for (int k = 0; k < maps[i].c; k ++)
        scanf("%d,%d", &maps[i].next[j][k], &maps[i].score[j][k]);
    }
  }
  for (int i = 0; i < n; i ++)
    printMap(maps[i]);

  int totalScore = go(maps, 0, 0, 0);
  printf("%d\n", totalScore);
  for (int i = 0; i < n; i ++)
    printf("%s %d\n", maps[i].name, maps[i].scored);

  return(0);
}