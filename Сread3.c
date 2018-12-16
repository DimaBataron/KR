#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
/* Упражнение 6-6 Напишите прогрмму, которая печатает слова из
своего файла ввода расположенные в порядке убывания частоты их
появления.Перед каждым словом напечатайте число его повторений
*/
// работает не слюбыми данными
struct BinTree 
{
	int count;
	char *w;
	struct BinTree *left;
	struct BinTree *right;
};
struct list
{
	int count;
	char *w;
	struct list *next;
};

struct BinTree *Tree(struct BinTree *P,char *w);
struct list *ScanTree(struct BinTree *P, struct list *l);
FILE *fopenCon(char *way,char *format);
struct BinTree *InFile(FILE *fp);
void SortingList(struct list *l);
void PrintList(struct list *l);

void main()
{
	FILE *fp;
	struct list *l =NULL;
	struct BinTree *P = NULL;
	SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
	fp=fopenCon("C:\\1.txt","rt");
	P=InFile(fp);
	l=ScanTree(P,l);
	SortingList(l);
	PrintList(l);
	getch();
}
FILE *fopenCon(char *way,char *format)
{// Функция открывающая заданный файл в случае ошибки выводит сообщение
	FILE *p;
	int Err;
	if((Err=fopen_s(&p,way,format))!=0)
	{
		printf("Error open file\n press key");
		getch();
		exit(0);
	}
	return p;
}
struct BinTree *InFile(FILE *fp)
{ // вводит слова из файла принимает указатль на открытый файл
	char c,w[100],*slovo;
	int i=0; // буква в слове;
	struct BinTree *tree = NULL; // указатель на вершину дерева
	
	while((c = fgetc(fp))!= EOF) // считываем слова побуквенно
	{
		while (c == ' ') c = fgetc(fp);
		i=0;
		while (c!= ' ' && c!='\n' && c!= EOF && c!='\t' && c!=',' && c!=';')
			{
				w[i++] = c;
				c = fgetc(fp);
			}
		if(i!=0)
		{
			w[i]='\0';
			slovo = (char *) malloc((sizeof(char)*(i+1)));
			strcpy(slovo,w);
			tree = Tree(tree,slovo);
		}
	}
	return tree; // возвращает указатель на вершину дерева
}
struct BinTree *Tree(struct BinTree *P,char *w)
{
	int comp;
	if (P==NULL)
	{
		P= (struct BinTree *) malloc(sizeof(struct BinTree));
		P->w=w;
		P->count=0;
		P->left=NULL;
		P->right=NULL;
	}
	else 
	{
		if((comp=strcmp(P->w,w))==0) P->count++;
		else 
		{
			if(comp<0) P->right=Tree(P->right,w);
			else P->left=Tree(P->left,w);
		}
	}
	return P;
}
struct list *ScanTree(struct BinTree *P, struct list *l)
{ 

	struct list *poin;
	if(P!=NULL)
	{	
		if(l!=NULL)
		{
			poin =(struct list *) malloc(sizeof(struct list));
			l->next=poin;
			poin->next=NULL;
		}
		else
			{
				l = (struct list *) malloc(sizeof(struct list));
				l->next=NULL;
				poin = l;
			}
		poin= ScanTree(P->left,poin);
		poin->w=P->w;
		poin->count=P->count;
		poin= ScanTree(P->right,poin);
	}
	return l;
}
void SortingList(struct list *l)
{
	struct list *p;
	int buf;
	char *Wbuf;
	int k=0,i; //количество проходов
	p=l;
	while(p->next!=NULL)
	{
		if(p->count < p->next->count)
		{ // Обмен местами информационные части
			buf=p->next->count;
			p->next->count=p->count;
			p->count=buf;
			Wbuf=p->next->w;
			p->next->w= p->w;
			p->w=Wbuf;
		}
		p=p->next;
		k++;
	}
	for(i=0;i<k;i++)
	{
			while(p->next!=NULL)
			{
				if(p->count < p->next->count)
				{ // Обмен местами информационные части
					buf=p->next->count;
					p->next->count=p->count;
					p->count=buf;
					Wbuf=p->next->w;
					p->next->w= p->w;
					p->w=Wbuf;
				}
			p=p->next;
			}
	}
}
void PrintList(struct list *l)
{
   struct list *p;
   p=l;
   while(p!=NULL)
   {
	   printf("%4d %s\n",p->count,p->w);
	   p=p->next;
   }

}
