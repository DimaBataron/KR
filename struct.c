//#include <windows.h> 
#include <stdio.h>
#include <conio.h>
// ПРИМЕР Структуры и функции
struct date 
{
	int day;
	int month;
	int year;
	int yearday;
	char mon_name[4];
};
/* DAY_OF_YEAR Преобразование дня месяца в день года и наоборот */
void DAY_OF_YEAR(struct date *pd); // в функию передаеться указатель на структуру
void scan_date(struct date *pd); // ввод даты

void main () {
	struct date day;
	scan_date(&day);
	DAY_OF_YEAR(&day);
	getch();
}

void DAY_OF_YEAR(struct date *pd)
{
	int DAY_TAB[2][13]=
	{ {0,31,28,31,30,31,30,31,31,30,31,30,31},
	  {0,31,29,31,30,31,30,31,31,30,31,30,31} }; //дни в высокосном году и обычном
	int i,leap;
	leap = pd->year%4==0 && pd->year%100!=0 && pd->year%400==0;
	for(i=1;i<pd->month;i++)
		pd->yearday+=DAY_TAB[leap][i];
	printf("\nYearday = %d",pd->yearday);
}

void scan_date(struct date *pd)
{ // запись в структуру 
   // По
	puts("d.m.y");
	scanf("%d%d%d",&(pd->day),&(pd->month),&(pd->year));
	printf("%d %d %d",pd->day,pd->month,pd->year);
	pd->yearday=0;
}