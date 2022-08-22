#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h> 
#include <time.h>


long int* divisao();
long int mdc(long int a,long int b);
long int* fatoracao_com_repeticao(long int a);
long int* bezout(long int a,long int b);
void fatoracao_fermat(long int a);
long int* fatoracao_sem_repeticao(long int a);
long int qtd_divisores(long int a);
void numeros_perfeitos(long int a);


float raiz(long int n);
void print_vetor(long int *pvt, int tam);
long int valida_int(void);
long int valida_int_fatoracao(void);
long int potencia(long int base,int exp);
int checa_primalidade(long int n);



int main(void)
{
	int opcao=-1;
	long int b,*q_r,*xy,a,*lista;
	
	while(opcao!=0)
	{
		puts("\n\n\n\n[*~*~*~*~*~*~]\nInsira a operação que deseja fazer:\n"
		"[1] Para dividir um número pelo outro\n"
		"[2] Para achar o MDC de dois numeros\n"
		"[3] Para achar x e y da combinação linear do MDC de dois numeros.\n"
		"[4] Fatoracao nao-distinta \n"
		"[5] Fatoracao por Fermat\n"
		"[6] Para a fatoraçao distinta\n"
		"[7] QUantidade de divisores de um numero e soma dos divisores\n"
		);
		opcao=valida_int();

		switch (opcao)
		{
			case 1:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o dividendo:");
				a=valida_int();
				puts("\nInsira o divisor:");
				b=valida_int();

				q_r = divisao(a,b);
				printf("\nO resultado da divisão de [%ld] por [%ld] \n"
				"terá quociente=[%ld]\n"
				"E resto=[%ld]\n\n\n*******************\n\n\n",a,b,q_r[0],q_r[1]);
				free(q_r);
				break;

			case 2:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o primeiro numero:");
				a=valida_int();
				puts("\nInsira o segundo numero:");
				b=valida_int();
				printf("\n\nO MDC(%ld,%ld) é = %ld\n\n\n*********\n\n"
				,a,b,mdc(a,b));
				break;

			case 3:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o primeiro numero:");
				a=valida_int();
				puts("\nInsira o segundo numero:");
				b=valida_int();
				xy=bezout(a,b);
				printf("\n\nPara [%ld*x + %ld*y = %ld], teremos\n"
				"x = %ld e y = %ld"
				"\n\n*******\n\n"
				,a,b,mdc(a,b),xy[0],xy[1]);
				free(xy);
				break;
			case 4:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o numero a ser fatorado:");
				a=valida_int_fatoracao();
				puts("\nFatores primos não-distintos:");
				lista=fatoracao_com_repeticao(a);
				print_vetor(lista,lista[0]);
				free(lista);

				break;

			case 5:
				puts("\n\n[*~*~*~*~*~*~]\nInsira um numero impar a ser fatorado por fermat:");
				a=valida_int_fatoracao();
				puts("\nFatores por Fermat:");
				fatoracao_fermat(a);
				break;

			case 6:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o numero a ser fatorado:");
				a=valida_int_fatoracao();
				puts("\nFatores primos distintos:\n");
				lista=fatoracao_sem_repeticao(a);
				print_vetor(lista,lista[0]);
				free(lista);
				break;

			case 7:
				puts("\n\n[*~*~*~*~*~*~]\nInsira o numero para descobrirmos a quantidade de divisores:");
				a=valida_int_fatoracao();
				printf("O número de divisores de %ld é igual a : %ld",a,qtd_divisores(a));
				break;

			
		}
	}

	return 0;
}

long int valida_int(void)        //VALIDA INTEIROS
{
	int valido,lixo,valor;
	valido=scanf("%d",&valor);
        while(valido==0)
        {
            while((lixo=getchar()) != EOF && lixo!= '\n');
            puts("\nInsira um valor válido: ");
            valido=scanf("%d",&valor);
        }
	return valor;
}

long int* divisao(long int a,long int b)
{
	long int *p=0,q,r;

	r=a;
	q=0;
	while(r>=b)
	{
		r=r-b;
		q++;
	}

	p=(long int*)calloc(2,sizeof(long int));

	*p=q;
	*(p+1)=r;

	return p;

}

long int mdc(long int a,long int b)
{
	long int *q_r;
	q_r=divisao(a,b);
	while(q_r[1]!=0)
	{
		a=b;
		b=q_r[1];
		free(q_r);
		q_r=divisao(a,b);
	}
	free(q_r);
	return b;

}

long int* bezout(long int a,long int b)
{
	int x_2=1,y_2=0,x_1=0,y_1=1;
	long int x,y,*q_r;
	long int *xy=0;

	q_r=divisao(a,b);
	x=x_2-(x_1*q_r[0]);
	y=y_2-(y_1*q_r[0]);

	while(q_r[1]!=0)
	{

		x=x_2-(x_1*q_r[0]);
		y=y_2-(y_1*q_r[0]);

		x_2=x_1;
		x_1=x;
		y_2=y_1;
		y_1=y;

		a=b;
		b=q_r[1];
		free(q_r);
		q_r=divisao(a,b);
	}
	free(q_r);

	xy=(long int*)calloc(2,sizeof(long int));
	xy[0]=x;
	xy[1]=y;

	return xy;

}
/* a funçao a seguir retorna um ponteiro para uma array dinamico com todos os fatores primos REPETIDOS de "a".
	ESSENCIAL: o indice 0 armazena um inteiro com o tamanho do array.
	Ou seja, o numero de fatores distintos será p[0]-1
	e a partir de p[1] temos os fatores. */
