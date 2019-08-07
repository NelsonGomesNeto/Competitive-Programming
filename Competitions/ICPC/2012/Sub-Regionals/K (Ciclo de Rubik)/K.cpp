#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

char movements[81];
int cube[6][3][3];
char movementMap[256], all[13] = "FfBbUuDdLlRr";
// 0 1 2 3 4 5
// F B U D L R
int corners[4][2] = {{0, 0}, {0, 2}, {2, 2}, {2, 0}};
// Indicates the 4 faces of the i-th movement
int sideMap[6][4] = {{2, 5, 3, 4}, {3, 5, 2, 4}, {1, 5, 0, 4}, {0, 5, 1, 4}, {0, 3, 1, 2}, {0, 2, 1, 3}};
// Indicates the starting corner of the i-th movement
int cornerMap[6][4] = {{3, 0, 2, 2}, {0, 2, 1, 0}, {0, 1, 1, 1}, {3, 3, 2, 3}, {0, 3, 3, 0}, {2, 2, 1, 1}};
//    0  1     2    3
// down up right left
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
int dirMap[6][4] = {{2, 0, 3, 1}, {2, 1, 3, 0}, {2, 3, 3, 3}, {2, 2, 3, 2}, {0, 1, 1, 0}, {1, 1, 0, 0}};
// int faceMap[6] = {0, 1, 2, 3, 4, 5}; just divide movementMap by 2
// starts from piece 2 or 6 (see on turnFace)
int rotationMap[6] = {1, -1, 1, -1, 1, 1};

void turnFace(int face)
{
  int pieces[8], p = 0, i = 0, j = 0;
  int positions[8][2];
  while (j < 3)
  {
    positions[p][0] = i, positions[p][1] = j;
    pieces[p ++] = cube[face][i][j ++];
  }
  j --, i ++;
  while (i < 3)
  {
    positions[p][0] = i, positions[p][1] = j;
    pieces[p ++] = cube[face][i ++][j];
  }
  i --, j --;
  while (j >= 0)
  {
    positions[p][0] = i, positions[p][1] = j;
    pieces[p ++] = cube[face][i][j --];
  }
  j ++, i --;
  while (i >= 1)
  {
    positions[p][0] = i, positions[p][1] = j;
    pieces[p ++] = cube[face][i --][j];
  }
  if (rotationMap[face] == -1) reverse(pieces, pieces+8);
  p = 6 + (rotationMap[face] == -1 ? -1 : 0);
  for (int k = 0, a = 0; k < 8; k ++, a = ((a + rotationMap[face]) % 8 + 8) % 8, p = (p + 1) % 8)
  {
    DEBUG printf("\t\t%d %d - %d\n", positions[a][0], positions[a][1], p);
    cube[face][positions[a][0]][positions[a][1]] = pieces[p];
  }
}
void turnSide(int face)
{
  int pieces[12], p = 0;
  for (int f = 0; f < 4; f ++)
    for (int i = corners[cornerMap[face][f]][0], j = corners[cornerMap[face][f]][1], a = 0; a < 3; a ++, i += di[dirMap[face][f]], j += dj[dirMap[face][f]])
      pieces[p ++] = cube[sideMap[face][f]][i][j];
  p = 9;
  for (int f = 0; f < 4; f ++)
    for (int i = corners[cornerMap[face][f]][0], j = corners[cornerMap[face][f]][1], a = 0; a < 3; a ++, i += di[dirMap[face][f]], j += dj[dirMap[face][f]])
    {
      // printf("\t\t%d - %d %d\n", sideMap[face][f], i, j);
      cube[sideMap[face][f]][i][j] = pieces[p ++];
      p %= 12;
    }
}
void apply(char op)
{
  if (op >= 'a' && op <= 'z')
    for (int i = 0; i < 3; i ++)
      apply(toupper(op));
  else
  {
    int face = movementMap[op] >> 1;
    DEBUG printf("\tTurning face: %d\n", face);
    turnFace(face);
    turnSide(face);
  }
}

bool solved()
{
  for (int i = 0; i < 6; i ++)
    for (int j = 0; j < 3; j ++)
      for (int k = 0; k < 3; k ++)
        if (cube[i][j][k] != i)
          return(false);
  return(true);
}

int main()
{
  for (int i = 0; i < 12; i ++) movementMap[all[i]] = i;

  while (scanf("%s", movements) != EOF)
  {
    getchar();
    for (int i = 0; i < 6; i ++)
      for (int j = 0; j < 3; j ++)
        for (int k = 0; k < 3; k ++)
          cube[i][j][k] = i;
    int ans = 0;
    do
    {
      for (int i = 0; movements[i]; i ++)
      {
        DEBUG printf("Movement: %c\n", movements[i]);
        apply(movements[i]);
      }
      ans ++;
    } while (!solved());
    printf("%d\n", ans);
  }
  return(0);
}