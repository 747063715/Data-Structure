#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define OK true
#define ERROR false
#define Status bool
//����ṹ����������
typedef struct
{
    char no[20];
    char name[50];
    float price;
}Book;
//����һ��������
typedef struct LNode
{
    Book data;
    struct LNode *next;

}LNode, *LinkList;
//����>>�����
istream & operator>>(istream &in, Book &A){
    in >> A.no >> A.name >>A.price;
    return in;
}
//����������
void CreateList_R(LinkList &L, int n)
{
    L = new LNode;
    L->next=NULL;
    LinkList r=L;
    for(int i = 0;i<n;i++)
    {
        cout<<"������ͼ����Ϣ��"<<endl;
        LinkList p = new LNode;
        cin>>p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}
//ȡֵ����������L�е�i������Ԫ�ص�ֵ
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
//����!=�����
bool operator!=(Book a, Book b)
{
    if(a.no==b.no && a.name==b.name && a.price==b.price) return true;
    else return false;

}
//���Ҳ���,���ظ����ݵ�λ�����
int LocateElem_L(LinkList L, Book e)
{
    LinkList p = L->next;
    int j = 1;
    while(p && p->data!=e)
    {
        p = p->next;
        ++j;
    }
    if(p) return j; //����λ�õ����
    else return 0;
} 
//�������
Status ListInsert(LinkList &L, int i, Book e)
{
    LinkList p = L;
    int j = 0;
    while(p && j<i-1)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>i-1) return false;   //�ҵ���i-1������Ԫ��
    LinkList s = new LNode;     //�����µĽ��
    s->next = p->next;
    p->next = s;
    return true;
}
//ɾ������,������ɾ����������
Status ListDelete(LinkList &L, int i,Book e)
{
    LinkList p = L;
    int j = 0;
    while((p->next) && (j<i-1))   //�ҵ���i-1������Ԫ��
    {
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i-1) return false;
    LinkList q = p->next;
    p->next = q->next;
    e = q->data;             //�洢ɾ����������
    delete q;
    return 0;            
}
//��������ı�
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
//����<<
ostream & operator<<(ostream &out, Book &A)
{
    out << A.no << A.name <<A.price;
    return out;
}
//��ӡ
void ShowList(LinkList &L)
{
    LinkList p;
	p=L->next;
    cout<<"ISBN"<<" "<<"����"<<" "<<"�۸�"<<endl;
    while(p)
    {
        cout<<p->data.no<<" "<<p->data.name<<" "<<p->data.price<<endl;
	    p=p->next;
    }

}
int main()
{
    cout<<"��ӭ����ͼ�����ϵͳ!"<<endl;
    cout<<"������ͼ��������"<<endl;
    LinkList L;
    int n;
    cin>>n;
    CreateList_R(L,n);
    cout<<"�����е�����Ԫ�����£�"<<endl;
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
        if(option == 1)
        {
            ShowList(L);
        }
       else if(option == 2)
        {
            cout<<"������Ҫ����ͼ���λ�ã�"<<endl;
            int position;
            cin>>position;
            cout<<"���������ͼ���ISBN���������۸�"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            if(ListInsert(L, position, X)) cout<<"����ɹ�!"<<endl;
            else cout<<"����ʧ��!"<<endl;
        }
        else if(option == 3)
        {
            cout<<"������Ҫɾ��ͼ���λ�ã�"<<endl;
            int Num;
            cin>>Num;
            Book e;
            if(ListDelete(L, Num, e)) cout<<"ɾ���ɹ�!ɾ���ڵ�������ǣ�"<<e<<endl;
            else cout<<"ɾ��ʧ��!"<<endl;
            break;
        }
        else if(option == 4)
        {
            cout<<"������Ҫ����ͼ���ISBN���������۸�:"<<endl;
            Book X;
            cin>>X.no;
            cin>>X.name;
            cin>>X.price;
            int position;
            position = LocateElem_L(L,X);
            cout<<"�ҵ��ˣ�ͼ���λ���ǣ�"<<position<<endl;
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





























