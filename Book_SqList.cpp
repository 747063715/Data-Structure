#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXSIZE 10000
#define OK true
#define ERROR false
#define Status bool

//���幹����������
typedef struct
{
    char no[20];
    char name[50];
    float price;
}Book;
//����˳���
typedef struct 
{
    Book *book;
    int length;
}SqList;
//��ʼ��˳���
Status InitList(SqList &L)
{
    L.book = new Book[MAXSIZE];
    if(!L.book) exit(false);
    L.length = 0;
    return OK;
}
//ȡ��˳����е�ͼ�����Ϣ
Status GetElem(SqList &L, Book &e, int i)
{
    if(i<1 || i>L.length) return false;
    e = L.book[i-1];
    return OK;

}
//����
Status InsertSqList(SqList &L, int i, Book e)
{
	//�Ƿ񳬳����Ա�����䷶Χ
	if (i<1||i>L.length+1)
	{
		return false;
	}
	//��ǰԪ�س������Ա������޷�����
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
//�ж��Ƿ���ͬһ����
Status Compire(Book x,Book y)
{
    if(strcmp(x.no, y.no)==0 && strcmp(x.name,y.name)==0 && (x.price==y.price) )
    return OK;
    else
    {
        return false;
    }
}
//���ң�������ͼ���λ��
int LocateElem(SqList L, Book e)
{
    for(int i = 0;i<=L.length;i++)
    {
        if(Compire(L.book[i],e)) return i+1;//�����ҵ�������λ��
    }
}
//ɾ��
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
//��ӡ
void ShowList(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<"ISBN: "<<L.book[i].no<<" "<<"Name: "<<L.book[i].name<<" "<<"Price: "<<L.book[i].price<<endl;
    }
}

int main()
{
    cout<<"��ӭ����ͼ�����ϵͳ!"<<endl;
    SqList L;
    InitList(L);
    cout<<"˳����ʼ���ɹ�!"<<endl;
    cout<<"������ͼ�����ϸ��Ϣ��"<<endl;
    cout<<"-------------------------"<<endl;
    int num;
    cout<<"������ͼ���������"<<endl;
    cin>>num;
    for(int i = 0;i<num;i++)
    {
        cout<<"������ISBN���������۸�"<<endl;
        Book X;
        cin>>X.no>>X.name>>X.price;
        if(InsertSqList(L, i+1, X))
        {
            cout<<"����ɹ�!"<<endl;
        }
        else
        {
            cout<<"����ʧ��!"<<endl;
        }
    }
    cout<<"ͼ����Ϣ�������!"<<endl;
    cout<<"---------------------------"<<endl;
    ShowList(L);
    cout<<"��ѡ����Ҫ�Ĺ��ܣ�"<<endl;
    cout<<"0------------->��������"<<endl;
    cout<<"1------------->��ӡͼ��"<<endl;
    cout<<"2------------->����ͼ��"<<endl;
    cout<<"3------------->ɾ��ͼ��"<<endl;
    cout<<"4------------->����ͼ��"<<endl;
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
            cout<<"������Ҫ����ͼ���λ�ã�"<<endl;
            int position;
            cin>>position;
            cout<<"���������ͼ���ISBN���������۸�"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;

            if(InsertSqList(L, position, X)) cout<<"����ɹ�!"<<endl;
            else cout<<"����ʧ��!"<<endl;
            break;

        }
        else if(option==3)
        {
            cout<<"������Ҫɾ��ͼ���λ�ã�"<<endl;
            int Num;
            cin>>Num;
            if(ListDelete(L, Num)) cout<<"ɾ���ɹ�!"<<endl;
            else cout<<"ɾ��ʧ��!"<<endl;
            break;

        }
        else if(option==4)
        {
            cout<<"������Ҫ����ͼ���ISBN���������۸�:"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            int position;
            position=LocateElem(L,X);
            cout<<"ͼ���λ�ã�"<<position<<endl;
            break;
        }
        else
        {
           
            cout<<"��������������һ��!"<<endl;
        }
    }
    cout<<"-----------------------------"<<endl;
    cout<<"��лʹ�ñ�ϵͳ����ӭ�´��ټ�!"<<endl;
    return 0;
}