#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
/* Упражнение 6-4 Напишите программу которая читает "C" -программу и 
печатает в алфавитном порядке каждую группу имен переменных, 
которые совпадают в первых семи символах, но отличаются 
где-то дальше
*/
FILE *fopenCon(char *way,char *format);
struct nameT {
	char *nameT;
};
struct BinTree
{ //структура для хранения элементов дерева
	char *wordP;
	int col;
	struct BinTree *left;
	struct BinTree *rigt;
};
struct BinTree *funcTree(struct BinTree *st,char *w); 
struct BinTree *func(struct nameT *Z,FILE *P, int kol);
struct nameT *returnS();
int kolS(struct key *keytab);
int funcP(char *wordP, char *w);
void treeprint(struct BinTree *P);


void main()
{
	FILE *fp;
	struct nameT *KeyWord;
	struct BinTree *ver;
	int kol;
	fp = fopenCon("C:\\1.txt","rt");
	KeyWord=returnS();
	kol = kolS(KeyWord);
	ver = func(KeyWord,fp,kol);
	treeprint(ver);
	fclose(fp);
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
struct nameT *returnS()
{ // Содержит список имен типов после которых следуют имена переменных
	static struct nameT mas[] =
	{
		{"int"},
		{"char"},
		{"short"},
		{"long"},
		{"double"},
		{NULL}
	};
	return mas;
}
int kolS(struct nameT *keytab)
{//вычисляет количество слов в структуре
	int i=0;
	while((keytab+i)->nameT !=NULL) i++;
	return i;
}
struct BinTree *func(struct nameT *Z,FILE *P, int kol)
{ //Читает из файла слова ищет имена. Возвращает указатель на корень бинарного дерева
	char z[100],*c;
	int i,k,fl;
	struct BinTree *ver =NULL;
	while((fscanf(P,"%s",z))!=EOF)
	{
		for(i=0;i<kol;i++)
		{
			if(strcmp(z,(Z+i)->nameT)==0) // если нашли название типа
			{
				do
				{
					fl=0;
					fscanf(P,"%s",z); // слудеющее слово после типа всегда имя.
					k=0;
					while(z[k]!=',' && z[k]!='\0' && z[k]!=';') k++; 
					if(z[k] ==',') // признак того что далее идут так-же имена;
						{	fl=1; 
							z[k]='\0';
						}
					if(z[k]=';') z[k]='\0';
					c= (char *) malloc(sizeof(char)*(k+1)); // памть для слова
					strcpy(c,z);
					//добавление поученого имени в дерево;
					ver = funcTree(ver,c);
				}
				while(fl==1);// если была запятая то повторить
			}
		}
	}
	return ver;
}
struct BinTree *funcTree(struct BinTree *st,char *w) // нельзя передавать указатель на пустую структуру
{
	int cound;
	if(st == NULL)
	{
		st = (struct BinTree *) malloc (sizeof(struct BinTree));
		st->wordP=w;
		st->left=NULL;
		st->rigt=NULL;
		st->col = 0;
	}
	else
	{
		if((cound=funcP(st->wordP,w))==0) // слова равны
		{
			(st->col)++;
		}
		else 
		{
			if(cound<0) // первая отличная буква первого слова меньше буквы второго
			{
				st->rigt=funcTree(st->rigt,w);
			}
			else st->left=funcTree(st->left,w); // больше
		}
	}
	return st;
}
int funcP(char *wordP, char *w)
{
	int i,fl,z;
	for(i=0,fl=1;i<7;i++)
	{
		//Почему тут не сдвигается
		if(*(wordP+i)!=*(w+i) || (wordP[i]=='\0' || w[i]=='\0'))
		{
			fl=0;
			break;
		}
	}
	if( fl==0 && wordP[i]=='\0' && wordP[i]=='\0') fl=1;
	if (fl==1) return 0;
	else return wordP[i]-w[i]; // >0 последняя буква первого слова старше;
}
void treeprint(struct BinTree *P)
{
	if(P!=NULL)
	{
		treeprint(P->left);
		printf("%4d%s\n",P->col,P->wordP);
		treeprint(P->rigt);
	}
}