long int* fatoracao_com_repeticao(long int a)
{
	long int i,n,*lista,tam=1;
	n=a;
	float rz=raiz(a);

	lista = calloc(1,sizeof(long int));
	lista[0]=1;

	for(i=2;i<=rz;i++)
	{
		while(n%i==0)
		{
			tam++;
			lista = realloc(lista,tam*(sizeof(long int)));
			lista[0]=tam;
			lista[tam-1]=i;
			n=n/i;
			rz=raiz(n);
		}
	}
	if(n!=1)
	{
	tam++;
	lista = realloc(lista,tam*(sizeof(long int)));
	lista[0]=tam;
	lista[tam-1]=n;
	}


	return lista;


}
/* a funçao a seguir retorna um ponteiro para uma array dinamico com todos os fatores primos DISTINTOS de "a".
	ESSENCIAL: o indice 0 armazena um inteiro com o tamanho do array.
	Ou seja, o numero de fatores distintos será p[0]-1
	e a partir de p[1] temos os fatores. */
long int* fatoracao_sem_repeticao(long int a)
{
	long int i,n,*lista,tam=1;
	n=a;
	float rz=raiz(a);

	lista = calloc(1,sizeof(long int));
	lista[0]=1;

	for(i=2;i<=rz;i++)
	{
		if(n%i==0)
		{
			tam++;
			lista = realloc(lista,tam*(sizeof(long int)));
			lista[0]=tam;
			lista[tam-1]=i;
			while(n%i==0) n=n/i;
			rz=raiz(n);
		}
	}
	if(n!=1)
	{
	tam++;
	lista = realloc(lista,tam*(sizeof(long int)));
	lista[0]=tam;
	lista[tam-1]=n;
	}


	return lista;


}

void fatoracao_fermat(long int a)
{
	long int x=raiz(a),y;
	float yfloat=raiz(a);
	printf("Parte inteira da raiz de %ld eh %ld\n",a,x);
	if(x*x==a)
	{
		printf("  %ld  ",x);
	}
	else
	{
		x++;
		yfloat=raiz((x*x)-a);
		y=yfloat;
		while( (y*y!=(x*x)-a) && (x!=(a+1)/2))
		{
			x++;
			yfloat=raiz((x*x)-a);
	    y= (long int) yfloat;
			//printf("x+y=%ld &&&     x-y=%ld\n"
			//"x=%ld e y=%ld\n\n",x+y,x-y,x,y);
		}
    if(y*y==(x*x)-a)
		{
			printf("FAtores: %ld e %ld",(x+y),(x-y));
		}
		else if(x==(a+1)/2)
		{
			printf("%ld eh primo.\n",a);
		}
	}
}


long int qtd_divisores(long int a)
{
	long int *distintos,*repetidos,*expoentes,conta=0;
	long int i,j,k,*soma_pg;

	distintos = fatoracao_sem_repeticao(a);
	repetidos = fatoracao_com_repeticao(a);

	expoentes = calloc(distintos[0]-1,sizeof(int));
	soma_pg = calloc(distintos[0]-1,sizeof(int));

	for(k=0,i=1;i<distintos[0];i++,k++)
	{
		conta=0;
		for(j=1;j<repetidos[0];j++)
		{
			distintos[i]==repetidos[j]? conta++ : 0;
		}

		expoentes[k]=conta+1;

	}
	k=1; //será o resultado
	for(i=0;i<distintos[0]-1;i++)
	{
		k*=expoentes[i];
	}


	//armazenando a soma da pg onde (razao=fator primo, termos = n_expoentes, 1o termo=1) para cada fator primo EM soma_pg
	
	// print_vetor(distintos,distintos[0]);
	// for(i=0;i<distintos[0]-1;i++)
	// {
	// 	printf("\no expoente de %d é = %d",distintos[i+1],expoentes[i]-1);
	// }

	for ( i=1,j=0; i < distintos[0]; i++,j++)
	{
		soma_pg[j]= ( potencia(distintos[i],expoentes[j]) - 1 ) / ( distintos[i] - 1);
	}
	j=1;
	for(i=0;i<distintos[0]-1;i++)
	{
		j=j*soma_pg[i];
	}
	printf("\nA soma dos divisores de %ld eh = %ld\n",a,j);

	return k;



}





long int valida_int_fatoracao(void)
{
	int valido,lixo;
	long int valor;
	valido=scanf("%ld",&valor);
        while(valido==0 || valor <2)
        {
            while((lixo=getchar()) != EOF && lixo!= '\n');
            puts("\nInsira um valor válido: ");
            valido=scanf("%ld",&valor);
        }
	return valor;
}

long int potencia(long int base,int exp)
{
	int i,n=base;
	for(i=0;i<exp-1;i++)
	{
		n*=base;
	}

	return n;
}

float raiz(long int n)
{
	long int sup,inf,usa;
	float qse_raiz;
	for(sup=0;;sup++)
	{
		if(sup*sup>n) break;
	}
	inf=sup-1;
	(sup*sup)-n>n-(inf*inf)?(usa=inf):(usa=sup);
	qse_raiz=(((n+(usa*usa))*1.0)/(2*usa));
	return qse_raiz;
}

void print_vetor(long int *pvt, int tam)
{
    int i;
	for(i=1;i<tam;i++)
    {
		if(i==1) printf("\n\t{");
        printf(" %ld ,",pvt[i]);
    }
	puts("}\n");
}

int checa_primalidade(long int n)
{
	float rz=raiz(n);
	long int i;
	for(i=2;i<=rz;i++)
	{
		if(n%i==0)
		{
			return 0;
		}
	}
	return 1;
}

