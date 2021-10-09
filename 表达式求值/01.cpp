/*
 * @Author: Yang Yang
 * @Date: 2021-10-09 19:02:50
 * @LastEditTime: 2021-10-09 22:10:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Experiment\Book_LNode.cpp
 */
#include <iostream>
#include <cstdlib>
#define defaultsize 1000
#define increasesize 5000

typedef struct
{
  char *base;
  char *top;
  int stacksize; //栈的存储容量
} OPRTstack;
typedef struct
{
  double *base;
  double *top;
  int stacksize;
} NUMstack;

int createStack(OPRTstack *s)
{
  s->base = (char *)malloc(sizeof(char) * defaultsize);
  if (!s->base)
    return 0;
  s->top = s->base;
  s->stacksize = 10;
  return 1;
}
int pop(OPRTstack *s, char *e)
{
  if (s->top == s->base)
    return 0;
  s->top--;
  *e = *(s->top);
  return 1;
}
int push(OPRTstack *s, char e)
{
  if (s->top - s->base >= s->stacksize)
  {
    s->base = (char *)realloc(s->base, sizeof(char) * (s->stacksize + increasesize));
    if (!s->base)
      return 0;
    s->top = s->base + s->stacksize;
    s->stacksize += increasesize;
  }
  *(s->top) = e;
  s->top++;
}
int isEmpty(OPRTstack *s)
{
  if (s->top == s->base)
    return 1;
  else
    return 0;
}
char GetTop(OPRTstack *s)
{
  if (!isEmpty(s))
  {
    char *temp = s->top;
    temp--;
    return *(temp);
  }
  else
    return '!'; //这样定义的话，栈里面不能存储！这个数据
}
void showStack(OPRTstack *s)
{
  if (isEmpty(s))
    return;
  for (int i = 0; i < s->top - s->base; i++)
  {
    printf("%c ", s->base[i]);
  }
  printf("  ");
}


int createStack(NUMstack *s)
{
  s->base = (double *)malloc(sizeof(double) * defaultsize);
  if (!s->base)
    return 0;
  s->top = s->base;
  s->stacksize = 10;
  return 1;
}
int pop(NUMstack *s, double *e)
{
  if (s->top == s->base)
    return 0;
  s->top--;
  *e = *(s->top);
  return 1;
}
int push(NUMstack *s, double e)
{
  if (s->top - s->base >= s->stacksize)
  {
    s->base = (double *)realloc(s->base, sizeof(double) * (s->stacksize + increasesize));
    if (!s->base)
      return 0;
    s->top = s->base + s->stacksize;
    s->stacksize += increasesize;
  }
  *(s->top) = e;
  s->top++;
}
int isEmpty(NUMstack *s)
{
  if (s->top == s->base)
    return 1;
  else
    return 0;
}
double GetTop(NUMstack *s)
{
  if (!isEmpty(s))
  {
    double *temp = s->top;
    temp--;
    return *(temp);
  }
  else
    return -1; //这样定义的话，栈里面不能存储！这个数据
}
void showStack(NUMstack *s)
{
  if (isEmpty(s))
    return;
  for (int i = 0; i < s->top - s->base; i++)
  {
    printf("%f ", s->base[i]);
  }
  printf("  ");
}
//判断c是不是运算符
int isOPRT(char c)
{
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
    return 1;
  else
    return 0;
}

char compare(char a, char b)
{
  if (a == '+')
  {
    if (b == '*' || b == '/' || b == '(')
      return '<';
    else
      return '>';
  }
  else if (a == '-')
  {
    if (b == '*' || b == '/' || b == '(')
      return '<';
    else
      return '>';
  }
  else if (a == '*')
  {
    if (b == '(')
      return '<';
    else
      return '>';
  }
  else if (a == '/')
  {
    if (b == '(')
      return '<';
    else
      return '>';
  }
  else if (a == '(')
  {
    if (b == ')')
      return '=';
    else if (b == '#')
      return '!';
    else
      return '<';
  }
  else if (a == ')')
  {
    if (b == '(')
      return '!';
    else
      return '>';
  }
  else if (a == '#')
  {
    if (b == ')')
      return '!';
    if (b == '#')
      return '=';
    else
      return '<';
  }
}
//运算函数
double calculate(double left, double right, char operators)
{
  switch (operators)
  {
  case '+':
    return left + right;

  case '-':
    return 1.0 * left - right;

  case '*':
    return left * right;

  case '/':
    return 1.0 * left / right;
  }
}

int main()
{
  //定义运算符栈和操作数栈
  OPRTstack oprt;     
  NUMstack num;     
  NUMstack temp;
  //定义所需的变量

  int build = 0;      
  double index;       
  int complex = 1;    
  char operators;     
  double left, right; 
  createStack(&num);
  createStack(&oprt);
  createStack(&temp);
  printf("键入运算表达式，以#结束\n");
  push(&oprt, '#');
  char c = getchar();
  int error = 0; //syntax error 标识符
  while (c != '#' || GetTop(&oprt) != '#')
  {
    while (!isOPRT(c)) 
    {
      push(&temp, c - '0');
      c = getchar();
    }
    while (!isEmpty(&temp)) 
    {
      pop(&temp, &index);
      build += (index * complex);
      complex *= 10;
    }
    complex = 1;
    if (build)
      push(&num, double(build)); 
    build = 0;

    if (isOPRT(c)) 
    {
      switch (compare(GetTop(&oprt), c))
      {
      case '<':
        push(&oprt, c);
        c = getchar();
        break;

      case '=':
        pop(&oprt, &operators);
        c = getchar();
        break;

      case '>':
        pop(&oprt, &operators);
        pop(&num, &right);
        pop(&num, &left);
        push(&num, calculate(left, right, operators)); 
        break;

      case '!':
        printf("Syntax Error!");
        error = 1;
        break;
      }
    }
    if (error)
      break;
  }
  if (!error)
    printf("结果为：%.2f", GetTop(&num));
  return 0;
}
