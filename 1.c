//#include <windows.h> 
#include <stdio.h>
#include <conio.h>
// ������
/* DAY_OF_YEAR �������������� ��� ������ � ���� ���� � �������� */
int DAY_OF_YEAR(int year, int month, int day);
//���������� 5-6 ���������� ������� DAY_OF_YEAR ��������� ���������
void DAY_OF_YEARP(int *year, int *mounth, int *day,int *DAY_TAB);
// ����� ���� � ���������� � ������������ ����
    int DAY_TAB[2][13]=
	{ {0,31,28,31,30,31,30,31,31,30,31,30,31},
	  {0,31,29,31,30,31,30,31,31,30,31,30,31} };
void main () {
	int year,month,day, *p; // *p-��������� �� ������ DAY_TAB
	puts("d.m.y");
	scanf("%d%d%d",&day,&month,&year);
	printf("%d %d %d",day,month,year);
	day=DAY_OF_YEAR(year,month,day);
	printf("\n%d",day);
	getch();
	// ���� � �������������� ����������
	puts("\nd.m.y");
	scanf("%d%d%d",&day,&month,&year);
	printf("%d %d %d",day,month,year);
	p=&DAY_TAB[0][0]; // ��������� ������
	DAY_OF_YEARP(&year,&month,&day,p);
	printf("\n%d",day);
	getch();
}
int DAY_OF_YEAR(int year, int month, int day)
{
	int i,leap;
	leap = year%4==0 && year%100!=0 && year%400==0;
	for(i=1;i<month;i++)
		day+=DAY_TAB[leap][i];
	return day;
}
void DAY_OF_YEARP(int *year, int *month, int *day,int *DAY_TAB)
{ // ���� � �����������
	int i,leap;
	leap = *year%4==0 && *year%100!=0 && *year%400==0;
	for(i=1;i<*month;i++)
		*day+=*(DAY_TAB+leap*13 +i);
}