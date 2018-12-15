#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
//Символ "Я" имеет тот -же код как и EOF
/* Упражнение 6-5 Напишите прогрмму выдачи перекрестных ссылок,
т.е. программу которая печатает список всех слов документа и для каждого
из этих слов номеров строк, в ктороые это слово входитж
*/

struct BinTree 
{
	char *w;
	struct List *mas;
	struct BinTree *left;
	struct BinTree *right;
};
struct List
{
	int m;
	struct List *next;
};
struct BinTree *funcTree(struct BinTree *ver,char *w,int n);
struct List *funcList(struct List *lis, int n);
struct BinTree *InWord(FILE *fp);
FILE *fopenCon(char *way,char *format);
struct BinTree *treeprint(struct BinTree *ver);
void main()
{
	FILE *fp;
	struct BinTree *ver;
	SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
	fp = fopenCon("C:\\1.txt","rt");
	ver = InWord(fp);
	treeprint(ver);
	fclose(fp);
	getch();
}


struct BinTree *funcTree(struct BinTree *ver,char *w,int n)
{ // функуия формирует бинарное дерево слов
	int num;
	if(ver==NULL) 
	{
		ver = (struct BinTree *) malloc(sizeof(struct BinTree));
		ver->w = w;
		ver->left = NULL;
		ver->right =NULL;
		ver->mas = NULL;
		ver->mas = funcList(ver->mas,n);
	}
	else
	{
		if((num=strcmp(ver->w,w)) == 0) 
			ver->mas = funcList(ver->mas,n);
		else 
		{
			if(num>0) ver->left =  funcTree(ver->left,w,n);
			else ver->right = funcTree(ver->right,w,n);
		}
	}
	return ver;
}
struct List *funcList(struct List *lis, int n)
{ // функция записывает в дерево номера строк где слово встречается
	if(lis == NULL)
	{
		lis = (struct List *) malloc(sizeof(struct List));
		lis->m = n;
		lis->next =NULL;
	}
	else lis->next=funcList(lis->next,n);
	return lis;
}
struct BinTree *InWord(FILE *fp)
{ // вводит слова из файла принимает указатль на открытый файл
	char c,w[100],*slovo;
	int k=0; // номер строки
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
			tree = funcTree(tree,slovo,k);
		}
		if (c == '\n')
		{
			k++;
		}

	}
	return tree; // возвращает указатель на вершину дерева
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
struct BinTree *treeprint(struct BinTree *ver)
{ // выводит дерево
	if( ver !=NULL)
	{
		treeprint(ver->left);
		printf("%s ", ver->w);
		while(ver->mas!= NULL)
		{
			printf("%d ", ver->mas->m);
			ver->mas = ver->mas->next;
		}
		printf("\n");
		treeprint(ver->right);
	}
}
