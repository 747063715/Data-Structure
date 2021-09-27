#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define OK true
#define ERROR false
#define Status bool
//定义结构体数据类型
typedef struct
{
    char no[20];
    char name[50];
    float price;
}Book;
//定义一个单链表
typedef struct LNode
{
    Book data;
    struct LNode *next;

}LNode, *LinkList;
//重载>>运算符
istream & operator>>(istream &in, Book &A){
    in >> A.no >> A.name >>A.price;
    return in;
}
//创建单链表
void CreateList_R(LinkList &L, int n)
{
    L = new LNode;
    L->next=NULL;
    LinkList r=L;
    for(int i = 0;i<n;i++)
    {
        cout<<"请输入图书信息："<<endl;
        LinkList p = new LNode;
        cin>>p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}
//取值操作，返回L中第i个数据元素的值
int GetElem(LinkList &L,int i,Book &e)
{
    LinkList p = L->next;
    int j = 1;
    while(p && j<i)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i) return false;
    e = p->data;
    return 0;
}
//重载!=运算符
bool operator!=(Book a, Book b)
{
    if(a.no==b.no && a.name==b.name && a.price==b.price) return true;
    else return false;

}
//查找操作,返回该数据的位置序号
int LocateElem_L(LinkList L, Book e)
{
    LinkList p = L->next;
    int j = 1;
    while(p && p->data!=e)
    {
        p = p->next;
        ++j;
    }
    if(p) return j; //返回位置的序号
    else return 0;
} 
//插入操作
Status ListInsert(LinkList &L, int i, Book e)
{
    LinkList p = L;
    int j = 0;
    while(p && j<i-1)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i-1) return false;   //找到第i-1个数据元素
    LinkList s = new LNode;     //生成新的结点
    s->next = p->next;
    p->next = s;
    return true;
}
//删除操作,并保存删除结点的数据
Status ListDelete(LinkList &L, int i,Book e)
{
    LinkList p = L;
    int j = 0;
    while((p->next) && (j<i-1))   //找到第i-1个数据元素
    {
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i-1) return false;
    LinkList q = p->next;
    p->next = q->next;
    e = q->data;             //存储删除结点的数据
    delete q;
    return 0;            
}
//计算链表的表长
int ListLength(LinkList L)
{
    LinkList p;
    p = L->next;
    int i = 0;
    while(p)
    {
        i++;
        p = p->next;
    }
    return i;

}
//重载<<
ostream & operator<<(ostream &out, Book &A)
{
    out << A.no << A.name <<A.price;
    return out;
}
//打印
void ShowList(LinkList &L)
{
    LinkList p;
	p=L->next;
    cout<<"ISBN"<<" "<<"书名"<<" "<<"价格"<<endl;
    while(p)
    {
        cout<<p->data.no<<" "<<p->data.name<<" "<<p->data.price<<endl;
	    p=p->next;
    }

}
int main()
{
    cout<<"欢迎来到图书管理系统!"<<endl;
    cout<<"请输入图书总数："<<endl;
    LinkList L;
    int n;
    cin>>n;
    CreateList_R(L,n);
    cout<<"链表中的数据元素如下："<<endl;
    ShowList(L);
    cout<<"请选择需要的功能："<<endl;
    cout<<"0------------->结束程序"<<endl;
    cout<<"1------------->打印图书"<<endl;
    cout<<"2------------->插入图书"<<endl;
    cout<<"3------------->删除图书"<<endl;
    cout<<"4------------->查找图书"<<endl;
    int option;
    cin>>option;
    while(option)
    {
        if(option == 1)
        {
            ShowList(L);
        }
       else if(option == 2)
        {
            cout<<"输入需要插入图书的位置："<<endl;
            int position;
            cin>>position;
            cout<<"请输入插入图书的ISBN，书名，价格："<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            if(ListInsert(L, position, X)) cout<<"输入成功!"<<endl;
            else cout<<"输入失败!"<<endl;
        }
        else if(option == 3)
        {
            cout<<"输入需要删除图书的位置："<<endl;
            int Num;
            cin>>Num;
            Book e;
            if(ListDelete(L, Num, e)) cout<<"删除成功!删除节点的数据是："<<e<<endl;
            else cout<<"删除失败!"<<endl;
            break;
        }
        else if(option == 4)
        {
            cout<<"输入需要查找图书的ISBN，书名，价格:"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            int position;
            position = LocateElem_L(L,X);
            cout<<"找到了！图书的位置是："<<position<<endl;
            break;
        }
         else
        {
           
            cout<<"发生错误，请再试一次!"<<endl;
        }
        
    }
    cout<<"-----------------------------"<<endl;
    cout<<"感谢使用本系统，欢迎下次再见!"<<endl;
    return 0;
}





























