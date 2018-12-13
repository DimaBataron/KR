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
struct nameT *returnS();
int kolS(struct key *keytab);
struct BinTree *func(struct nameT *Z,FILE *P, int kol);


void main()
{
	FILE *fp;
	struct nameT *KeyWord;
	int kol;
	fp = fopenCon("C:\\1.txt","rt");
	fclose(fp);
	KeyWord=returnS();
	kol = kolS(KeyWord);
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
	char z[100],*c,c1;
	int i,k,fl;
	while(fscanf(P,"%s",z)!=EOF)
	{
		for(i=0;i<kol;i++)
		{
			if(strcmp(z,(Z+i)->nameT)==0) // если нашли название типа
			{
				do
				{
					fl=0;
					while(fgetc(P)==" "); // после типа через пробелы всегда следуют имена;
					k=0;
					z[k++]=fgetc(P);
					// записываем имя по буквам
					while(z[k]!=" " && z[k]!="," && z[k]!=";") z[k++]=fgetc(P); 
					if(z[k] ==",") fl=1; // признак того что далее идут так-же имена;
					z[k]="\0";
					c= (char *) malloc(sizeof(char)*(k+1)); // памть для слова
					strcpy(c,z);
				//здесь функция добавления слова в дерево
				}
				while(fl==1);// если была запятая то повторить
			}
		}
	}
}

