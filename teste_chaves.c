#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>


void teste(mpz_t n,mpz_t d,mpz_t e);
void descripta(mpz_t n, mpz_t d);
void encripta(mpz_t n, mpz_t e);

void carrega(mpz_t n,mpz_t d,mpz_t e);



int main(void)
{
    mpz_t n,d,e;
    mpz_init(n);
    mpz_init(d);
    mpz_init(e);
    
    carrega(n,d,e);
    teste(n,d,e);

    return 0;
}


void teste(mpz_t n,mpz_t d,mpz_t e)
{
    int opcao=-1;
    while(opcao!=0)
    {
        puts("\n\nTeste de chaves!!! Insira o que deseja:\n"
        "[1] Encriptar dado\n"
        "[2] Descriptar dado.");
        scanf("%d",&opcao);

        switch(opcao)
        {
            case 1:
            encripta(n,e);
            break;

            case 2:
            descripta(n,d);
            break;
        }
    }
}

void encripta(mpz_t n, mpz_t e)
{
    mpz_t encript;
    mpz_init(encript);

    puts("\n insira o numero a ser encriptado:");
    gmp_scanf("%Zd",encript);

    mpz_powm(encript,encript,e,n);
    
    gmp_printf("\nDado encriptado: %Zd",encript);

}

void descripta(mpz_t n, mpz_t d)
{
    mpz_t descript;

    mpz_init(descript);
    puts("\n insira o numero a ser descriptado:");

    gmp_scanf("%Zd",descript);

    mpz_powm(descript,descript,d,n);
    
    gmp_printf("\nDado descriptado: %Zd",descript);

}


void carrega(mpz_t n,mpz_t d,mpz_t e)
{
    FILE *pa;


    pa=fopen("chaves.txt","r");
    if(pa==NULL)
    {
        puts("\nErro abrindo arquivo.\n");
        return;
    }

    gmp_fscanf(pa,"n: %Zd",n);

    gmp_fscanf(pa,"\ne: %Zd",e);
    

    gmp_fscanf(pa,"\nd: %Zd",d);

    fclose(pa);

    gmp_printf("n: %Zd\n"
    "e: %Zd\n"
    "d: %Zd\n",n,e,d);

}