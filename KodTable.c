#include <windows.h> 
#include <stdio.h>
#include <conio.h>
// Программа для вывода символов и их кодов в текстовый файл и на экран
FILE *fopenCon(char *way,char *format);
void main()
{
	int i,j;
	char sym;
	FILE *fp;
	//SetConsoleOutputCP(1251);
    //SetConsoleCP(1251);
	fp=fopenCon("C:\\KodTable.txt","wt");//создаем файл для записи
	for(i=0;i<16;i++)
	{
		sym = i<<4; // битовый сдвиг влево
		for(j=0;j<16;j++)
		{
			sym +=j;
			{
			fprintf(fp,"%c %x%x  ",sym,i,j);
			fprintf(stdout,"%c %x%x  ",sym,i,j);
			}
		}
		fprintf(fp,"\n");
		fprintf(stdout,"\n");
	}
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