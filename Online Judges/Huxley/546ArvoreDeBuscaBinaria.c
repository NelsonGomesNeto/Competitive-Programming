#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t
{
  int node;
  struct tree_t *left, *right;
} tree_t;

void printTree(tree_t *tree, int depth)
{
  printf("(");
  if (tree == NULL) { printf(")"); return; }
  printf("%d", tree->node);
  printTree(tree->left, depth + 1);
  printTree(tree->right, depth + 1);
  printf(")");
}

tree_t* newTree(int num)
{
  tree_t *temp = (tree_t*) malloc(1 * sizeof(tree_t));
  temp->node = num;
  temp->left = temp->right = NULL;
  return(temp);
}

int getNum(char treeString[], int *i)
{
  int num = 0;
  while (treeString[*i] >= '0' && treeString[*i] <= '9')
  {
    num = num * 10 + (treeString[*i] - '0');
    *i += 1;
  }
  return(num);
}

tree_t* fillTree(char treeString[], int *i)
{
  tree_t *tree = NULL;
  if (!treeString[*i]) return(tree);
  if (treeString[*i] == '(')
  {
    *i += 1;
    if (treeString[*i] == ')')
    {
      *i += 1;
      return(NULL);
    }
    int num = getNum(treeString, i);
    tree = newTree(num);
    tree->left = fillTree(treeString, i);
    tree->right = fillTree(treeString, i);
    *i += 1;
  }
  return(tree);
}

int isBinaryTree(tree_t *tree)
{
  if (tree == NULL) return(1);
  if (tree->left != NULL && tree->left->node > tree->node) return(0);
  if (tree->right != NULL && tree->right->node < tree->node) return(0);
  if (isBinaryTree(tree->left) && isBinaryTree(tree->right)) return(1);
  return(0);
}

int main()
{
  int size = 0; char treeString[10000], each;
  while (scanf("%c", &each) != EOF && each != '\n')
  {
    if (each == ' ') continue;
    treeString[size ++] = each;
  }

  int i = 0;
  tree_t *tree = fillTree(treeString, &i);
   printTree(tree, 0);
  printf("%s\n", isBinaryTree(tree) ? "VERDADEIRO" : "FALSO");

  return(0);
}