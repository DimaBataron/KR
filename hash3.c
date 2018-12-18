#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
/* Упражнение 6-8 Разработайте простую, основанную на функциях
этого раздела, версию препроцессора для обработки конструкций 
#define, пригодную для использования с "C" программами 
ВНИМАНИЕ!! имя макросса должно быть отделено пробелами
т.к. у символа 'я' код -1 не принимает русские буквы.
Лень писать функции для обработки русских строк
*/
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
FILE *macros(FILE *fp);
void main()
{
	int i=0;
	FILE *fp;
	fp=fopenCon("C:\\1.txt","rt");
	Fread(fp); // заполнение хэш таблицы из файла
	PrintHashtabl(); //печать хэш таблицы
	fp=macros(fp);
	fclose(fp);
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
FILE *macros(FILE *fp)
{
	FILE *fp1;
	char w[100],*c,sim;
	struct nlist *np;
	fp1=fopenCon("C:\\2.txt","wt");
	rewind(fp); // устанавливает указатель позиции в файле в начало
	while(fscanf(fp,"%s",w)!=EOF)
	{
		if(strcmp(w,"#define") == 0)
		{
			fprintf(fp1,"%s",w);
			fscanf(fp,"%s",w);
			fprintf(fp1," %s",w);
			fscanf(fp,"%s",w);
			fputc(' ',fp1);
		}

		if((np=lookup(w))==NULL) // такой макрос не опрделен
			fprintf(fp1,"%s",w);
		else
			fprintf(fp1,"%s",np->def); // есть записываем его значение
		if((sim=fgetc(fp))=='\n')
			fprintf(fp1,"%c",sim);
		else fputc(' ',fp1);
	}
	fputc('\0',fp1);
	fclose(fp);
	return fp1;
}