#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
typedef struct stack_t stack_t;
typedef struct node_t node_t;
#define TAMANHO INT_MAX

node_t* newNode(int value); //Novo nó
stack_t* newStack(); //Nova pilha
bool isEmpty(stack_t *stack); //Está vazia?
bool isFull(stack_t *stack); //Está cheia?
int size(stack_t *stack); //Tamanho atual

void push(stack_t *stack, int value); //Adiciona
bool pop(stack_t *stack); //Remove
bool destroy(stack_t *stack); //Destrói

int main()
{
  char comando[30];
  stack_t *back = newStack();
  stack_t *forward = newStack();
  int atual = 0;
  while (scanf("%s", comando) != EOF)
  {
    getchar();
    if (comando[0] == 'E') //ENTER
    {
      if (atual == 0)
      { atual = 404; }
      else
      { push(back, 404); }
      while (!isEmpty(forward))
        pop(forward);
    }
    else if (comando[0] == 'B') //BACK
    {
      if (pop(back))
        push(forward, 404);

      if (isEmpty(back)) atual = 0;
    }
    else //FORWARD
    {
      if (pop(forward))
        push(back, 404);
    }
  }

  printf("BACK: %d\nFORWARD: %d\n", size(back), size(forward));
  destroy(back);
  destroy(forward);
  return(0);
}

struct node_t
{
  int value;
  node_t *bot;
};

struct stack_t
{
  int size;
  int cap;
  node_t *top;
};

node_t* newNode(int value)
{
  node_t *temp = (node_t*) malloc(1 * sizeof(node_t));
  temp->value = value;
  temp->bot = NULL;
  return(temp);
}

stack_t* newStack()
{
  stack_t *temp = (stack_t*) malloc(1 * sizeof(stack_t));
  temp->size = 0;
  temp->cap = TAMANHO;
  return(temp);
}

bool isEmpty(stack_t *stack)
{
  return(!stack->size);
}

bool isFull(stack_t *stack)
{
  return(stack->size == stack->cap);
}

int size(stack_t *stack)
{
  return(stack->size);
}

void push(stack_t *stack, int value)
{
  if (isFull(stack)) return;
  node_t *temp = newNode(value);
  if (isEmpty(stack))
  {
    stack->top = temp;
  }
  else
  {
    temp->bot = stack->top;
    stack->top = temp;
  }
  stack->size ++;
}

bool pop(stack_t *stack)
{
  if (isEmpty(stack)) return(0);
  node_t *temp = stack->top->bot;
  free(stack->top);
  stack->top = temp;
  stack->size --;
  return(1);
}

bool destroy(stack_t *stack)
{
  while (!isEmpty(stack))
    pop(stack);
  free(stack);
}
