#include <windows.h> 
#include <stdio.h>
#include <conio.h>
// ПРИМЕР Массивы структур
// программа подсчета числа вхождений каждого ключевого слова языка С
// программа читает из файла и выводит на экран
struct key
{
	char *keyword; // слово кторое ищем
	int keycount; // количество этих слов
};
struct key *keyret(); 
FILE *fopenCon(char *way,char *format);
void comp(struct key *keytab,char *wordF,int kol);
void outStr(struct key *keytab,int kol);
//ввод пути к файлу с консоля
int main (int argc,char *argv[]) {
	FILE *fp;
	struct key *keytab;
	char wordF[100];
    const int kol=6; //количество искомых слов
	keytab=keyret(); //инициализируем структуру
	fp=fopenCon(argv[2],"rt"); // открытие файли переданного из командной строки
	while(fscanf(fp,"%s",wordF)!=EOF) //t-количество прочитанных полей
		comp(keytab,wordF,kol);
	outStr(keytab,kol);
	fclose(fp);
}
struct key *keyret() // функция иницилизирующая структуру возвращает адрес
{ // статическая значит что остается в памяти
	static struct key keytab[]=
	{ 
	{"break",0},
	{"case",0},
	{"char",0},
	{"while",0},
	{"unsigned",0},
	{"FILE",0}
	};
	return keytab;
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
void comp(struct key *keytab,char *wordF,int kol)
{//Функция сравнивающая слова структуры с словом из файла
	int i,j,k;
	for(i=0;i<kol;i++)
	{
		j=0;k=0;
		while((keytab+i)->keyword[j++]==wordF[k++]);
		if((keytab+i)->keyword[--j]=='\0')
			(keytab+i)->keycount++;
	}
}
void outStr(struct key *keytab,int kol)
{// выводит результат на экран
	int i;
	for(i=0;i<kol;i++)
	{
		printf("\n%10s %d",(keytab+i)->keyword,(keytab+i)->keycount);
	}
	puts("\nWait press");
	getch();
}