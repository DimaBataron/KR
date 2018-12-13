#include<stdio.h> //Модуль стандартного ввода-вывода
#include<conio.h> /*Модуль функций расширения ввода-вывода*/
#include<windows.h>
#include<math.h> //Подключаем библиотеку математических функций

	FILE *fp, *fp1, *fp2;

	
void main()
{ 
	int i=0,z=0,n=0; // переменная индекс сдвига в slowsl
	int glasn,per=0; // количество гласных в слове per были ли уже добавления
	int mznak=1;
	int nslow; // начало слова
	int pk=1; // искали ли на этом проходе конец слова
	char slow[40],slowsl[40]; // слово получаемое из файла slowsl слово разделенное по слогам которое нужно вывести в файл
	int slows[40];				// схема букв в словах
	int x1, x2, x3, x4, x5, x6, x7,x8, kbukv,k,f=0, Sglasn=0,fl=0;    // kbukv сколько букв в слове осталось
	fp=fopen("E:\\A.txt","rt");  // файл с исходными словами
	fp1=fopen("E:\\B.txt","wt"); // схема слова;
	fp2=fopen("E:\\C.txt","wt"); // слово по слогам
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//проверить везде ли правильно уменьшаеться колияество гласных. Если больше нет запись и braik 
	for(i=0;i<40;i++)  // очищаю память слова 
	{
		slowsl[i]='\0';
	}
	while((fscanf(fp,"%s",slow))!=EOF) // считывает слова пока не конец файла
		{
			i=0;glasn=0; z=0; n=0; Sglasn=0; kbukv=0; per=0; mznak=1;
			f=0; x1=-1; x2=-1; x3=-1; x4=-1; x5=-1; x6=-1; x7=-1; k=0; fl=0;
			while(slow[i]!='\0')   // цикл формирования схемы слова
			{
				switch(slow[i])
				{
				case 'а' : glasn++; slows[z]=1; break;
				case 'о' : glasn++; slows[z]=1; break;
				case 'и' : glasn++; slows[z]=1; break;
				case 'ы' : glasn++; slows[z]=1; break;
				case 'у' : glasn++; slows[z]=1; break;
				case 'э' : glasn++; slows[z]=1; break;
				case 'е' : glasn++; slows[z]=1; break;
				case 'ю' : glasn++; slows[z]=1; break;
				case 'ё' : glasn++; slows[z]=1; break;
				case 'я' : glasn++; slows[z]=1; break;
				
				case 'й' : slows[z]=2; break;
				case 'м' : slows[z]=2; break;
				case 'н' : slows[z]=2; break;
				case 'л' : slows[z]=2; break;
				case 'р' : slows[z]=2; break;

				case 'п' : slows[z]=3; break;
				case 'б' : slows[z]=3; break;
				case 'ф' : slows[z]=3; break;
				case 'в' : slows[z]=3; break;
				case 'т' : slows[z]=3; break;
				case 'д' : slows[z]=3; break;
				case 'с' : slows[z]=3; break;
				case 'з' : slows[z]=3; break;
				case 'ц' : slows[z]=3; break;
				case 'ч' : slows[z]=3; break;
				case 'ш' : slows[z]=3; break;
				case 'щ' : slows[z]=3; break;
				case 'ж' : slows[z]=3; break;
				case 'г' : slows[z]=3; break;
				case 'х' : slows[z]=3; break;
				case 'к' : slows[z]=3; break;
				case 'ь' : slows[z]=4; break;
				case '-' : z--;k=i; while(slow[i]!='\0') { slow[i]=slow[i+1]; i++; } i=k-1; break;
				default : slows[z]=4;  //твердый знак;
				}
				fprintf(fp1, "%d", slows[z]); // запись схемы в файл
				z++;
				i++;
			}
			fprintf(fp1, "\n", slows[z]);
			slow[i]='\n';
			slow[i+1]='\0';
			i=0;
	kbukv=z+1;  // количество букв в слове -- далее количество оставшихся букв
	nslow=1;
//	slows[z]<0 ;  признак окончания строки схемы слова
	z=0;
	if(glasn>1)         // если больше одной гласной
	{
	while(slows[z]>-1)  // цикл пока не конец слова
	{
		pk=0;
		if(nslow==1)
		{
			x1=slows[z+0];
			x2=slows[z+1];
			x3=slows[z+2];
			x4=slows[z+3];
			x5=slows[z+4];
			x6=slows[z+5];
			x7=slows[z+6];
			x8=slows[z+7];
			if(((x1==3 && x2==1 && x3==2 && x4==3 && x5==2) ||
				(x1==3 && x2==2 && x3==1 && x4==2 && x5==3) ||
				 (x1==3 && x2==1 && x3==2 && x4==3 && x5==3)) && x6!=1)//31232 32123 31233 санкт
			{
				for(i=0;i<5;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
			}
			if(nslow && (x1==3 && x2==3 && x3==2 && x4==1) && (x5==2 || x5==3) && x6!=1) //33213 33212
			{
				for(i=0;i<5;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
			}
			if(nslow && x1==3 && x2==3 && x3==1 && x4==3 && x5!=1) // 3313 пред чрез
			{
				for(i=0;i<4;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				i=z;  // ищем скопление согласных перед мягким знаком
				while(slows[i]>0 && slows[i]!=4 && (slows[i]==2 || slows[i]==3)) i++;
				if(slows[i]==4)
				{
					k=i-z+1;
					for(i=0;i<k;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				}
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
			}
			if(nslow && slow[z]=='й' && slow[z+1]=='о' && slow[z+2]=='р' && slow[z+3]=='к')
			{
				{
				for(i=0;i<4;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
				if(x5==1 && x6==2 && x7==3 && x8!=1) //2123-123- йорк-ант
				{
					k=z;
					for(i=z;i<k+3;i++,n++,kbukv--,z++) slowsl[n]=slow[z]; 
					slowsl[n++]='-';
					glasn--;
					pk=1;
				}
			}
			}
			if(nslow && x1==2 && x2==1 && x3==2 && x4==3 && x5!=1) //2123 и не 1
			{
				for(i=0;i<4;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
			}
			if(nslow && (((x1==2 || x1==3) && x2==1 && x3==3) || 
				(x1==1 && x2==2 & x3==3)) &&  x4!=1) //213 313 123
			{
				if(x4==4) for(i=0;i<4;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				else for(i=0;i<3;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
			}
			if(nslow && x1==3 && x2==3 && x3==1 && x4==2 && x5==3 && x6!=1) //33123
			{  
				glasn--;
				if(glasn>1) // слог даже если после него 1 только если а не в конце слова
				{
					for(i=0;i<5;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				if(x6!=4) slowsl[n++]='-';
				else
				{
					slowsl[n++]=slow[z++];
					slowsl[n++]='-';
				}
				fl=1;
				nslow=0;
				glasn--;
				pk=1;
				}
			}
		}
		if(nslow==1)
			{
				if(((x1==3 && x2==1 && x3==3) || (x1==1 && x2==3 && x3==3) ||
					x1==1 && x2==3 && x3==2) && x4!=1) //313 133 132 в начале слова
				{
					for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					slowsl[n++]='-';
					nslow=0;
					fl=1;
					pk=1;
				}
				if(nslow && ((x1==1 && x2==2) || (x1==1 && x2==3)) && x3!=1) //12 13 в начале слова
				{
					if(x3!=4)
						for(i=0;i<2;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					else for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					nslow=0;
					slowsl[n++]='-';
					glasn--;
					fl=1;
					pk=1;
				}
			}

		if(nslow==1)
		{
		// смотрим начало слова 1321 1331 1221 1231
		if(((x1==1 && x2==3 && x3==2 && x4==1) || (x1==1 && x2==3 && x3==3 && x4==1) || 
		   (x1==1 && x2==2 && x3==2 && x4==1) || (x1==1 && x2==2 && x3==3 && x4==1)))
			{
			 for(i=0;i<2;i++,z++,n++,kbukv--)  slowsl[n]=slow[z];
				fl=1;
				nslow=0;
				glasn--;
				per=0;
		   /* i=z; 	fl=0; while(slows[i]==3 || slows[i]==2) i++;  //скопление согласных с мягким хнаком
		   if(slows[i]==4) 
		   {
			   k=i-z+1;
			   for(i=0;i<k;i++,z++,n++,kbukv--)
			   {
				   slowsl[n]=slow[z];
				   fl=1;
			   }
			   slowsl[n++]='-';
			   nslow=0;
		   }
		   else // сотрит есть ли еще гласные если да ставит черту
			   { 
				   i=z;
				   while(slows[i]>-1 && slows[i]!=1) i++;
					   if(slows[i]==1) slowsl[n++]='-';
				}
			*/
			}
			if(nslow && x1==3 && x2==2 && x3==1)// 321 в начале слова
			{
				if(slow[z+3]!='й')
					for(i=0;i<3;i++,z++,n++,kbukv--)  slowsl[n]=slow[z];
				else for(i=0;i<4;i++,z++,n++,kbukv--)  slowsl[n]=slow[z];
				i=z;
				while(slows[i]!=4 && slows[i]!=1) i++; // поиск согласных и мягкого знака после них
				if(slows[i]==4) // скопление согласных завершаеться мягким знаком
				{
					k=i-z+1;
					for(i=0;i<k;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
				}
				slowsl[n++]='-';
				fl=1;
				nslow=0;
				glasn--;
				per=0;
			}
		}
		if(kbukv>6)
		{
			x1=slows[z+0];
			x2=slows[z+1];
			x3=slows[z+2];
			x4=slows[z+3];
			x5=slows[z+4];
			x6=slows[z+5];
			x7=slows[z+6];
			if(x1==1 && x2==3 && x3==3 && x4==3 && x5==2 && x6==1) //1-33321 ствлё
			{
				slowsl[n++]=slow[z++];
				slowsl[n++]='-';
				for(i=0;i<4;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
				glasn-=2;
				fl=1;
				pk=1;
				nslow=0;
			}
		}
		if(kbukv>3)
		{
			x1=slows[z+0];
			x2=slows[z+1];
			x3=slows[z+2];
			x4=slows[z+3];
			x5=slows[z+4];
			if((x1==3 && x2==3 && x3==3 && x4==1) || (x1==3 && x2==3 && x3==2 && x4==1) )  //3331 или 3321 или    (2212 это удалил. Нет такого ппавиа. это только если посл этих слогов идут только согласные
			{  
				if(nslow==0 && slows[z-1]==1 && slowsl[n-1]!='-') slowsl[n++]='-'; //если перед этой комбинацией 1
				for(i=0;i<4;i++,n++,z++,kbukv--) slowsl[n]=slow[z];  // запись этих букв в разбиение
				// n переменная для записи букв в slowsl
				pk=1;
				nslow=0;
				i=z;  
				while(pk==1 && (slows[i]==2  || slows[i]==3)) i++;   // считаем сколько согласных после этих букв 
				if(slows[i]<0)                       // после этих букв идут только согласные 
				{
					for(k=z;k<i;kbukv--,k++,n++,z++) slowsl[n]=slow[z]; // i указывает на конец слова
					break;
				}
				if(pk==1) pk=0;
				glasn--;
				if(glasn>0) slowsl[n++]='-'; // записываем признак разделения слогов
				fl=1;   // что-то записали
				nslow=0;
				if(x5==4 && glasn>0) // если после этого сочетания есть мягкий или твердый знак
					{
						slowsl[n-1]=slow[z++];
						slowsl[n++]='-';
						nslow=0;
						kbukv--;
					}
			}
			if(x1==3 && x2==3 && x3==3 && x4==3 && x5==1) //33331
			{
				if(nslow==0 && slows[z-1]==1 && slowsl[n-1]!='-') slowsl[n++]='-'; //если перед этой комбинацией 1
				for(i=0;i<5;i++,n++,z++,kbukv--) slowsl[n]=slow[z];  // запись этих букв в разбиение
				// n переменная для записи букв в slowsl
				pk=1;
				nslow=0;
				i=z;  
				while(pk==1 && slows[i]==2  && slows[i]==3) i++;   // считаем сколько согласных после этих букв 
				if(slows[i]==-1)                       // после этих букв идут только согласные 
				{
					for(k=z;k<i;kbukv--,k++,n++,z++) slowsl[n]=slow[z]; // i указывает на конец слова
					break;
				}
				if(pk==1) pk=0;
				glasn--;
				if(glasn>0) slowsl[n++]='-'; // записываем признак разделения слогов
				fl=1;   // что-то записали
				nslow=0;
				if(x5==4 && glasn>0) // если после этого сочетания есть мягкий или твердый знак
					{
						slowsl[n-1]=slow[z++];
						slowsl[n++]='-';
						nslow=0;
						kbukv--;
					}
			}
		}
		if(kbukv>3)
		{
			x1=slows[z];
			x2=slows[z+1];
			x3=slows[z+2];
			x4=slows[z+3];
			if(x1==2 && x2==1 && x3==2 && (x4==2 || x4==3) && glasn>0)
			{
				glasn--;
				for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
				if(glasn>0) slowsl[n++]='-';
			}
			
			/*
			if((x1==3 && x2==3 && x3==1) || (x1==2 && x2==2 && x3==1) || (x1==3 && x2==2 && x3==1))  //331 или 221 или 321 // а мягкий знак здесь не учел
				// написать функцию для поиска здесь мягкого знака (код ниже вывести в функцию)
			{
				i=z+3;								
				while(slows[i]!=1 && slows[i]>-1) i++;
				if(slows[i]>-1)   // есть еще гласные
				{
					for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z]; //записываем 331 или 221
					slowsl[n++]='-';
					glasn--;
					fl=1;
					nslow=0;
				}
				else // гласных нет
				{
					for(i=0;kbukv>0;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					slowsl[n++]='-';
					fl=1;
					glasn--;
					nslow=0;
					break;
				}
				if(x4==4 && glasn>0)  // если после этого сочетания есть мягкий или твердый знак
					{
						slowsl[n-1]=slow[z++];
						slowsl[n++]='-';
						nslow=0;
					}
			}
			*/
			// тут переписать
			if(slows[z]==1 && nslow==1) //13 31 13-21 12-21 12-31 ДОБАВИЛ НАЧАЛО СЛОВА
			{
				x1=slows[z+1];
				x2=slows[z+2];
				x3=slows[z+3];
				if(x1==3 && x2==3 && x3==1) //331
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
					}
					if(x1==3 && x2==2 && x3==1) //321
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
					}
					if(x1==2 && x2==2 && x3==1) //221
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
					}
					if(x1==2 && x2==3 && x3==1) //231 
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
					}
					//смотрим последний ли это слог(т.е. еслить ли еще гласные)
					i=z;
					while(pk==1 && slows[i]>-1 && slows[i]!=1)
						{
							i++;
						}
					if(slows[i]<-1)
					{
						i=i-z;
						for(k=0;k<i;k++,n++,z++) slowsl[n]=slow[z];
						break;
					}
					if(pk==1) pk=0;
			}
			if(nslow==0)  //если не первый слог не начало слова
			{	
				x4=slows[z+3];
				if(x4==1) 
				{
					x1=slows[z];
					x2=slows[z+1];
					x3=slows[z+2];
					x5=slows[z+4];
					x6=slows[z+5];
					// 213 313 удалил
					if(x1==2 && x2==1 && x3==2) //212
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						if(x5==1 || ((x5==2 || x5==3)&& x6==1)) slowsl[n++]='-'; // добавил т.к. всегда так
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
						if(x5==2 && (x6==2 || x6==3)) //21212-3 добавить если 3 не в конце слова
						{
							slowsl[n++]=slow[z++];
							slowsl[n++]='-';
						}
					}
					if(x1==3 && x2==1 && x3==2) //312
					{
						for(i=0;i<4;i++,n++,z++,kbukv--)
						{
							if(i==2) slowsl[n++]='-';
							slowsl[n]=slow[z];
						}
						if(x5==1 || ((x5==2 || x5==3)&& x6==1)) slowsl[n++]='-'; // добавил т.к. всегда так
						nslow=0;
						glasn-=2;
						fl=1;
						pk=1;
						if(x5==2 && (x6==2 || x6==3)) //31212-3
						{
							slowsl[n++]=slow[z++];
							slowsl[n++]='-';
						}
					}
				}
				
			}
			if(nslow==1)
			{
				x1=slows[z+0];
				x2=slows[z+1];
				x3=slows[z+2];
				x4=slows[z+3];
				x5=slows[z+4];
				if(x1==1 && x2==3 & x3==3) //133
				{
					for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					nslow=0;
					slowsl[n++]='-';
					fl=1;
					pk=1;
				}
				if(x1==3 && x2==1 && x3==3 && x4==3 && x5!=1) //3133
				{
					for(i=0;i<4;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					slowsl[n++]='-';
					nslow=0;
					fl=1;
					pk=1;
				}
				i=z;
				while(pk==1 && slows[i]>-1 && slows[i]!=1) i++;   // проверяем не последний ли это слог
				if(slows[i]<-1)
				{  // если слог последний записываем все символы
					i=i-z;
					for(k=0;k<i;k++,n++,z++) slowsl[n]=slow[z];
					break;
				}
				if(pk==1) pk=0;
			}
			x1=slows[z+0];
			x2=slows[z+1];
			x3=slows[z+2];
			x4=slows[z+3];
			if((nslow==0 && ((x1==3 && x2==3 && x3==1) || (x1==2 && x2==2 && x3==1) || 
					(x1==3 && x2==2 && x3==1) || (x1==2 && x2==3 && x3==1) ||
 					(x1==2 && x2==1 && x3==2) || (x1==3 && x2==1 && x3==2 && x4!=1)))||
					((x1==3 || x1==2) && x2==1 && x3==2 && x4!=1))   // 331 221 321 231 312
				{
					if(slowsl[n-1]!='-' && nslow==0) //если перед этими сочетаниями нет черты
					{
						slowsl[n++]='-';
					}
					f=0;
					for(i=0;i<3;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					i=z;
					/* while(slows[i]!=4 && slows[i]!=1) i++; // поиск согласных и мягкого знака после них
					if(slows[i]==4) // скопление согласных завершаеться мягким знаком
					{
						k=i-z+1;
						for(i=0;i<k;i++,z++,n++,kbukv--) slowsl[n]=slow[z];
					}
					*/
					pk=1; // 
					i=z;
					k=i;
					nslow=0;  // теперь точно не начало слова
					while(pk==1 && slows[i]>-1 && (slows[i]==2 || slows[i]==4)) // скопление согласных
					{ // мягкий знак между ними игнорируем
							i++;
					}
					k=i-k+1;
					if((slows[i]<0) && k>3)  // нашли скопление и оно в конце слова
					{
						while(slows[z]>-1)
							slowsl[n++]=slow[z++]; // просто переписываем
						break;
					}
					// точно ли нужна следующая строчка ?
					else if(k>3)  // если скопление не в конеце или вообще не скопление
					{
						slowsl[n++]=slow[z++]; // переписываем но после первой гласной ставим -
						slowsl[n++]='-';
							while(slows[z]>-1)
								slowsl[n++]=slow[z++];
						f=1;   // если заходили сюда
						pk=1;
					}
					i=z;
					while(pk==1 & slows[i]>-1 && slows[i]!=1) i++; // проверяем не последний ли это слог
					if(slows[i]<-1)
					{  // если слог последний записываем все символы
						i=i-z;
						for(k=0;k<i;k++,n++,z++) slowsl[n]=slow[z];
						break;
					}
					if(pk==1) pk=0;
					glasn--;
					if(slow[z]=='т' && slow[z+1]=='ь' && slow[z+2]=='с' && slow[z+3]=='я')  //после этого сочетания ться
					{
						slowsl[n++]='-';
						for(k=0;k<4;k++,n++,z++) slowsl[n]=slow[z];
					}
					else
					{
						if(f!=1 && glasn>0 )  // туда не заходили
						{ 
							if(slows[z]==3 && slows[z+1]==3 && slows[z+2]==3 && slows[z+3]==1)
							{
								slowsl[n++]='-';
								for(k=0;k<4;k++,n++,z++) slowsl[n]=slow[z];
								glasn--;
								if(glasn>0) slowsl[n++]='-';
							}
							else
							{
								if((x4==2 || x4==3) && slows[z+1]!=1)
									{
									slowsl[n++]=slow[z++];
									kbukv--;
									slowsl[n++]='-';
									}
								else
								{
								slowsl[n++]='-';
								f=0;
								} 
							}
						}
						fl=1;
						if(x4==4 && glasn>0) // если после этого сочетания есть мягкий или твердый знак
						{
							i=z+2;  // z==x3
							while(slows[i]>-1 && slows[i]!=4 && (slows[i]==2 || slows[i]==3)) i++;
							if(slows[i]==4)
							{
								slowsl[n-1]=slow[z++];
								for(k=z;k<i+1;k++,z++,kbukv--,n++) slowsl[n]=slow[z];
								slowsl[n++]='-';
								pk=1;
							}
							else
							{
							slowsl[n-1]=slow[z++];
							slowsl[n++]='-';
							pk=1;
							}
						}
					}
					if(slow[z]=='й' && (slows[z+1]==3 || slows[z+1]==2))  //й краткое (2)
					{
						if(glasn>0)
						{
							if(slowsl[n-1]=='-')
							{
								slowsl[n-1]=slow[z++];
								slowsl[n++]='-';
							}
							else
							{
								slowsl[n++]=slow[z++];
								slowsl[n++]='-';
							}
						}
						else 
						{
							while(slow[z]!='\0') slowsl[n++]=slow[z++];

						}
					}
				}
		}
		k=z; f=0;
		while(nslow==0 && slows[k]>-1 && slows[k]==3) {f++; k++; } // СКОПЛЕНИЕ ГЛАСНЫХ 3 И БОЛЕЕ
		if(f>2) //если 2 подряд
			if(slows[k]==2) //следующая после них 2?
			{
				if(slows[k+1]!=1) 
				{
					for(i=z;i<k+1;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					pk=1;
				}
				else
				{
					if(slows[k+1]==1) 
					for(i=z;i<k;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					slowsl[n++]='-';
					fl=1;
				}
			}
			
			// ТУТ еще какойто код 4- мягкий знак 0=твердый знак
		//x1=slows[z]; x2=slows[z+1]; x3=slows[z+2]; x4=slows[z+3];
		/*
		if((x1==1 && x2==1 && fl==0 && nslow==0) || (x1==1 && x2==2 && fl==0 && nslow==0) || (x1==1 && x2==3 && fl==0 && nslow==0) || (x1==2 && x2==3 && fl==0 && nslow==0))   // 1-1 1-2 1-3 2-3 удалил fl=0
		{
			i=z+1;  // считаем если гласная последняя
			while(slows[i]!=1 && slows[i]>-1) i++;    
				if(slows[i]>-1)  // если не конец значит есть еще гласная 
					{
						if(x2==2 && x3==3 && x4==1)   
						{
							slowsl[n++]=slow[z++] ;
							slowsl[n++]=slow[z++] ;
							slowsl[n++]='-';
							glasn--;
							fl=1;
						}
					   /*	else
						{                              // что тут делает забыл поэтому отключил
							slowsl[n++]=slow[z++] ;
							slowsl[n++]='-';
							glasn--;
							fl=1;
						} 
					}
				else               // если нет больше гласных записываем все буквы
				{
					for(i=z;slows[z]>-1;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
					break;
				}
		}
		*/
		
		Sglasn=0;
		i=z; // поиск мягкого или твердого знака
		// надо сделать отходит к предыдущей согласной
		if(mznak==1)
		{
			while((slows[i]>-1) && slows[i]!=4)  // -1 окончание схемы слова 
			{
				if(slows[i] == 1) 	Sglasn++; // считаем гласные до мягкого знака
				i++;  
			}
			if(slows[i]<-1) mznak=0;
			if(slows[i]>-1)      // нашли мягкий знак; i указывает на него
			{                    // i  указвает позицию мягкого знака или твердого знака в схеме

				if(slow[i-1]=='т' && slow[i+1]=='с' && slow[i+2]=='я'&& (i==z+1))                // ТЬСЯ
						{
								if(slows[i-2]==1 && slowsl[n-1]!='-') slowsl[n++]='-';
								for(k=i-1;k<i+3;k++,n++,kbukv--) slowsl[n]=slow[k]; // позиция буквы и ее номер в схеме равны
								slowsl[n++]='-';
								glasn--;
								fl=1;
								z=k;
								if(slows[i+3]<0) break;
						}
				if(Sglasn==1)   // до мягкого знака была только одна гласная
					{
						k=i+1;
						i++;
						while(slows[i]>-1 && slows[i]!=1 && slows[i]!=4) i++;
						if(slows[i]==1 && slow[i]!='я' && slow[i-1]!='c')   // смотрим есть ли после него гласные
						{
							for(i=z;i<k;i++,n++,z++,kbukv--) // если есть черта после мягкого знака
							{
								slowsl[n]=slow[z];
							}
							slowsl[n++]='-';
							glasn--;
							nslow=0;
							fl=1;
						}
						if(slows[i]==4)   // между мягким и твердым нет гласных
						{
							for(i=z;i<k;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
							slowsl[n++]='-';
							nslow=0;
							fl=1;
						}
					}
			}
		}
		/* if(slows[z]==0 || slows[z]==4) // мягкий или твердый знак
		{ slowsl[n++]=slow[z++]; 
		slowsl[n++]='-'; kbukv--; fl=1; 
		glasn--;
		} 
		*/
		x1=slows[z]; x2=slows[z+1]; x3=slows[z+2]; x4=slows[z+3]; x5=slows[z+4];
		if(fl==0) // была ли где-то запись?  fl=0 небыло
				{
					k=z; i=z+1;
					while(slows[i]>-1 && slows[i]!=1) i++;
					if(slows[i]<0)  //гласных больше нет
					{
						for(k=z;k<i;n++,z++,kbukv--,k++) slowsl[n]=slow[z];
						break;
					}
					else
					{
						if(x1==1 && (x2==1 || x2==3))  //1-3 1-1 113-
						{
							if(nslow==0 && slows[z-1]==1 && x2==3 && x3!=1) // смотрит если предыдущая 1
								{
									i=z;// и не конец слова
									while(slows[i]!=1 && slows[i]>0) i++;
									if(slows[i]==1)  // значит не конец слова
									{
										for(i=0;i<2;i++,n++,z++,kbukv--) slowsl[n]=slow[z];
										if(slows[z]!=4) slowsl[n++]='-'; // если после этого сочетания не мягкий знак
										else
										{
											slowsl[n++]=slow[z++];
											slowsl[n++]='-';
											kbukv--;
										}
										glasn--;
									}
									else   // конец слова
									{
										while(slow[z]!='\0') slowsl[n++]=slow[z++];
										break;
									}
								}
							else {
								slowsl[n++]=slow[z++];
								slowsl[n++]='-';
								//slowsl[n++]=slow[z++]; // необходимо
								fl=1;
								nslow=0;
								glasn--;
								}
							if(x2==1 && x5==1 && ((x3==3 && x4==3) ||   //11331 11231 11321 11221
								(x3==2 && x4==3) || (x3==3 && x4==2) ||
								(x3==2 && x4==2)))
							{
								slowsl[n++]=slow[z++];
								slowsl[n++]=slow[z++];
								slowsl[n++]='-';
							}

						} 
						if((x1==3 && x2==3 && nslow==0) || (x1==1 && x2==2))  //1-2 3-3 не начало слова
						{
							slowsl[n++]=slow[z++];
							// 
							fl=1;
							nslow=0;
							if(x1==1) glasn--;
							if(glasn>0)slowsl[n++]='-';
						}
					}
				}
		if(glasn==1) // если осталась одна гласная
		{
			i=z;
			while(slows[i]!=4 && slows[i]>0) i++;
			if(slows[z]<0) //и нет мягкого знака
				{
					while(slow[z]!='\0') slowsl[n++]=slow[z++];
					break;
			}
		}
		if(fl==0)
			{
				if(slows[z+1]==1)
				if(slows[z]==1){ nslow=0; glasn--; }
				slowsl[n++]=slow[z++];
				if(slows[z]==1 && slows[z-1]==4 && nslow==0) slowsl[n++]='-';
			}
		fl=0;
	} // конец цикла выделения слогов
	if(slowsl[n-1]=='-')
		{
			slowsl[n-1] = '\n';
			slowsl[n]='\0';
		}
	else
		{
			slowsl[n]='\n';
			slowsl[n+1]='\0';
		}
	i=0;
	fputs(slowsl,fp2);
	fprintf(stdout,"%s",slowsl);
	i=0;
	n=0;
	while(slowsl[i]!='\0')  // очищаю память слова 
	{
		slowsl[i]='\0';
		slows[i]=-1;
		slow[i]='\0';
		i++;
	}
}    // если больше одной гласной
		else      // если одна гласная в слове записываем его в выходную переменную
		{
			fprintf(stdout,"%s",slow);
			fprintf(fp2,"%s",slow);
		}
}  // цикл счтывания слов
fclose(fp2);
fclose(fp1);
fclose(fp);
getch();
}