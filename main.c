#include "func.h"
#define N 1000


int main()
{
	float t[N],Uvx[N],Uvix[N];
	int n=10,choice;
	system("clear");
	while (1)
	{
		zastavka();
		char str[]="-------------------------------------------------\n";
		printf("%s|                      МЕНЮ                     |\n",str);
		printf("|1 - Расчет параметра                           |\n");
		printf("|2 - Расчёт параметра с заданной точностью      |\n");
		printf("|3 - Запись данных t,Uvx,Uvix в файлы           |\n%s",str);
				
		printf("Количество точек:");
		scanf("%d",&n);

		form_t(n,t);
		form_Uvx(n,t,Uvx);
		form_Uvix(n,Uvix,Uvx);
		print_mas(n,t,Uvx,Uvix);
		
		printf("\n Выбор:");scanf("%d",&choice);
		switch (choice)
		{
		case 1:printf("\n             РАСЧЕТ ПАРАМЕТРА №4        ");param(n,Uvx,t,1);break;
		case 2:printf("\n   НАХОЖДЕНИЕ МОМЕНТА ВРЕМЕНИ ПРИ КОТОРОМ UVX ДОСТИГАЕТ МАКСИМУМА ");param_w_accuracy(n,t,Uvx);break;
		case 3:write_to_file(n);printf("Данные успешно записаны в файл!\n");break;
		default:printf("Нет такой опции\n");
		}
		int ch;
		printf("\nПродолжить работу программы? [1(Да)/0(Нет)]");
		while (1)
		{
			scanf("%d",&ch);
			if (ch==1) {system("clear");break;}
			else if (ch==0) {printf("Работа программы завершена\n");sleep(2.5);exit(0);}
			else printf("Попробуйте снова\n");
		}

	}

		
	
	return 0;
}
