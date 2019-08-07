#include <stdio.h>
#include <string.h>
#define leftNode tree[root][0]
#define rightNode tree[root][1]

int max(int a, int b)
{
  return(a > b ? a : b);
}

int findHeight(int tree[][2], int root)
{
  if (root == -1) return(0);
  if (leftNode == -1 && rightNode == -1) return(1);

  return(max(1 + findHeight(tree, leftNode), 1 + findHeight(tree, rightNode)));
}

int main()
{
  int nodes, connections, root;
  scanf("%d %d %d", &nodes, &connections, &root);

  int tree[nodes][2], node, left, right, i;
  memset(tree, -1, sizeof(tree));
  for (i = 0; i < connections; i ++)
  {
    scanf("%d %d %d", &node, &left, &right);
    tree[node][0] = left;
    tree[node][1] = right;
  }

  int answer = findHeight(tree, root);

  printf("%d\n", answer);

  return(0);
}