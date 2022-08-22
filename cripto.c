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

void teste1(void);
int teste_fermat(mpz_t numero, int base_i);
void teste2(void);
int teste_car(mpz_t numero);
void exibir_pseudoprimos(void);
void teste3();
int miller_rabin(mpz_t numero,int base_i);
void mostrar_fatorando(void);
void mostrar_testando(void);

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
		"[8] Teste de Fermat\n"
		"[9] Teste para ver se um numero é de  Carmichael\n"
		"[10] TEste de Miller-Rabin para o numero dado.\n"
        "[11] EXibe pseudoprimos para o numero dado.\n"
		"[12] Mostrar todos primos até N, fatorando-os\n"
		"[13] Mostrar todos primos até N, testando-os com Miller-Rabin\n"
		"[0] Para sair do programa");
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

			case 8:
				teste1();
				break;
		
			case 9:
				teste2();
				break;


            case 10:
            teste3();
            break;

            case 11:
            exibir_pseudoprimos();
            break;

			case 12:
			mostrar_fatorando();
			break;

			case 13:
			mostrar_testando();
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
			printf("x+y=%ld &&&     x-y=%ld\n"
			"x=%ld e y=%ld\n\n",x+y,x-y,x,y);
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

void teste1(void)
{
    int opcao=-1, base;
    mpz_t numero;
    mpz_init(numero);
    puts("\n\n[*~*~*~*~*~*~*~*~*~*~*~*~]\n"
	"\nO teste de fermat verifica se um numero é composto,\n"
	"utilizando uma das versões do Pequeno Teorema de Fermat, que afirma:\n\n"
	"\t\tSe um numero N é primo, qualquer numero A^(N-1) é congruente a 1 módulo N");
    puts("\n\nInsira o numero que deseja checar se é composto:");
    gmp_scanf("%Zd",numero);

	puts("\n\nInsira a base A que deseja testar:");

    base = valida_int();

    while(opcao!=0)
    {
        if(teste_fermat(numero,base))
        {
            gmp_printf("\n\t\t\t\t\t\t\t\tO numero %Zd é pseudoprimo para a base %d\n\n"
            "Deseja testar outra base? Insira-a, ou 0 para cancelar.\n",numero,base);
            base=valida_int();
            opcao=base;
            
            
        }
        else
        {
            gmp_printf("\n\t\t\t\t\t\t\t\tO numero %Zd é composto\n\n",numero);
            opcao=0;
   
        }
    }

}

int teste_fermat(mpz_t numero, int base_i)
{
    mpz_t modulo,base,exp;
    mpz_init(modulo);
    mpz_init(exp);
    mpz_init_set_ui(base,base_i);
    mpz_sub_ui(exp,numero,1);
    mpz_powm(modulo,base,exp,numero);

    if(!mpz_cmp_ui(modulo,1)) // caso seja pseudoprimo a base
    {
        return 1;
    }
    return 0;
}

void teste2()
{
    mpz_t numero;
    mpz_init(numero);
	puts("Um numero é considerado de Carmichael se para todas as bases A,\n"
	"ele satisfaz a seguinte versão do Pequeno Teorema de Fermat:\n"
	"\n\t Se N é primo, qualquer numero A^N é congruente a A modulo N\n");
    puts("\nInsira o numero a testar primalidade/carmichael:");

    gmp_scanf("%Zd",numero);

    if(teste_car(numero))
    {
        puts("\n\t\t\t\t\t\t\t\tO numero é composto e não-carmichael.\n");
    }
    else
    {
        puts("\t\t\t\t\t\t\t\t O numero é primo ou carmichael!");
    }

}
int teste_car(mpz_t numero)
{
    mpz_t iterador,modulo,limite;

    mpz_init_set_ui(iterador,2);
    mpz_init(modulo);
    mpz_init(limite);
    mpz_sub_ui(limite,numero,1);

    while(mpz_cmp(iterador,limite)<0)
    {
        gmp_printf("Testando com a base %Zd....\n",iterador);
        mpz_powm(modulo,iterador,numero,numero);

        if(mpz_cmp(modulo,iterador)) // se o modulo e diferente da base(iterador)
        {
            return 1;
        }
        mpz_add_ui(iterador,iterador,1);
    }
    return 0;
}

void teste3()
{
    int base,opcao=-1;
    mpz_t numero;
    mpz_init(numero);

    puts("\n\nQual numero deseja testar?");
    gmp_scanf("%Zd",numero);

    puts("\n\nCom qual base?");
    base = valida_int();
    while(opcao!=0)
    {
        if(miller_rabin(numero,base))
        {
            gmp_printf("\t\t\t\t\t\t\t\t\t"
            "O Numero %Zd é composto.\n",numero);
            break;
        }
        else
        {
            gmp_printf("\t\t\t\t\t\t\t\t\t"
            "O numero %Zd é pseudoprimo forte para a base %d \n"
            "Deseja testar outra base? Insira-a ou 0 para cancelar.\n",numero,base);
            base=valida_int();
            opcao = base;
        }
    }
}

