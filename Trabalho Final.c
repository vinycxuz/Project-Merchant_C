#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define CPF 11
//CÓDIGO DA DUPLA: VINÍCIUS AARÃO CALDAS DA COSTA E LARYSSA RIBEIRO SOUSA
//Estrutura do CLIENTE
struct arvore{
    int cod, fb;
    char nome[MAX];
    char cpf[11];
    long int telefone;
    struct arvore *esquerda;
    struct arvore *direita;
    struct arvore *pai;
};

struct arvore *raiz = NULL;
//FUNÇÕES DO CLIENTE
void alteraCliente();
void insere();
void exibir_ordenado(struct arvore*);
void remove_p();
void remover(struct arvore*);
struct arvore* menor_direita(struct arvore*);
struct arvore* buscar(int);
int altura(struct arvore*);
struct arvore* balanceia(struct arvore*);
struct arvore* rot_direita(struct arvore*);
struct arvore* rot_esquerda(struct arvore*);
void exibir_niveis_b(struct arvore *aux, int atual, int cont);
//ESTRUTURA DO PRODUTO
typedef struct P {
    int codigo;
    char descricao[MAX];
    float preco;
    struct P *esq;
    struct P *dir;

}produto;
//ESTRUTURA PARA DATA
typedef struct d
{
    int dia;
    int mes;
    int ano;
}DATA;

//ESTRUTURA DO ESTOQUE
typedef struct E {
    int qntd;
    DATA data;
    int code;
    struct E *proximo;
}Estoque;


//VERIFICAR SE CPF TEM SÓ LETRAS, SERVE PARA NUMERO ALEATORIO
int verificacao_cpf(char x[])
{
    int i = 0;
    int len = strlen(x);

    for(i = 0;i < len; i++)
    {
        if(x[i] < '0' || x[i] > '9')
            return 0;
    }
    return 1;
}
//VERIFICAR A VALIDAÇÃO DO CPF
int validacao_cpf(char x[]){
    int i, j, dig1 = 0, dig2 = 0;
    if((strcmp(x,"00000000000") == 0) ||
       (strcmp(x,"11111111111") == 0) ||
       (strcmp(x,"22222222222") == 0) ||
       (strcmp(x,"33333333333") == 0) ||
       (strcmp(x,"44444444444") == 0) ||
       (strcmp(x,"55555555555") == 0) ||
       (strcmp(x,"66666666666") == 0) ||
       (strcmp(x,"77777777777") == 0) ||
       (strcmp(x,"88888888888") == 0) ||
       (strcmp(x,"99999999999") == 0))
        return 0;
    else
    {
        for(i = 0, j = 10; i < strlen(x)-2; i++, j--)
        {
         dig1 += (x[i]-48) * j;
        }
         dig1 %= 11;
        if(dig1 < 2)
        {
         dig1 = 0;
        }
        else
        {
         dig1 = 11 - dig1;
        }
        if((x[9]-48) != dig1)
        {
            return 0;
        }
        else
        {
        for(i = 0, j = 11; i < strlen(x)-1; i++, j--)
        {
         dig2 += (x[i]-48) * j;
        }
         dig2 %= 11;
        if(dig2 < 2)
        {
          dig2 = 0;
        }
        else
        {
         dig2 = 11 - dig2;
        }
        if((x[10]-48) != dig2)
            {
            return 0;
            }
        }
    }
    return 1;
}
//CRIAR ARVORE DO PRODUTO
produto *criaArvore (void)
{
    return NULL;
}
//BUSCAR O PRODUTO E RETORNAR O ENDEREÇO
produto *BuscaProduto(produto *P, int cod)
{
    if(P == NULL)
        return NULL;
    else if (P->codigo > cod)
        return BuscaProduto(P->esq, cod);
    else if (P->codigo < cod)
        return BuscaProduto(P->dir, cod);
    else return P;
}
//FUNÇÃO PARA ALTERAR O PRODUTO, BSUCA O ENDEREÇO DO PRODUTO E ATRIBUINDO OS NOVOS DADOS.
produto *alterarProduto (produto *P, int cod, float pre, char *N){
    BuscaProduto(P, cod);
    P->codigo = cod;
    P->preco = pre;
    strcpy(P->descricao, N);
    return P;
}
//FUNÇÃO PARA INSERIR OS DADOS DOS PRODUTOS
produto *InserirProduto (produto *P, int cod, float pre, char *N){
    if(P == NULL){
        P = (produto*) malloc(sizeof(produto));
        P->codigo = cod;
        P->preco = pre;
        strcpy(P->descricao, N);
        P->esq = P->dir = NULL;
    }
    else if(cod < P->codigo)
        P->esq = InserirProduto(P->esq, cod, pre, N);

    else
        P->dir = InserirProduto(P->dir, cod, pre, N);

    return P;
}

