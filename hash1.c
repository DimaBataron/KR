#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
/* Упражнение 6-7 Напишите процедуру, которая будет удалять 
имя и определение из таблицы управляемой функциями LOOKUP и INSTALL*/
#define hashsize 100
struct nlist
{
	char *Name; // имя
	char *def;  // заменяющий текст
	struct nlist *next;
};
static struct nlist *hashtab[hashsize]; //(xэш) таблица указателей 

struct nlist *lookup(char *S);
FILE *fopenCon(char *way,char *format);
int hash( char *S);
struct nlist *install(char *Name, char *def);
char *strsave(char *s);
void  Fread(FILE *fp);
void PrintHashtabl();
void DelHashNotation(char *S);

void main()
{
	int i=0;
	FILE *fp;
	fp=fopenCon("C:\\1.txt","rt");
	Fread(fp);
	fclose(fp);
	PrintHashtabl();
	DelHashNotation("hashsize"); // удаляет запись с именем hashsize из хэш таблицы
	PrintHashtabl();
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
char *strsave(char *s)
{ //копирует строку в другую область памяти т.к. эта будет затерта
	char *st;
	st= (char *) malloc(sizeof(strlen(s))+1); // выделяем память для указателя
	strcpy(st,s);// копирование строки в выделенную память
	return st; // возвращает указатель
}
int hash( char *S)
{ // возвращает значение функции хеширования
	int hashval;
	for(hashval = 0; *S!='\0';)
		hashval += *S++; // суммирует все коды символов
	return(hashval % hashsize); 
	// возвращает остаток от деления суммы кодов на размер массива
}
struct nlist *lookup(char *S)
{ // функция ищет данный элемент.
	// Возвращает указатель на элемент либо NULL
	struct nlist *np;
	for(np=hashtab[hash(S)];np!=NULL;np=np->next)
		if(strcmp(S,np->Name)==0) return(np);
	return(NULL);
}
struct nlist *install(char *Name, char *def)
{// использует функцию lookup чтобы определить не
	// присутствует ли уже вводимое в данный момент имя
	// если нет создается новый элемент
	struct nlist *np,*p;
	int hashval;
	if((np = lookup(Name)) == NULL) // имя не найдено
	{
		np =(struct nlist *) malloc(sizeof (*np));
		if(np==NULL) return NULL;
		if((np->Name = strsave(Name))==NULL) return NULL; // запись имени
		if((np->def = strsave(def))==NULL) return NULL; // и значения
		np->next= NULL;
		hashval = hash(np->Name); // ключ хэша
		if(hashtab[hashval]==NULL) // если в эту ячейку таблицы
		{ // ничего не записано
			hashtab[hashval]=np; //делаем первую запись
		}
		else
		{
			for(p=hashtab[hashval];p->next!=NULL;p=p->next);
			p->next=np; // находим пустое место и записываем туда
		}
	}
	else 
	{ // если такое имя найдено перезаписываем значение
		free(np->def);
		if((np->def = strsave(def))==NULL) return NULL;
	}
	return np;
}
void  Fread(FILE *fp)
{// функция записи определений в хэш таблицу
	char *Name, slow[100], *def;
	while(fscanf(fp,"%s",slow)!=EOF)
	{
		if(strcmp(slow,"#define")==0) // "" - cтроковая константа ''= символьная
		{
			fscanf(fp,"%s",slow);
			Name = strsave(slow); // после define имя
			fscanf(fp,"%s",slow); // после имени значение
			def = strsave(slow);
			if(install(Name,def)==NULL) puts("Error write");
			// записывает полученные значения в таблицу
		}
	}
}
void PrintHashtabl()
{ // вывод хэш таблицы на экран
	int i=0;
	struct nlist *p;
	while(i<hashsize)
	{
		if(hashtab[i]!=NULL)
		{
			printf("Write %d:",i);
			for(p=hashtab[i];p!=NULL;p=p->next)
			{
				printf("Name:%8s Def:%5s--->",p->Name,p->def);
			}
			printf("\n");
		}
		i++;
	}
}
void DelHashNotation(char *S)
{//функция удаляет запись из хэша
	struct nlist *np,*prev;
	int fl=0;
	prev = NULL;
	for(np=hashtab[hash(S)];np!=NULL;np=np->next)
	{
		if(strcmp(S,np->Name)==0) // нашли такую запись
		{
			fl=1;
			if((np->next) == NULL) //эта запись последняя в списке
			{
				free(np);
				if(prev!=NULL)
					{
						prev->next=NULL;
						break;
					}
				else
					{
						hashtab[hash(S)]=NULL; //запись единственная 
						break;
					}
			}
			else // эта запиь не последняя
				{
					if(prev!=NULL) // есть ли перед ней запись
						{ // есть
							prev->next=np->next;
							free(np);
							break;
						}
					else // нет
						{
							hashtab[hash(S)]=np->next;
							free(np);
							break;
						}
				}
		}
		prev=np;
	}
	if(fl==1) printf("Delite %s\n",S);
	else printf("Not found %s\n",S);
}