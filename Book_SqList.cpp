#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXSIZE 10000
#define OK true
#define ERROR false
#define Status bool

//定义构造数据类型
typedef struct
{
    char no[20];
    char name[50];
    float price;
}Book;
//定义顺序表
typedef struct 
{
    Book *book;
    int length;
}SqList;
//初始化顺序表
Status InitList(SqList &L)
{
    L.book = new Book[MAXSIZE];
    if(!L.book) exit(false);
    L.length = 0;
    return OK;
}
//取出顺序表中的图书的信息
Status GetElem(SqList &L, Book &e, int i)
{
    if(i<1 || i>L.length) return false;
    e = L.book[i-1];
    return OK;

}
//插入
Status InsertSqList(SqList &L, int i, Book e)
{
	//是否超出线性表的区间范围
	if (i<1||i>L.length+1)
	{
		return false;
	}
	//当前元素超过线性表长度则无法插入
	if (L.length==MAXSIZE)
	{
		return false;
    }

	//
	for (int j = L.length-1; j>=i-1; j--)
	{
		L.book[j + 1] = L.book[j];
	}
	L.book[i - 1] = e;
	++L.length;
	return 1;
}
//判断是否是同一本书
Status Compire(Book x,Book y)
{
    if(strcmp(x.no, y.no)==0 && strcmp(x.name,y.name)==0 && (x.price==y.price) )
    return OK;
    else
    {
        return false;
    }
}
//查找，并返回图书的位置
int LocateElem(SqList L, Book e)
{
    for(int i = 0;i<=L.length;i++)
    {
        if(Compire(L.book[i],e)) return i+1;//返回找到的数的位置
    }
}
//删除
Status ListDelete(SqList &L, int i)
{
    if(i<1 || i >L.length) return false;
    for(int j = i; j <= L.length-1;j++)
    {
        L.book[j]=L.book[j+1];
        --L.length;
        return true;
    }
}
//打印
void ShowList(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<"ISBN: "<<L.book[i].no<<" "<<"Name: "<<L.book[i].name<<" "<<"Price: "<<L.book[i].price<<endl;
    }
}

int main()
{
    cout<<"欢迎来到图书管理系统!"<<endl;
    SqList L;
    InitList(L);
    cout<<"顺序表初始化成功!"<<endl;
    cout<<"请输入图书的详细信息："<<endl;
    cout<<"-------------------------"<<endl;
    int num;
    cout<<"请输入图书的总数："<<endl;
    cin>>num;
    for(int i = 0;i<num;i++)
    {
        cout<<"请输入ISBN，书名，价格："<<endl;
        Book X;
        cin>>X.no>>X.name>>X.price;
        if(InsertSqList(L, i+1, X))
        {
            cout<<"输入成功!"<<endl;
        }
        else
        {
            cout<<"输入失败!"<<endl;
        }
    }
    cout<<"图书信息输入完成!"<<endl;
    cout<<"---------------------------"<<endl;
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
        if(option==1) 
        {
            ShowList(L);
        }
        else if(option==2)
        {
            cout<<"输入需要插入图书的位置："<<endl;
            int position;
            cin>>position;
            cout<<"请输入插入图书的ISBN，书名，价格："<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;

            if(InsertSqList(L, position, X)) cout<<"输入成功!"<<endl;
            else cout<<"输入失败!"<<endl;
            break;

        }
        else if(option==3)
        {
            cout<<"输入需要删除图书的位置："<<endl;
            int Num;
            cin>>Num;
            if(ListDelete(L, Num)) cout<<"删除成功!"<<endl;
            else cout<<"删除失败!"<<endl;
            break;

        }
        else if(option==4)
        {
            cout<<"输入需要查找图书的ISBN，书名，价格:"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            int position;
            position=LocateElem(L,X);
            cout<<"图书的位置："<<position<<endl;
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