//FUNÇÃO QUE BUSCA PRODUTO NO ESTOQUE
Estoque *buscaEstoque (Estoque* el, int cod);
void BuscarProduto (produto *P, Estoque *E, int cod){
    P = BuscaProduto(P,cod);
    E = buscaEstoque(E, cod);
        if(P != NULL){
        printf("Produto encontrado.\n");
        printf("\n");
        printf("Produto do codigo: %d\n", P->codigo);
        printf("Preco atual: %f\n", P->preco);
        printf("Descricao do produto: %s\n", P->descricao);
        printf("\n");
        printf("Pressione enter para continuar. \n");
        printf("\n");
        getchar();
        }
        else{
            printf("Produto nao encontrado. \n");
            printf("Pressione enter para continuar. \n");
            printf("\n");
            getchar();
        }
}

//FUNÇÃO QUE REMOVE PRODUTO DO ESTOQUE
produto* RemoverProduto (produto *P, int cod){
    if (P == NULL)
        return NULL;
    else if(P->codigo > cod)
        P->esq = RemoverProduto(P->esq, cod);
    else if(P->codigo < cod)
        P->dir = RemoverProduto(P->dir, cod);
    else {
        if(P->esq == NULL && P->dir == NULL){
            free(P);
            P = NULL;
            return P;
        }
     else if(P->esq == NULL){
        produto *T = P;
        P = P->dir;
        T = NULL;
        free(T);
        return T;
     }
     else if(P->dir == NULL) {
        produto *T = P;
        P = P->esq;
        T = NULL;
        free(T);
        return T;
     }
     else {
        produto* F = P->esq;
        while(P->dir != NULL){
            F = F->dir;
        }
        P->codigo = F->codigo;
        F->codigo = cod;
        P->esq = RemoverProduto(P->esq, cod);
      }
    }
}
//FUNÇÃO PARA LISTAR OS PRODUTOS CADASTRADOS
void ImprimirProduto (produto *P){
    if(P != NULL){
        ImprimirProduto(P->esq);
        printf("\n");
        printf("Produto do codigo: %d\n", P->codigo);
        printf("Preco atual: %f\n", P->preco);
        printf("Descricao do produto: %s\n", P->descricao);
        printf("\n");
        ImprimirProduto(P->dir);
    }
    else{
        printf("Encerrada procura.\n");
        printf("Pressione enter para continuar. \n");
        printf("\n");
        getchar();

    }
}

Estoque *inicio(void){
return NULL;
}
//FUNÇÃO PARA REALIZAR ENTRADA DE UM PRODUTO DO ESTOQUE
Estoque *EntradaProduto (Estoque* e, produto *P, int quantidade, int d, int m, int a, int codigo)
{
    if(P->codigo == codigo){
    Estoque *Novo = (Estoque*) malloc(sizeof(Estoque));
    Novo->qntd = quantidade;
    Novo->code = codigo;
    Novo->data.dia = d;
    Novo->data.mes = m;
    Novo->data.ano = a;
    Novo->proximo = e;
    return Novo;
    }
}

//FUNÇÃO PARA RETIRAR O ESTOQUE DE UM PRODUTO
Estoque *SaidaProduto (Estoque* el, int codigo)
{
  Estoque *anterior = NULL;
  Estoque *e = el;

  while(e != NULL && e->code != codigo){
    anterior = e;
    e = e->proximo;
  }

  if(e == NULL)
    return el;

  if(anterior == NULL){
    el = e->proximo;
  }else
  {
      anterior->proximo = e->proximo;
  }
  free(e);
  e = NULL;
  return e;
}
//FUNÇÃO QUE BUSCA UM DETERMINADO PRODUTO NO ESTOQUE, RETORNANDO O ENDEREÇO
Estoque *buscaEstoque (Estoque* el, int cod)
{
    Estoque* e;
    for(e=el; e!=NULL; e=e->proximo)
        if(e->code == cod)
            return e;
        return NULL;
    }