int miller_rabin(mpz_t numero,int base_i)
{
    mpz_t limite,k,modulo,par,q,i,base;
    mpz_init_set_ui(i,0);
    mpz_init(modulo);
    mpz_init(k);
    mpz_set_ui(k,0);
    mpz_init(q);

    mpz_init(limite);
    mpz_sub_ui(limite,numero,1);
    mpz_init_set(par,limite);

    mpz_init_set_ui(base,base_i);

    while(1)
    {
        if(mpz_even_p(par))
        {
            mpz_add_ui(k,k,1);
            mpz_fdiv_q_ui(par,par,2);
        }
        else break;
    } // pegar q e k
    mpz_set(q,par);
    mpz_powm(modulo,base,q,numero);
	mpz_set_si(par,1);

	// gmp_printf("TEmos q=%Zd e k=%Zd\n"
	// "i=%Zd e modulo=%Zd\n",q,k,i,modulo);

    while(mpz_cmp(i,k))
    {

		// gmp_printf("testando %Zd elevado a (%Zd elevado a %Zd) * %Zd ) mod %Zd\n"
		// "que é %Zd\n",base,par,i,q,numero,modulo);

        if(  !mpz_cmp(modulo,limite) || 
		(!mpz_cmp_ui(i,0) && !mpz_cmp_si(modulo,1)) ||
		( mpz_cmp_si(i,0) && !mpz_cmp(par,limite) )    )
        {
            return 0; // se pseudoprimo forte a base
        }
        mpz_add_ui(i,i,1); // par vai ser o expoente
		mpz_mul_si(par,par,2);
		mpz_mul(par,par,q);
        mpz_powm(modulo,base,par,numero);
    }
    return 1; // se composto


}
void exibir_pseudoprimos()
{
    int base,n,i,fortes;
    mpz_t candidato;
    mpz_init(candidato);

    puts("\n\n Deseja pseudoprimos para qual base?");
    base = valida_int();

    mpz_set_ui(candidato,base+2);
    puts("QUantos pseudoprimos?");
    n = valida_int();
	puts("Insira:\n [1] Pseudoprimos \"Normais\"\n"
	"[2]Somente pseudoprimos fortes\n");
	fortes =valida_int();


    for(i=0;i<n;i++)
    {
        while(!teste_fermat(candidato,base) || mpz_probab_prime_p(candidato,30))
        {
            mpz_add_ui(candidato,candidato,1);
        }
        if(fortes==1) gmp_printf("\t\t\t\t\t\t\t\t O numero %Zd é pseudoprimo para %d\n",candidato,base);
        if(!miller_rabin(candidato,base))
        {
            if(fortes==1) gmp_printf("\t\t\t\t\t\t\t\t\tE é forte também.\n");
			else 
			{
				gmp_printf("\t\t\t\t\t\t\t\t\tO numero %Zd é pseudoprimo forte para %d\n",candidato,base);
			}
        }
		else if(fortes==2)
		{
			i--;
		}
        mpz_add_ui(candidato,candidato,1);
    }

    
}

void mostrar_fatorando(void)	
{	
	mpz_t num,aux,mod,sqr;
	int opcao;
	long int i,numero;
	puts("\n\n[*~*~*~*~*~*~*~*~*~*~*~*~]\n"
	"\nVocẽ deseja fatorar até N ou fatorar N\n?"
	"[1] Para fatorar N\n"
	"[2] Para fatorar até N\n");

	opcao = valida_int();
	mpz_init(num);
	mpz_init_set_si(aux,2);
	mpz_init(mod);
	mpz_init(sqr);
	puts("\n\nInsira N:");
	gmp_scanf("%Zd",num);
	if(mpz_fits_slong_p(num))
	{
		numero = mpz_get_si(num);
		printf("\n[Numero %ld cabe em long int..]\n",numero);
		
	}
	else opcao=3;

	if(opcao==2)
	{
		for(i=3;i<numero;i+=2)
		{
			if(checa_primalidade(i))
			{
				printf("\n\t %ld é primo",i);
			}
		}
	}
	else if(opcao==1)
	{
		if(checa_primalidade(numero))
		{
			printf("\n\t\t\t\tO numero %ld é primo.\n",numero);
		}
		else
		{
			printf("\n\t\t\t\tO numero %ld é composto.\n",numero);
		}		
	}
	else
	{
		mpz_root(sqr,num,2);
		while(mpz_cmp(aux,sqr))
		{
			mpz_mod(mod,num,aux);
			gmp_printf("testando fator: %Zd\n",aux);
			if(!mpz_cmp_si(mod,0))
			{
				gmp_printf("\n\t\t\t O numero %Zd é composto e tem um fator = %Zd\n",num,aux);
				return;
			}
			mpz_add_ui(aux,aux,1);
		}
		gmp_printf("\n\t\t\t O numero %Zd é primo.",num);


	}
}

void mostrar_testando(void)
{
	mpz_t candidato,aux;
	long int num,testes,i,k,primo=1,r;
	puts("\n\n\n[*~*~*~*~*~*~*~*~*~*~*~*~]\n"
	"Insira o numero limite N (tipo int, nao usarei a GMP):");
	num = valida_int();
	puts("\nInsira o numero de testes a serem feitos para cada candidato:\n");
	testes=valida_int();

	mpz_init(candidato);
	mpz_init(aux);
	
	for(i=5;i<num;i+=2)
	{	
		primo=1;
		mpz_set_si(candidato,i);
		for(k=0;k<testes;k++)
		{
			while(1)
			{
				r=(rand()%i);
				mpz_gcd_ui(aux,candidato,r);
				if(!mpz_cmp_si(aux,1) && r!=1 && r!=i-1) break;
			}

			if(miller_rabin(candidato,r))
			{
				//printf("%ld é composto e r=%ld\n",i,r);
				primo = 0;
				break;
			}
		}

		if(primo)
		{
			gmp_printf("\n \t\t\t\t\t\t\t%Zd é um provavel primo. r=%d\n",candidato,r);
		}
	}

}

