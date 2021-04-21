#include <bits/stdc++.h>
#define DEBUG if(0)
#define DEBUG2 if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Let's look at a simpler version of the problem, suppose you have some numbers
  and you want to count how many ways to place them into the cube faces (discarting
  ways that are equal by rotations).

  To solve that we only need to know how many of them are equal!
  It doesn't matter if it's [1, 2, 3, 4, 5, 5] or [343, 117, 2, 1, 6, 6], both of them
  have the same number of ways to fill the faces.

  And you can calculate it by trying every possible permutation and then removing the ones
  that are already present through others rotations.
    It's simpler then it looks:
      Map an array to cube faces
      Implement rotations (so that you can iterate through all 24 rotations of a cube)
      Then for every permutation of the numbers:
        Through all possible rotations, put the lexicographically smallest into an set
          (smallest lexycographically is just a cheap way to ensure that
          if two ways of filling are the same, they sure will have the same lexicographically
          smallest rotation)

  Cool, but what can we achieve with it.


  Notice that we can also calculate the combinations of numbers that sum to s, and even more
  we can add restrictions to them!
  Let's use x1, x2, x3, x4, x5, x6 to represent the numbers that we will put in the cube faces
  Let's make x1 <= x2 <= x3 <= x4 <= x5 <= x6

  Now, if x1 = x2 < x3 = x4 = x5 < x6, it's the same as having two repeated
  numbers: [1, 1, 2, 2, 2, 3].
  So, the number of ways to fill the cube with these restrictions is equal to:
    a * b, where:
      a = Number of ways to paint [1, 1, 2, 2, 2, 3]
      b = Number of combinations of numbers where x1 = x2 < x3 = x4 = x5 < x6 and sum(x) = s

  That number of combinations can be done with DigitDP or Fast Matrix Exponentiation
  I will show only DigitDP, and it's a bit tricky
    the memorization matrix is:
      memo[i][carry] = number of combinations whose sum so far is equal until the i-th
      digit of s and has carry 'carry'
  You will need to get rid of the rules x1 = x2 < x3 = x4 = x5 < x6
  You can do that be getting what that represents into the sum:
    x6 - x5 will be present once, let's call it y3
    x3 - x2 will be present 4 times, let's call it y2
    x2 - x1 will be present 6 times, let's call it y1
  So we can repesent the sum as: 6*y1 + 4*y2 + y3 = s
    (And this is the only restriction)

  But we're not allowed to have 0s, so just subtract 1 from each x
    Notice that we're substracting 1 from each x and 6*y1 + 4*y2 + y3 has 11 'x's
    So it's: 6*y1 + 4*y2 + y3 = s - 11
  Now we're allowed to have 0s :)

  With that said, we can apply the DigitDP

  NICE
*/

lli s;
vector<int> sDigits;
lli fillSDigits(vector<int> &equation)
{
  lli sum = 0;
  for (int i: equation) sum += i;

  sDigits.clear();
  lli aux = s - sum;
  while (aux)
  {
    sDigits.push_back(aux % 10);
    aux /= 10;
  }
  return s - sum;
}
const int maxFaces = 6;
const lli mod = 998244353;

lli memo2[maxFaces][210];
lli countPossibleDigits(vector<int> &equation, int target, int i = 0, int sum = 0)
{
  if (target < 0 || sum > target) return 0;
  if (i == equation.size())
    return sum == target;
  lli &ans = memo2[i][sum];
  if (ans != -1)
    return ans;

  ans = 0;
  for (int d = 0; d <= 9; d++)
    ans = (ans + countPossibleDigits(equation, target, i + 1, sum + d * equation[i])) % mod;
  return ans;
}

lli memo[18][100];
lli solve(vector<int> &equation, int i = 0, int carry = 0)
{
  if (i == sDigits.size())
    return carry == 0;
  lli &ans = memo[i][carry];
  if (ans != -1)
    return ans;

  ans = 0;
  for (int newCarry = 0; newCarry <= 20; newCarry++)
  {
    memset(memo2, -1, sizeof(memo2));
    ans = (ans + countPossibleDigits(equation, newCarry * 10 + sDigits[i] - carry) * solve(equation, i + 1, newCarry) % mod) % mod;
  }
  return ans;
}