//FUNÇÃO QUE PROCURA UM PRODUTO E MOSTRA O ESTOQUE DELE
void ExibirEstoque (Estoque *el, int cod)
{
        el = buscaEstoque(el, cod);
        if(el != NULL){
            printf("Codigo do produto: %i \n", el->code);
            printf("Quatidade em estoque: %i \n", el->qntd);
            printf("Data de insercao do ultimo estoque: %i / %i / %i\n",el->data.dia, el->data.mes, el->data.ano);
            printf("Pressione enter para continuar. \n");
            printf("\n");
            getchar();
        } else
        printf("Produto nao encontado. \n");
}
//VERIFICAR SE O VALOR DE PREÇO É VALIDO
int validacao_preco(float x)
{
    if(x <= 0)
        return 0;
    else
        return 1;
}
//MENU PADRÃO
void menu (){
    printf("Sistema e-commerce Judas Supermercados.\n");
    printf("Selecione uma das seguintes opcoes:\n");
    printf("0 - Atualizar o menu.\n");
    printf("1 - Inserir Produto.\n");
    printf("2 - Buscar Produto.\n");
    printf("3 - Alterar Produto.\n");
    printf("4 - Excluir Produto.\n");
    printf("5 - Exibir informacoes de produtos.\n");
    printf("6 - Cadastrar Cliente.\n");
    printf("7 - Alterar Cliente.\n");
    printf("8 - Excluir Cliente.\n");
    printf("9 - Exibir informacoes de um cliente.\n");
    printf("10 - Entrada ou saida de estoque de um produto.\n");
    printf("11 - Exibir estoque atual de um produto.\n");
    printf("+12 - Sair do sistema.\n");
}
//MENU COM O CODIGO DOS PRODUTOS, VALE RESSALTAR QUE O CODIGO DE CADA PRODUTO SEGUE A LEGENDA ACRESCIDO DE 1, OU SEJA.
//EXEMPLO: PRIMEIRO PRODUTO CADASTRADO, TIPOS CARNES,, SERÁ 310000 + 1. SE FOR UMA SEGUNDA PRODUTO DE CARNE CADASTRADO
//SERÁ 310001 + 1, E ASSIM SUCESSIVAMENTE.
void codigosProdutos(){
    printf("Selecao de produto e-commerce Judas Supermercados.\n");
    printf("O preco de carnes e queijos sao dados em quilogramas.\n");
    printf("Selecione o tipo de produto:\n");
    printf("1 - Carnes [cod. 3100000]\n");
    printf("2 - Laticinios. [cod. 3200000]\n");
    printf("3 - Cereias. [cod. 3300000]\n");
    printf("4 - Hortalicas e legumes. [cod. 3400000]\n");
    printf("5 - Produtos de higiene e limpeza. [cod. 3500000]\n");
    printf("6 - Papelaria. [cod. 3600000]\n");
}

 int main (void){
     //declaracao das variaveis, inicio das arvores e lista encadeada.
    Estoque *J;
    produto *S;
    J = inicio();
    S = criaArvore();
    struct arvore *b;
    int n;
    char cpff[CPF];
    int aux = 0;
    int c = 0;
    int codFinal = 0;
    float p = 0;
    //declaracao de 6 contadores automaticos para o codigo unico para cada produto.
    int contador[6];
        for(int i = 0; i < 6; i++)
                contador[i] = 0;

    do{
        char nome[MAX] = {0};
        menu();
        printf("Digite a opcao: \n");
        scanf("%i", &aux);

        if(aux == 1){
            codigosProdutos();
            printf("Digite o tipo de produto: \n");
            scanf("%d", &c);
            // LAÇO SE IF PARA SELEÇÃO DAS OPÇÕES E CHAMADAS DAS FUNÇÕES, SENDO CADA FUNÇÃO SEGUINDO A ORDEM DO MENU PEDIDO.
            while (c > 6){
            printf("Opcao invalida. \n");
            printf("Digite o tipo de produto: \n");
            scanf("%d", &c);
            }
            if ((c == 1) || (c == 0)){
                ++contador[0];
               codFinal = 310000 + contador[0];

            }
            if (c == 2){
                ++contador[1];
               codFinal = 320000 + contador[1];
            }
            if (c == 3){
                ++contador[2];
               codFinal = 330000 + contador[2];
            }
            if (c == 4){
                ++contador[3];
               codFinal = 340000 + contador[3];
            }
            if (c == 5){
                ++contador[4];
               codFinal = 350000 + contador[4];
            }
            if (c == 6){
                ++contador[5];
               codFinal = 360000 + contador[5];
            }

            fflush(stdin);

            printf("Digite a descricao do produto: (Maximo 1000 letras).\n");
            gets(nome);

            fflush(stdin);


            printf("Digite o preco: \n");
            scanf("%f", &p);
            while (validacao_preco(p) == 0){
                printf("Preco invalido. \n");
                printf("Digite o preco: \n");
                scanf("%f", &p);
            }
            printf("Produto cadastrado.\n");
            printf("\n");
            printf("Codigo do produto: %d\n", codFinal);
            printf("Preco do produto: %f\n", p);
            printf("Descricao do produto: %s\n", nome);
            S = InserirProduto(S, codFinal, p, nome);
            printf("Pressione enter para continuar. \n");
            printf("\n");
            getchar();
        }
        codFinal = 0;
        if (aux == 2){
            printf("Digite o codigo do produto: \n");
            scanf("%d", &codFinal);
            BuscarProduto(S, J, codFinal);
            printf("Pressione enter para continuar. \n");
            printf("\n");
            getchar();
        }
        codFinal = 0;
        if (aux == 3){
        codFinal = 0;
            printf("Digite o codigo do produto: \n");
            scanf("%d", &codFinal);
            if(BuscaProduto(S, codFinal) == NULL){
                printf("Codigo nao encontrado. \n");
                printf("Pressione enter para continuar. \n");
                printf("\n");
                getchar();
            }
            if(BuscaProduto(S, codFinal) != NULL){
                fflush(stdin);

                printf("Digite a descricao do produto: ");
                gets(nome);

                fflush(stdin);

                printf("Digite o preco: \n");
                scanf("%f", &p);

                alterarProduto(S, codFinal, p, nome);

                printf("Pressione enter para continuar. \n");
                printf("\n");
                getchar();
            }

        }
        codFinal = 0;
        if (aux == 4){
            printf("Digite o codigo do produto: \n");
            scanf("%d", &codFinal);
            if (BuscaProduto(S, codFinal) == NULL){
                printf("Produto nao encontrado.\n");

                fflush(stdin);

            }
             if(BuscaProduto(S, codFinal) != NULL){
                S = RemoverProduto(S, codFinal);
                printf("Produto removido do sistema. \n");

                printf("Pressione enter para continuar. \n");
                printf("\n");
                getchar();
             }

        }
        codFinal = 0;
        if(aux == 5){
            ImprimirProduto(S);
        }
        if(aux == 6){
            insere();
        }
        if (aux == 7){
            alteraCliente();
        }
        if (aux == 8){
            remove_p();
        }
        if (aux == 9){
            printf("Digite o codigo do cliente a procurar: \n");
                    scanf("%d", &n);

                    b = buscar(n);

                    if(b){
                        printf("Cliente encontrado:\n COD: %d\n NOME: %s\n CPF: %s\n TELEFONE: %d\n", b->cod, b->nome, b->cpf, b->telefone);

                    }

                    else{
                        printf("Cliente nao encontrado. \n");
                        printf("Pressione enter para continuar. \n");
                        printf("\n");
                        getchar();
                    }

                    b = NULL;
        }
        codFinal = 0;
        if (aux == 10){
            int e = 0;
            printf("Para realizar entrada (1) ou saida (2) de um produto: \n");
            scanf("%i", &e);
            while(e < 1 || e > 2){
                printf("Operacao invalida");
                printf("Para realizar entrada (1) ou saida (2) de um produto: \n");
                scanf("%i", &e);
            }
            if (e == 1){
                printf("Digite o codigo do produto: \n");
                scanf("%d", &codFinal);
                if (BuscaProduto(S, codFinal) != NULL){
                    int quantidade, d, m, an = 0;
                    printf("Digite a quantidade do produto: \n");
                    scanf("%i", &quantidade);
                    printf("Data de insercao: \n");
                    printf("Digite o ano: \n");
                    scanf("%i", &an);
                        while(an < 2000){
                            printf("Ano invalido.\n");
                            printf("Digite o ano: \n");
                            scanf("%i", &an);
                        }
                    printf("Digite o mes: \n");
                    while(m > 12){
                        printf("Mes invalido.\n");
                            printf("Digite o mes: \n");
                            scanf("%i", &m);
                    }
                            printf("Digite o dia: \n");
                            scanf("%i", &d);
                            while ((m == 1 || m == 3 || m==5 || m==7 || m==8 || m==10 || m==12) && (d > 31)){
                                printf("Dia invalido.\n");
                                printf("Digite o dia: \n");
                                scanf("%i", &d);
                            }
                            while ((m == 4 || m == 6 || m==9 || m==11) && (d > 30)){
                                printf("Dia invalido.\n");
                                printf("Digite o dia: \n");
                                scanf("%i", &d);
                            }
                            while((m == 2) && (an % 4 != 0) && (d > 28)){
                                printf("Dia invalido.\n");
                                printf("Digite o dia: \n");
                                scanf("%i", &d);
                            }
                    printf("Produto em estoque. \n");

                    J = EntradaProduto(J, S, quantidade, d, m, an, codFinal);
                }
                else {
                    printf("Codigo nao encontrado. \n");
                    printf("Pressione enter para continuar. \n");
                    printf("\n");
                    getchar();
                }
            }
            if (e == 2){
                printf("Digite o codigo do produto: \n");
                scanf("%d", &codFinal);
                if (BuscaProduto(S, codFinal) != NULL){
                    J = SaidaProduto(J, codFinal);
                }else{
                    printf("Produto nao encontrado. \n");
                    printf("Pressione enter para continuar. \n");
                    printf("\n");
                    getchar();
                }
            }
        }

        if(aux == 11){
            printf("Digite o codigo do produto: \n");
                scanf("%d", &codFinal);
                if (BuscaProduto(S, codFinal) != NULL)
                {
                   ExibirEstoque(J, codFinal);
                   printf("Pressione enter para continuar. \n");
                    printf("\n");
                    getchar();
                }
            else{
                printf("codigo nao encotrado ou inexistente.");
            }
        }
    }
        while((aux < 12) || (aux == 0));
    return 0;
    //EXISTE A UTILIZAÇÃO DE VARIAVEIS AUXILIARES PARA ATRIBUIR EM CADA FUNÇÃO.
 }
