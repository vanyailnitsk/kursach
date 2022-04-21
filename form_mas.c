#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
	//Формирование массивов для 50 точек и вывод в файл
	float t[N],Uvx[N],Uvix[N];
	form_t(50,t);
	form_Uvx(50,t,Uvx);
	form_Uvix(50,Uvix,Uvx);

	FILE *f1,*f2,*f3;
	f1=fopen("massiv_t.txt","w");
	f2=fopen("massiv_Uvx.txt","w");
	f3=fopen("massiv_Uvix.txt","w");
	
	for (int i=0;i<50;i++)
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
	int n;
	scanf("%d",&n);

	form_t(n,t);

	form_Uvx(n,t,Uvx);

	form_Uvix(n,Uvix,Uvx);

	print_mas(n,t,Uvx,Uvix);

	//printf("\nМаксимум Uvx достигается в точке %8.4f\n",param(n,Uvx,t));
	write_to_file();
	param (n,Uvx,t,1);
	param_w_accuracy(n,t,Uvx);
	zastavka();
	return 0;
}
