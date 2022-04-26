#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
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
	if (pr){printf("\nМаксимум Uvx = %7.5f достигается в точке t = %7.5f\n\n",max,vrem);}
	return vrem;
}


void param_w_accuracy(int n,float *t,float *Uvx )
{
	float p=1,eps=0.5,par=9999999;
	while (p>eps)
	{
		float par1=param(n,Uvx,t,0);
		p=fabs(par-par1)/par1;
		printf("n = %d\nparametr = %f\npogreshnost = %f\n",n,par1,p);
		par=par1;
		n=2*n;
	}
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
		printf("|1 - Контрольный расчет t,Uvx,Uvix для n точек  |\n");
		printf("|2 - Расчет параметра с заданной точностью      |\n");
		printf("|3 - Запись данных t,Uvx,Uvix в файлы           |\n%s",str);
				
		printf("Количество точек:");
		scanf("%d",&n);

		form_t(n,t);
		form_Uvx(n,t,Uvx);
		form_Uvix(n,Uvix,Uvx);
		print_mas(n,t,Uvx,Uvix);
		scanf("%d",&choice);

		switch (choice)
		{
		case 2:param(n,Uvx,t,1);break;
		case 3:write_to_file();break;
		}
		int ch;
		printf("Вернуться к началу цикла? [1(Да)/0(Нет)]");
		while (1)
		{
			scanf("%d",&ch);
			if (ch==1) {break;}
			else if (ch==0) exit(0);
			else printf("Попробуйте снова\n");
		}
	}

	//printf("\nМаксимум Uvx достигается в точке %8.4f\n",param(n,Uvx,t));
	write_to_file();
	param (n,Uvx,t,1);
	param_w_accuracy(n,t,Uvx);
	
	return 0;
}