//FUNÇÃO PARA ALTERAR CLIENTE, BUSCANDO O CODIGO UNICO DO CLIENTE E ALTERANDO OS VALORES DA ESTRUTURA.
void alteraCliente(){
    struct arvore *P;
    int cod;
    long int tel;
    char name[MAX];
    char cpfs[11];
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cod);
    P = buscar(cod);
    if(P == NULL){
        printf("Cliente nao encontrado. \n");
        return;
    }else{
    fflush(stdin);

    printf("Digite o cpf do cliente a inserir: ");
    gets(cpfs);

    fflush(stdin);
    fflush(stdin);

    printf("Digite o nome a inserir: ");
    gets(name);


    fflush(stdin);

    printf("Digite o telefone do cliente a inserir: ");
    scanf("%d", &tel);

        strcpy(raiz->nome, name);
        strcpy(raiz->cpf, cpfs);
        raiz->telefone = tel;

    }
}
//FUNÇÃO QUE INSERE O CLIENTE.
void insere(){
    struct arvore *aux1 = NULL, *aux2 = NULL, *aux3 = NULL;
    int n;
    char nomeaux[MAX];
    char cpfaux[11];
    long int telaux;

    printf("Digite o codigo do cliente a inserir: ");
    scanf("%d", &n);

    aux3 = buscar(n);
        if(aux3 == NULL){

    fflush(stdin);

    printf("Digite o cpf do cliente a inserir: ");
    gets(cpfaux);

    fflush(stdin);

    printf("Digite o nome a inserir: ");
    gets(nomeaux);


    fflush(stdin);

    printf("Digite o telefone do cliente a inserir: ");
    scanf("%d", &telaux);

        }else{
            printf("Codigo existente de: \n");
            printf("Cliente encontrado:\n COD: %d\n NOME: %s\n TELEFONE: %d\n", aux3->cod, aux3->nome, aux3->telefone);
            printf("CPF: %s \n", aux3->cpf);
            return;
        }
    if(!raiz){
        raiz = (struct arvore*) malloc(sizeof(struct arvore));

        if(!raiz){
            printf("Erro. \n");
            return;
        }

        raiz->cod = n;
        strcpy(raiz->nome, nomeaux);
        strcpy(raiz->cpf, cpfaux);
        raiz->telefone = telaux;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->pai = NULL;

        raiz->fb = 0;
    }

    else{
        aux1 = raiz;
        aux2 = aux1;

        while(aux2){
            if(n < aux2->cod){
                aux2 = aux2->esquerda;

                if(!aux2){
                    aux1->esquerda = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->esquerda){
                        printf("Erro.\n");
                        return;
                    }

                    aux2 = aux1->esquerda;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->cod = n;
                    strcpy(aux2->nome, nomeaux);
                    strcpy(aux2->cpf, cpfaux);
                    aux2->telefone = telaux;
                    break;
                }
                else{
                    aux1 = aux2;
                }
            }

            else{
                aux2 = aux2->direita;

                if(!aux2){
                    aux1->direita = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->direita){
                        printf("Erro.\n");
                        return;
                    }

                    aux2 = aux1->direita;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->cod = n;
                    aux2->telefone = telaux;
                    strcpy(aux2->nome, nomeaux);
                    strcpy(aux2->cpf, cpfaux);

                    break;
                }

                else{
                    aux1 = aux2;
                }
            }
        }
    }

    printf("Cliente cadastrado.\n");
    getchar();

    if(aux2){
        while(aux2){
            aux2->fb = altura(aux2->direita) - altura(aux2->esquerda);

            if(aux2->fb > 1 || aux2->fb < -1){
                aux2 = balanceia(aux2);
            }

            aux2 = aux2->pai;
        }
    }
}
//FUNÇÃO APENAS PARA TESTE DA ÁRVORE AVL, SE QUISER TESTAR A ARVORE, SÓ CHAMAR NA MAIN (NÃO FOI COLOCADA PARA ATINGIR APENAS OS REQUISITOS DE SUPERMERCADO.
void exibir_ordenado(struct arvore *aux){
    if(!raiz){
        printf("Nao existe clientes cadastrados. \n");
        return;
    }

    if(aux){
        exibir_ordenado(aux->esquerda);
        printf(" {COD: %d\n NOME: %s\n CPF: %s\n FB:(%d)\n} ", aux->cod, aux->nome, aux->cpf, aux->fb);
        exibir_ordenado(aux->direita);
    }
}
//FUNÇÃO QUE REMOVE O CLIENTE BUSCANDO O CODIGO UNICO E CHAMANDO A FUNÇÃO PRINCIPAL REMOVER.
void remove_p(){
    struct arvore *aux;
    int n;

    printf("Digite o numero que deseja remover: ");
    scanf("%d", &n);
    getchar();

    aux = buscar(n);

    if(aux){
        remover(aux);
        printf("Cliente removido. \n");
    }

    else{
        printf("O numero nao cadastrado. \n");
    }
}
//FUNÇÃO QUE REMOVE E ORGANIZA A ÁRVORE
void remover(struct arvore *aux){
    struct arvore *aux2, *salva = aux->pai;

    if(aux != raiz){
        if(!aux->esquerda && !aux->direita){
            if(aux->cod < aux->pai->cod){
                aux->pai->esquerda = NULL;
            }
            else{
                aux->pai->direita = NULL;
            }

            free(aux);
        }

        else if(!aux->direita){
            if(aux->cod < aux->pai->cod){
                aux->pai->esquerda = aux->esquerda;
            }
            else{
                aux->pai->direita = aux->esquerda;
            }
            aux->esquerda->pai = aux->pai;
            free(aux);
        }

        else if(!aux->esquerda){
            if(aux->cod < aux->pai->cod){
                aux->pai->esquerda = aux->direita;
            }
            else{
                aux->pai->direita = aux->direita;
            }
            aux->direita->pai = aux->pai;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->cod = aux2->cod;

            remover(aux2);
        }
    }

    else{
        if(!aux->esquerda && !aux->direita){
            free(aux);
            raiz = NULL;
        }

        else if(!aux->direita){
            aux->esquerda->pai = NULL;
            raiz = aux->esquerda;
            free(aux);
        }

        else if(!aux->esquerda){
            aux->direita->pai = NULL;
            raiz = aux->direita;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->cod = aux2->cod;

            remover(aux2);
        }
    }

    if(salva){
        while(salva){
            salva->fb = altura(salva->direita) - altura(salva->esquerda);

            if(salva->fb > 1 || salva->fb < -1){
                salva = balanceia(salva);
            }

            salva = salva->pai;
        }
    }
}
//FUNÇÃO AUXILIAR DA ÁRVORE AVL
struct arvore* menor_direita(struct arvore *aux){
    while(aux->esquerda){
        aux = aux->esquerda;
    }

