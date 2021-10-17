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
    {'<', '<', '<', '<', '<', '=', '0'}, // ����"("=")"��ʾ�����������������������������
    {'>', '>', '>', '>', '0', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '='} // "=" ��ʾ�������ʽ��ֵ���
};                                      //  "0"��ʾ�����ܳ����������

//Precede �����ж������ջջ������� a1 ���������� a2 ֮������ȹ�ϵ����
char Procede(char a, char b)
{ // ���� pre[][] �� ��������ӳ���ϵ
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
        break; // # �Ǳ��ʽ�Ľ�����
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
//���㺯��
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
    char ss[2] = "#"; //β����\0
    char s[maxn];
    cin >> s;
    strcat(s, ss); // ����ʽβ���� "#"--���������
    char c = s[0];
    int k = 1;
    while (c != '#' || OPTR.top() != '#')
    { //���ʽδ�����������δ��
        int y = 0;
        if (c >= '0' && c <= '9')
        {
            while (c >= '0' && c <= '9')
            { // ��������������
                y = y * 10 + (c - '0');
                c = s[k++];
            }
            OPND.push(y); // �Ѷ���������������ջ
        }
        else
        {
            switch (Procede(OPTR.top(), c))
            {
            case '<': //ջ��Ԫ������Ȩ��
                OPTR.push(c);
                c = s[k++];
                break;
            case '=':
                OPTR.pop(); // ������
                c = s[k++]; // ������һ���ַ�
                break;
            case '>': //��ջ������������ջ
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
    cout << OPND.top();                                   //�������ջ��Ԫ��
    return 0;
}
