#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//#include "func.h"
#define N 1000


void form_t(int n, float *t)
{
	float tn=0,tk=2;
	float dt=(tk-tn)/(n-1);
	for (int i=0;i<n;i++)
	{
		t[i]=tn+i*dt;
	}
}

void form_Uvx(int n,float *t,float *Uvx)
{
	float a1=1.5,a2=3,U=25;
	for (int i=0;i<n;i++)
	{
		Uvx[i]=U*(exp(-a1*t[i])-exp(-a2*t[i]));
	}
}

void form_Uvix(int n,float *Uvix,float *Uvx)
{
	float Uvx1=10;
	for (int i=0;i<n;i++)
	{
		if (Uvx[i]<=Uvx1){
			Uvix[i]=4;}
		else {Uvix[i]=(Uvx[i]-1)*(Uvx[i]-1);}
	}
}

void print_mas(int n,float *t, float *Uvx,float *Uvix)
{
	printf("  №      t       Uvx     Uvix  \n\n");
	for (int i=0;i<n;i++)
	{
		printf("%3d %8.5f %8.5f %8.5f\n",i+1,t[i],Uvx[i],Uvix[i]);
	}
}

void write_to_file()
{
	//Формирование массивов для n точек и вывод в файл
	float t[N],Uvx[N],Uvix[N];
	int n;printf("Количество точек:");scanf("%d",&n);
	form_t(n,t);
	form_Uvx(n,t,Uvx);
	form_Uvix(n,Uvix,Uvx);

	FILE *f1,*f2,*f3;
	f1=fopen("massiv_t.txt","w");
	f2=fopen("massiv_Uvx.txt","w");
	f3=fopen("massiv_Uvix.txt","w");
	
	for (int i=0;i<n;i++)
	{
		fprintf(f1,"%7.5f\n",t[i]);
		fprintf(f2,"%7.5f\n",Uvx[i]);
		fprintf(f3,"%7.5f\n",Uvix[i]);
	}
	fclose(f1);fclose(f2);fclose(f3);
}

float param(int n,float *Uvx,float *t,int pr)
{
	float max=0;
	for (int i=0;i<n;i++)
	{
		if (Uvx[i]>max) {max=Uvx[i];}
	}

	float vrem;
	for (int i=0;i<n;i++)
	{
		if (Uvx[i]==max) {vrem=t[i];break;}
	}
	if (pr){printf("\nМаксимум Uvx = %7.5f  в точке t = %7.5f\n",max,vrem);}
	return vrem;
}


void param_w_accuracy(int n,float *t,float *Uvx )
{
	float ourParamValue,bigParamValue,pogreshnost;
	ourParamValue=param(n,Uvx,t,1);

	float t1[N],Uvx1[N],Uvix1[N];
	int n1=500;
	form_t(n1,t1);
	form_Uvx(n1,t1,Uvx1);
	form_Uvix(n1,Uvix1,Uvx1);
	bigParamValue=param(n1,Uvx1,t1,0);

	pogreshnost=fabs(bigParamValue-ourParamValue)/ourParamValue;
	printf("\rПогрешность:%.5f\n",pogreshnost);
}

void zastavka()
{
	FILE *zast = fopen("zastavka.txt","r");
	char ch;
	while (!feof(zast))
	{
		fscanf(zast,"%c",&ch);
		printf("%c",ch);
	}
	fclose(zast);
}

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
		case 1:printf("\n             РАСЧЕТ ПАРАМЕТРА        ");param(n,Uvx,t,1);break;
		case 2:printf("\n     РАСЧЁТ ПАРАМЕТРА С ЗАДАННОЙ ТОЧНОСТЬЮ ");param_w_accuracy(n,t,Uvx);break;
		case 3:write_to_file();printf("Данные успешно записаны в файл!\n");break;
		}
		int ch;
		printf("\nПродолжить работу программы? [1(Да)/0(Нет)]");
		while (1)
		{
			scanf("%d",&ch);
			if (ch==1) {system("clear");break;}
			else if (ch==0) {printf("Работа программы завершена\n");exit(0);}
			else printf("Попробуйте снова\n");
		}
	}

	//printf("\nМаксимум Uvx достигается в точке %8.4f\n",param(n,Uvx,t));
	write_to_file();
	param (n,Uvx,t,1);
	param_w_accuracy(n,t,Uvx);
	
	return 0;
}