    return aux;
}
//FUNÇÃO QUE BUSCA O CODIGO UNICO DO CLIENTE,
struct arvore* buscar(int n){
    struct arvore *aux;

    aux = raiz;

    while(aux && aux->cod != n){
        if(n < aux->cod){
            aux = aux->esquerda;
        }

        else{
            aux = aux->direita;
        }
    }

    return aux;
}
//FUNÇÃO LIMPAR ÁRVORE NÃO CHAMADA NA MAIN,
void limpar_arvore(struct arvore *aux){
    if(aux->esquerda){
        limpar_arvore(aux->esquerda);
    }

    if(aux->direita){
        limpar_arvore(aux->direita);
    }

    free(aux);
    raiz = NULL;
}
//FUNÇÃO APENAS PARA TESTE DA ÁRVORE AVL, SE QUISER TESTAR A ARVORE, SÓ CHAMAR NA MAIN (NÃO FOI COLOCADA PARA ATINGIR APENAS OS REQUISITOS DE SUPERMERCADO.
int altura(struct arvore *aux){
    if(!aux){
        return 0;
    }

    int ae = altura(aux->esquerda);
    int ad = altura(aux->direita);

    return (ae > ad) ? ae + 1: ad + 1;
}
//REALIZAR A ORGANIZAÇÃO DA ÁRVORE
struct arvore* rot_direita(struct arvore *aux){
    struct arvore *esq = aux->esquerda;

