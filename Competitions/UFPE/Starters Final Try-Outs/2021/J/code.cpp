#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

#define cube22 vector<vector<vector<int>>>
const int TOP = 0, FACE = 1, BOTTOM = 2, BACK = 3, LEFT = 4, RIGHT = 5;
string faceMap[6] = {
  "TOP", "FACE", "BOTTOM", "BACK", "LEFT", "RIGHT"
};

char cubeStr[8][7];

cube22 cube;

void printCube(cube22 curr)
{
  printf("--cube:\n");
  for (int i = 0; i < 6; i++)
  {
    printf("--%d - %s\n", i, faceMap[i].c_str());
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        printf("%d%c", curr[i][j][k], k == 1 ? '\n' : ' ');
  }
  printf("-------\n");
}

int getAt(int i, int j)
{
  return cubeStr[i][j] - '0';
}

bool solved(const cube22 &curr)
{
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        if (curr[i][j][k] != curr[i][0][0])
          return false;
  }
  return true;
}

void rotateFace(int i, cube22 &curr)
{
  int a00 = curr[i][0][0], a01 = curr[i][0][1], a10 = curr[i][1][0], a11 = curr[i][1][1];
  curr[i][0][0] = a10;
  curr[i][0][1] = a00;
  curr[i][1][1] = a01;
  curr[i][1][0] = a11;
}
cube22 L(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(4, res);
  vector<int*> pos = {
    &res[TOP][0][0],
    &res[TOP][1][0],
    &res[FACE][0][0],
    &res[FACE][1][0],
    &res[BOTTOM][1][0],
    &res[BOTTOM][0][0],
    &res[BACK][1][0],
    &res[BACK][0][0],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Lp(const cube22 &curr)
{
  return L(L(L(curr)));
}

cube22 R(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(5, res);
  vector<int*> pos = {
    &res[TOP][1][1],
    &res[TOP][0][1],
    &res[BACK][0][1],
    &res[BACK][1][1],
    &res[BOTTOM][0][1],
    &res[BOTTOM][1][1],
    &res[FACE][1][1],
    &res[FACE][0][1],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Rp(const cube22 &curr)
{
  return R(R(R(curr)));
}

cube22 U(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(0, res);
  vector<int*> pos = {
    &res[FACE][0][1],
    &res[FACE][0][0],
    &res[LEFT][0][1],
    &res[LEFT][0][0],
    &res[BACK][0][0],
    &res[BACK][0][1],
    &res[RIGHT][0][1],
    &res[RIGHT][0][0],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Up(const cube22 &curr)
{
  return U(U(U(curr)));
}

cube22 F(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(1, res);
  vector<int*> pos = {
    &res[TOP][1][0],
    &res[TOP][1][1],
    &res[RIGHT][0][0],
    &res[RIGHT][1][0],
    &res[BOTTOM][1][1],
    &res[BOTTOM][1][0],
    &res[LEFT][1][1],
    &res[LEFT][0][1],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Fp(const cube22 &curr)
{
  return F(F(F(curr)));
}

cube22 D(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(2, res);
  vector<int*> pos = {
    &res[FACE][1][0],
    &res[FACE][1][1],
    &res[RIGHT][1][0],
    &res[RIGHT][1][1],
    &res[BACK][1][1],
    &res[BACK][1][0],
    &res[LEFT][1][0],
    &res[LEFT][1][1],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Dp(const cube22 &curr)
{
  return D(D(D(curr)));
}

cube22 B(const cube22 &curr)
{
  cube22 res = curr;
  rotateFace(3, res);
  vector<int*> pos = {
    &res[TOP][0][1],
    &res[TOP][0][0],
    &res[LEFT][0][0],
    &res[LEFT][1][0],
    &res[BOTTOM][0][0],
    &res[BOTTOM][0][1],
    &res[RIGHT][1][1],
    &res[RIGHT][0][1],
  };
  vector<int> aux;
  for (int i = 0; i < pos.size(); i++)
    aux.push_back(*pos[i]);
  for (int i = 0; i < pos.size(); i++)
    *pos[(i + 2) % pos.size()] = aux[i];
  return res;
}
cube22 Bp(const cube22 &curr)
{
  return B(B(B(curr)));
}

int solve(cube22 curr, int depth = 0)
{
  if (solved(curr)) return 1;
  if (depth == 5) return 0;

  if (solve(L(curr), depth + 1)) return 1;
  if (solve(R(curr), depth + 1)) return 1;
  if (solve(U(curr), depth + 1)) return 1;
  if (solve(D(curr), depth + 1)) return 1;
  if (solve(F(curr), depth + 1)) return 1;
  if (solve(B(curr), depth + 1)) return 1;

  if (solve(Lp(curr), depth + 1)) return 1;
  if (solve(Rp(curr), depth + 1)) return 1;
  if (solve(Up(curr), depth + 1)) return 1;
  if (solve(Dp(curr), depth + 1)) return 1;
  if (solve(Fp(curr), depth + 1)) return 1;
  if (solve(Bp(curr), depth + 1)) return 1;
  return false;
}

int main()
{
  for (int tt = 1; tt <= 1; tt++)
  {
    for (int i = 0; i < 8; i++)
      scanf(" %s", cubeStr[i]);

    cube = vector<vector<vector<int>>>(6, vector<vector<int>>(2, vector<int>(2)));
    // TOP
    cube[0] = {
      {getAt(0, 2), getAt(0, 3)},
      {getAt(1, 2), getAt(1, 3)},
    };
    // FACE
    cube[1] = {
      {getAt(2, 2), getAt(2, 3)},
      {getAt(3, 2), getAt(3, 3)},
    };
    // BOTTOM
    cube[2] = {
      {getAt(5, 2), getAt(5, 3)},
      {getAt(4, 2), getAt(4, 3)},
    };
    // BACK
    cube[3] = {
      {getAt(7, 2), getAt(7, 3)},
      {getAt(6, 2), getAt(6, 3)},
    };
    // LEFT
    cube[4] = {
      {getAt(5, 0), getAt(4, 0)},
      {getAt(5, 1), getAt(4, 1)},
    };
    // RIGHT
    cube[5] = {
      {getAt(4, 5), getAt(5, 5)},
      {getAt(4, 4), getAt(5, 4)},
    };

    // printCube(cube);
    // printCube(U(cube));

    int ans = solve(cube);

    // int ans = 0;
    printf("%s\n", ans ? "YES" : "NO");
  }

  return 0;
}