void xRotation(vector<int> &cube)
{
  /* Rotation along the x-axis (Left-Right axis)
    2          2
  0 1 3 4 -> 1 3 4 0
    5          5
  */
  int aux0 = cube[0], aux1 = cube[1], aux3 = cube[3], aux4 = cube[4];
  cube[0] = aux1, cube[4] = aux0, cube[3] = aux4, cube[1] = aux3;
}
void zRotation(vector<int> &cube)
{
  /* Rotation along the z-axies (Bottom-Top axis)
    2          0
  0 1 3 4 -> 5 1 2 4
    5          3
  */
  int aux0 = cube[0], aux2 = cube[2], aux3 = cube[3], aux5 = cube[5];
  cube[0] = aux5, cube[2] = aux0, cube[3] = aux2, cube[5] = aux3;
}
int countUniqueWaysToWrite(vector<int> &equation)
{
  vector<int> eq = equation;
  sort(eq.begin(), eq.end());

  vector<int> nums;
  for (int i = 0; i < eq.size(); i++)
    for (int j = 0; j < eq[i]; j++)
      nums.push_back(i);
  vector<int> aux = nums;

  /*
      2
    0 1 3 4
      5
    0 - Face
    1 - Bottom
    2 - Left
    5 - Right
    3 - Back
    4 - Top
    There are 24 possible rotations
    You can choose 6 faces to be at the bottom and then
    choose 4 faces to be at the face
  */

  set<vector<int>> ways;
  do
  {
    nums = aux;
    vector<int> lexicographicallySmallestRotation = nums;

    for (int i = 0; i < 4; i++) // Bottoms: 0, 1, 3, 4
    {
      for (int j = 0; j < 4; j++)
      {
        lexicographicallySmallestRotation = min(lexicographicallySmallestRotation, nums);
        zRotation(nums);
      }
      xRotation(nums);
    }

    // Bottom 2
    zRotation(nums);
    xRotation(nums);
    aux = nums;
    for (int j = 0; j < 4; j++)
    {
      lexicographicallySmallestRotation = min(lexicographicallySmallestRotation, nums);
      zRotation(nums);
    }

    // Bottom 5
    xRotation(nums); xRotation(nums);
    for (int j = 0; j < 4; j++)
    {
      lexicographicallySmallestRotation = min(lexicographicallySmallestRotation, nums);
      zRotation(nums);
    }

    ways.insert(lexicographicallySmallestRotation);
  }
  while (next_permutation(aux.begin(), aux.end()));

  DEBUG2 {
    printf("{");
    bool start = true;
    for (auto &rot: ways)
    {
      if (!start) printf(", ");
      printf("'");
      for (int i: rot) printf("%d", i);
      printf("'");
      start = false;
    }
    printf("}\n");
  }

  return ways.size();
}

lli findCombinations(int i = 0, vector<int> equation = {0})
{
  if (i == maxFaces)
  {
    vector<int> deltaEquation = equation;
    for (int i = deltaEquation.size() - 2; i >= 0; i--)
      deltaEquation[i] += deltaEquation[i + 1];
    lli targetS = fillSDigits(deltaEquation);
    DEBUG {

      memset(memo, -1, sizeof(memo));
      printf("%lld || ", targetS);
      for (int j = 0; j < equation.size(); j++)
        printf("%d%s", equation[j], j < equation.size() - 1 ? " + " : " || ");
      for (int j = 0; j < deltaEquation.size(); j++)
        printf("%d%s", deltaEquation[j], j < deltaEquation.size() - 1 ? " + " : " || ");
      printf("%d %lld\n", countUniqueWaysToWrite(equation), solve(deltaEquation));
    }

    /*
      return numberOfWaysToPaint * numberOfWaysToSolveTheEquationForS
        number of ways to fill these numbers in the cube, where equation[i] is the number
        of times each number appeared, so we need to manually apply all possible rotations
        and count only the uniques

        number o ways to solve the equation = s, is the numbers we can choose for each
        number such that inputing thme into the equation will result s
    */
    memset(memo, -1, sizeof(memo));
    return solve(deltaEquation) * countUniqueWaysToWrite(equation) % mod;
  }

  lli ans = 0;
  vector<int> aux = equation;
  if (i != 0)
  {
    equation.push_back(1);
    ans = (ans + findCombinations(i + 1, equation)) % mod;
  }

  equation = aux;
  equation.back()++;
  ans = (ans + findCombinations(i + 1, equation)) % mod;

  // // x[i] = x[i - 1]
  // equation.back()++;
  // ans = (ans + findCombinations(i + 1, equation)) % mod;

  // // x[i] > x[i - 1]
  // if (i != 0)
  // {
  //   equation.back()--;
  //   equation.push_back(1);
  //   ans = (ans + findCombinations(i + 1, equation)) % mod;
  // }

  return ans;
}

int main()
{
  while (~scanf("%lld", &s))
  {
    // s -= 6; // allows x values to be 0
    sDigits.clear();
    lli aux = s;
    while (aux)
    {
      sDigits.push_back(aux % 10);
      aux /= 10;
    }

    lli ans = findCombinations();
    printf("%lld\n", ans);
  }
  return 0;
}