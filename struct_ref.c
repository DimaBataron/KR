#include <windows.h> // для работы с файлами
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
// ПРИМЕР структуры ссылающиеся на себя
//реккурентно формирует дерево бинарное дерево частотности слов
char *strsave(char *s);
FILE *fopenCon(char *way,char *format);
struct tnode
{
	char *wordP; // слово
	int count; //количество таких слов
	struct tnode *left; // указатели на структуры
	struct tnode *rigt;
};
struct tnode *talloc();
struct tnode *tree(struct tnode *P, char *w);
struct tnode *treeprint(struct tnode *P);
void main()
{
	FILE *fp;
	char *w, c[100];
	struct tnode *root;
	fp=fopenCon("C:\\1.txt","rt");
	root=NULL;
	while((fscanf(fp,"%s",c))!=EOF)
	{
		root=tree(root,c);
		treeprint(root);
	}
	fclose(fp);
	getch();
}
char *strsave(char *s)
{ //копирует строку в другую область памяти т.к. эта будет затерта
	char *st;
	st= (char *) malloc(sizeof(strlen(s))+1); // выделяем память для указателя
	strcpy(st,s);// копирование строки в выделенную память
	return st; // возвращает указатель
}
struct tnode *talloc()
{ // выделение памяти для структуры
	return ((struct tnode *) malloc(sizeof(struct tnode)));
}
struct tnode *tree(struct tnode *P, char *w)
{//функция формирующая бинарное дерево из слов w
	int cond;
	if(P==NULL) //новое слово
	{
		P=talloc(); // выделяем память для новой структуры и сохраням ее адрес
		P->wordP=strsave(w); //выделяем память, копируем слово и сохраняем адрес
		P->count=1;
		P->left = P->rigt = NULL; // слово новое указатели на сыновей пусты
	}
	else 
	{
		if((cond=strcmp(w,P->wordP))==0) //если строки равны
			P->count++;
		else
			{
				if(cond<0) //если первая строка менше второй
					P->left=tree(P->left,w);
				else P->rigt=tree(P->rigt,w);
			}
	}
	return(P);
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
struct tnode *treeprint(struct tnode *P)
{
	if(P!=NULL)
	{
		treeprint(P->left);
		printf("%4d%s\n",P->count,P->wordP);
		treeprint(P->rigt);
	}
}