    aux->esquerda = esq->direita;
    esq->direita = aux;

    if(aux->esquerda){
        aux->esquerda->pai = aux;
    }

    esq->pai = aux->pai;
    aux->pai = esq;

    if(aux == raiz){
        raiz = esq;
    }

    if(esq->pai){
        if(esq->cod < esq->pai->cod){
            esq->pai->esquerda = esq;
        }
        else{
            esq->pai->direita = esq;
        }
    }

    esq->fb = altura(esq->direita) - altura(esq->esquerda);
    aux->fb = altura(aux->direita) - altura(aux->esquerda);

    return esq;
}
//REALIZAR A ORGANIZAÇÃO DA ÁRVORE
struct arvore* rot_esquerda(struct arvore *aux){
    struct arvore *dir = aux->direita;

    aux->direita = dir->esquerda;
    dir->esquerda = aux;

    if(aux->direita){
        aux->direita->pai = aux;
    }

    dir->pai = aux->pai;
    aux->pai = dir;

    if(aux == raiz){
        raiz = dir;
    }

    if(dir->pai){
        if(dir->cod < dir->pai->cod){
            dir->pai->esquerda = dir;
        }
        else{
            dir->pai->direita = dir;
        }
    }

    dir->fb = altura(dir->direita) - altura(dir->esquerda);
    aux->fb = altura(aux->direita) - altura(aux->esquerda);
    return dir;
}
//BALANCEAR A ÁRVORE
struct arvore* balanceia(struct arvore *aux){
    if(aux->fb < -1){
        if(aux->esquerda->fb > 0){
            aux->esquerda = rot_esquerda(aux->esquerda);
        }

        aux = rot_direita(aux);
    }

    else if(aux->fb > 1){
        if(aux->direita->fb < 0){
            aux->direita = rot_direita(aux->direita);
        }

        aux = rot_esquerda(aux);
    }

    return aux;
}
//EXIBIR OS NÍVEIS DA ÁRVORE
void exibir_niveis(struct arvore *aux){
    int i;

    for(i = 0; i <= altura(raiz); i++){
        printf("Nivel %d\n", i);
        exibir_niveis_b(raiz, i, 0);
        printf("\n\n");
    }
}

void exibir_niveis_b(struct arvore *aux, int atual, int cont){
    if(!raiz){
        printf("Cliente vazio. \n");
        getchar();
        return;
    }

    if(aux){
        exibir_niveis_b(aux->esquerda, atual, cont+1);

        if(atual == cont){
            printf("%d ", aux->cod);
        }

        exibir_niveis_b(aux->direita, atual, cont+1);
    }
}
