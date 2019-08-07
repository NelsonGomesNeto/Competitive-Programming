#include <bits/stdc++.h>
using namespace std;

const int maxN = 50; int n;

struct Node
{
  int value;
  Node *left, *right;
};
Node *bst;
Node* newNode(int value = 0)
{
  Node *temp = (Node*) malloc(sizeof(Node));
  temp->value = value;
  temp->left = temp->right = NULL;
  return(temp);
}
void insert(int value, Node *curr = bst)
{
  if (value <= curr->value)
  {
    if (curr->left == NULL) curr->left = newNode(value);
    else insert(value, curr->left);
  }
  else
  {
    if (curr->right == NULL) curr->right = newNode(value);
    else insert(value, curr->right);
  }
}
int getHeight(Node *curr = bst)
{
  if (curr == NULL) return(0);
  return(1 + max(getHeight(curr->left), getHeight(curr->right)));
}

int main()
{
  scanf("%d", &n);
  bst = newNode();
  scanf("%d", &bst->value);

  for (int i = 0; i < n - 1; i ++)
  {
    int value; scanf("%d", &value);
    insert(value);
  }

  int height = getHeight() + 1;

  char mat[height][(1 << height) + 2]; memset(mat, '_', sizeof(mat));
  // bfs
  queue<pair<Node*, pair<int, int>>> q; q.push({bst, {0, (1 << (height - 1))}});
  while (!q.empty())
  {
    Node *curr = q.front().first; int i = q.front().second.first, j = q.front().second.second; q.pop();
    mat[i][j] = curr == NULL ? 'x' : (curr->value + '0');
    if (i == height - 1 || curr == NULL) continue;
    q.push({curr->left, {i + 1, j - (1 << (height - (i + 2)))}});
    q.push({curr->right, {i + 1, j + (1 << (height - (i + 2)))}});
  }

  for (int i = 0; i < height - 1; i ++)
  {
    mat[i][(1 << height) + 1] = '\0';
    printf("%s\n", mat[i]);
  }

  return(0);
}
/*
________3________
____2_______4____
__1___x___x___5__

________3________
___2_________0___
1_____x___x_____x
*/