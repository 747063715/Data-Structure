#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
const int maxn = 110;
char priority[7][7] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', '0'}, // 此行"("=")"表示左右括号相遇，括号内运算已完成
    {'>', '>', '>', '>', '0', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '='} // "=" 表示整个表达式求值完毕
};                                      //  "0"表示不可能出现这种情况 ( 语法错误 )

//Precede 用于判断运算符栈栈顶运算符 a1 与读入运算符 a2 之间的优先关系函数
char Procede(char a, char b)
{ // 建立 pre[][] 到 运算符间的映射关系
    int i, j;
    switch (a)
    {
    case '+':
        i = 0;
        break;
    case '-':
        i = 1;
        break;
    case '*':
        i = 2;
        break;
    case '/':
        i = 3;
        break;
    case '(':
        i = 4;
        break;
    case ')':
        i = 5;
        break;
    case '#':
        i = 6;
        break; // # 是表达式的结束符
    }
    switch (b)
    {
    case '+':
        j = 0;
        break;
    case '-':
        j = 1;
        break;
    case '*':
        j = 2;
        break;
    case '/':
        j = 3;
        break;
    case '(':
        j = 4;
        break;
    case ')':
        j = 5;
        break;
    case '#':
        j = 6;
        break;
    }
    return priority[i][j];
}
//运算函数
int Operate(int m, int n, char x)
{
    if (x == '+')
        return m + n;
    if (x == '-')
        return n - m;
    if (x == '*')
        return m * n;
    if (x == '/')
        return n / m;
}

int main()
{
    stack<int> OPND;  
    stack<char> OPTR; 
    OPTR.push('#'); 
    char ss[2] = "#"; //尾部有\0
    char s[maxn];
    cin >> s;
    strcat(s, ss); // 运算式尾部加 "#"--结束运算符
    char c = s[0];
    int k = 1;
    while (c != '#' || OPTR.top() != '#')
    { //表达式未读完或者运算未完
        int y = 0;
        if (c >= '0' && c <= '9')
        {
            while (c >= '0' && c <= '9')
            { // 读入连续的数字
                y = y * 10 + (c - '0');
                c = s[k++];
            }
            OPND.push(y); // 把读进的数字入数字栈
        }
        else
        {
            switch (Procede(OPTR.top(), c))
            {
            case '<': //栈顶元素优先权低
                OPTR.push(c);
                c = s[k++];
                break;
            case '=':
                OPTR.pop(); // 脱括号
                c = s[k++]; // 读入下一个字符
                break;
            case '>': //退栈并将运算结果入栈
                char x = OPTR.top();
                OPTR.pop();
                int m = OPND.top();
                OPND.pop();
                int n = OPND.top();
                OPND.pop();
                OPND.push(Operate(m, n, x));
                break;
            }
        }
    }
    cout << OPND.top();
    return 0;
}
