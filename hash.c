#include <windows.h> // для работы с файлами
#include <stdlib.h> 
#include <stdio.h>
#include <conio.h>
#include <string.h> // для работы со строками
/* Поиск в таблице с использованием простой хэш функции.
Эта программа типичный представитель подпрограмм упраления
символьными таблицами макропроцессора или компилятора. */
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
	struct nlist *np;
	int hashval;
	if((np = lookup(Name)) == NULL) // имя не найдено
	{
		np =(struct nlist *) malloc(sizeof (*np));
		if(np==NULL) return NULL;
		if((np->Name = strsave(Name))==NULL) return NULL;
		hashval = hash(np->Name); // ключ хэша
		np->next = hashtab[hashval]; // есть ли тут ошибка?
		hashtab[hashval]=np; // запись элемента в хэш таблицу
	}
	else 
	{
		free(np->def);
		if((np->def = strsave(def))==NULL) return NULL;
		return np;
	}
}