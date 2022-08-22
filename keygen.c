#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>


void gera_p(mpz_t p);
void gera_q(mpz_t q);
void salva(mpz_t n,mpz_t d,mpz_t e);
void teste(mpz_t n,mpz_t d,mpz_t e);
void descripta(mpz_t n, mpz_t d);
void encripta(mpz_t n, mpz_t e);



int main(void)
{
    srand(time(NULL));

    mpz_t p,q,e,d,n,fi,pf,qf,mdc;


    puts("\t\t\t\t\t\t[GERADOR DE CHAVE RSA.......]\n\n"
    "\t\t\t\t\t\t PROCEDIMENTO:\n"
    "\t\t\t\t\t[Gerar 2 primos 'p' e 'q' de 700 ou mais algarismos...]\n\n");

    gera_p(p);
    gmp_printf("\n\n\n\t\t\t\t\t\t[Numero 'p' encontrado. Tamanho = %d]\n\n"
    "\t\t\t\t\t\t NUMERO 'p':\n\n"
    "%Zd\n\n",mpz_sizeinbase(p,10),p);
    
    gera_q(q);

    gmp_printf("\n\n\n\t\t\t\t\t\t[Numero 'q' encontrado. Tamanho = %d]\n\n"
    "\t\t\t\t\t\t NUMERO 'q':\n\n"
    "%Zd\n\n",mpz_sizeinbase(q,10),q);

    puts("\t\t\t\t\t\t[Calcular n=p*q]\n\n");
    mpz_init(n);
    mpz_mul(n,p,q);
    gmp_printf("n = %Zd",n);

    puts("\n\n\t\t\t\t\t[Achar inteiro positivo 'e' relativamente primo a (p-1)*(q-1),"
     "que será a chave de encriptação..]\n\n");

    mpz_init(pf);
    mpz_init(qf);
    mpz_sub_ui(qf,q,1);
    mpz_sub_ui(pf,p,1);
    mpz_init(fi);
    mpz_mul(fi,pf,qf);

    mpz_init(e);
    mpz_init(mdc);
    while(1)
    {
        mpz_set_ui(e,rand());
        mpz_gcd(mdc,e,fi);
        if(!mpz_cmp_si(mdc,1)) break;
    }
    gmp_printf("\t\t\t\t\t['e' encontrado: %Zd]\n",e);


    puts("\n\t\t\t\t\t\t[Achar 'd',    inverso de 'e' ao modulo de n]\n\n");
    mpz_init(d);
    mpz_invert(d,e,fi);
    gmp_printf("\n\t\t\t\t[ 'd' encontrado: %Zd",d);

    puts("\n\nSalvando chaves...");
    salva(n,d,e);
    puts("Chaves salvas!\n");
    

    teste(n,d,e);

    return 0;
}

void gera_p(mpz_t p)
{
    int i=0;


    puts("\n\t\t\t\t testando numero p");
    mpz_init(p);
    while(1)
    {
        i++;
        mpz_set_ui(p,2);

        while(mpz_sizeinbase(p,10)<700 || mpz_sizeinbase(p,10)>800)
        {
            mpz_ui_pow_ui(p,rand()%572,rand()%5+2);
            mpz_pow_ui(p,p,rand()%123+1);
        }
        
        mpz_sub_ui(p,p,rand()%200);
        if(!(i%64)) putchar('.');
        if(mpz_probab_prime_p(p,46)) break;


    }
    
}


void gera_q(mpz_t q)
{
    int i=0;


    puts("\n\t\t\t\t testando numero q");
    mpz_init(q);
    while(1)
    {
        i++;
        mpz_set_ui(q,2);

        while(mpz_sizeinbase(q,10)<700 || mpz_sizeinbase(q,10)>800)
        {
            mpz_ui_pow_ui(q,rand()%572,rand()%5+2);
            mpz_pow_ui(q,q,rand()%123+1);
        }
        
        mpz_sub_ui(q,q,rand()%200);
        if(!(i%64)) putchar('.');
        if(mpz_probab_prime_p(q,46)) break;


    }
    
    
    
}

void salva(mpz_t n,mpz_t d,mpz_t e)
{
    FILE *pa;

    pa = fopen("chaves.txt","w");
    if(pa==NULL)
    {
        puts("\nErro criando arquivo de chaves.\n");
        return;
    }


    fputs("n: ",pa);
    mpz_out_str(pa,10,n);


    fputs("\ne: ",pa);
    mpz_out_str(pa,10,e);


    fputs("\nd: ",pa);
    mpz_out_str(pa,10,d);

    fclose(pa);
    return;
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
