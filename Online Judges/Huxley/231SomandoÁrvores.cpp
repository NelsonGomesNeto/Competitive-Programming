#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, inf = 1e9; int sum;

struct Tree
{
  int value, left, right;
};
vector<Tree> tree; int t = 0;
char treeString[maxN]; int sat;

int numDigits(int num)
{
  int sz = num <= 0;
  while (num) num /= 10, sz ++;
  return sz;
}

void readTree(int prv = -1, bool isLeft = false)
{
  char op, cl; int num = inf;
  sscanf(treeString + sat, "%c%d", &op, &num);
  sat += 1 + (num != inf)*numDigits(num);
  int me = tree.size();
  if (num != inf)
  {
    if (prv != -1 && isLeft)
      tree[prv].left = me;
    if (prv != -1 && !isLeft)
      tree[prv].right = me;
    tree.push_back(Tree{num, -1, -1});
    readTree(me, true);
    readTree(me, false);
  }
  sscanf(treeString + sat, "%c", &cl); sat ++;
}
void printSpaces(int spaces) { while (spaces --) printf("   "); }
void printTree(int u = 0, int depth = 0, int s = 0)
{
  if (tree.empty() || u == -1) return;
  printSpaces(depth); printf("(%d, %d, %d)\n", u, tree[u].value, s + tree[u].value);
  printTree(tree[u].left, depth + 1, s + tree[u].value);
  printTree(tree[u].right, depth + 1, s + tree[u].value);
}
bool hasSum(int u = 0, int s = 0)
{
  if (tree.empty() || u == -1) return false;
  s += tree[u].value;
  if (tree[u].left == -1 && tree[u].right == -1) return s == sum;
  return hasSum(tree[u].left, s) || hasSum(tree[u].right, s);
}

int main()
{
  while (scanf("%d", &sum) != EOF && sum != -1000)
  {
    memset(treeString, '\0', sizeof(treeString));
    int at = 0, op = 0;
    while (!at || op)
    {
      scanf("%c", &treeString[at]);
      if (treeString[at] == '(') op ++;
      else if (treeString[at] == ')') op --;
      if (!op || treeString[at] == '\n' || treeString[at] == ' ' || treeString[at] == '\r') continue;
      at ++;
    }
    tree.clear(), t = 0, sat = 0;
    readTree();
    printTree();
    printf("%s\n", hasSum() ? "sim" : "nao");
  }
  return(0);
}