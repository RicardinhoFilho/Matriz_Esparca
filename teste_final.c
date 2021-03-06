// DS130 - T - TRABALHO PRATICO 1
// PROBLEMA 1 – CALCULADORA DE MATRIZ ESPARSA (50 pontos)
// FELIPE M. BETIOLLO E RICARDO PINTO GIASSON
// 21/11/2021

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    float dado;
    int lin, col;
    struct nodo *prox;
} Matriz_Esparsa;

typedef struct matrizes *Lista_Matrizes;

typedef struct matrizes
{
    char nome[1];
    struct Nodos_Matriz *corpo;
    int qtd_l, qtd_c;
    struct matrizes *prox;
} Matrizes_Esparsas;

typedef struct matrizes Matrizes;
typedef struct nodo *Nodos_Matriz;
typedef struct nodo Nodo_Matriz;

//Criar lista de marizes Matrizes_Esparsas
Lista_Matrizes *cria_lista()
{
    Lista_Matrizes *li = (Lista_Matrizes *)malloc(sizeof(Lista_Matrizes)); //reservar memoria para o primeiro no da lista
    if (li != NULL)
    {
        *li = NULL; //Dando ao ultimo elemento da lista o valor de null
        printf("Lista criada de matrizes criada com sucesso!.\n\n");
        return li;
    }
}

//Criar lista de nodos de uma matriz
Nodos_Matriz *cria_lista_nodo()
{
    Nodos_Matriz *li = (Nodos_Matriz *)malloc(sizeof(Nodos_Matriz)); //reservar memoria para o primeiro no da lista
    if (li != NULL)
    {
        *li = NULL; //Dando ao ultimo elemento da lista o valor de null
        printf("Lista de nodos criada com sucesso!.\n\n");
        return li;
    }
}

//Funcao para liberar a lista de matrizes
void libera_lista_matrizes(Lista_Matrizes *li)
{
    Matrizes *no = *li;
    if (li != NULL)
    {
        while ((*li) != NULL)
        {
            no = *li; //no recebe inicio da lista
            Matrizes *nodos = no->corpo;
            libera_nodos(nodos);
            *li = (*li)->prox; //inicio da lista vai apontar para a proxima matriz
            free(no);
        }

        //
        free(li); //libera inicio da lista
    }
    printf("Lista liberada.\n\n");
}

void libera_nodos(Nodos_Matriz *li)
{
    Nodo_Matriz *no = *li;
    while (no != NULL)
    {
        //printf("DADO: %f\n\n\n", no->dado);
        no = no->prox;
        free(no);
    }
}

//função checagem nodo vazio
int lista_vazia(Nodos_Matriz *li)
{

    if (li == NULL) //lista nula
        return 1;

    return 0;
}

//Função para inserir lista de nodo na matriz
int insere_dados_matriz(Lista_Matrizes *li, Nodo_Matriz *corpo, int q_col, int q_lin, char *nome)
{
    if (li == NULL)
        return 0;

    Matrizes *no = (Matrizes *)malloc(sizeof(Matrizes));
    if (no == NULL)
        return 0;
    no->corpo = corpo;
    no->qtd_c = q_col;
    no->qtd_l = q_lin;
    strcpy(no->nome, nome);
    // printf("ESTE É O NOME %s\n\n\n\n\n\n\n",no->nome);
    no->prox = (*li); //Proxima matriz

    *li = no;
    return 1;
}

//Função para criar nodo da listax
int insere_lista_nodo(Nodos_Matriz *li, int lin, int col, float valor)
{
    if (li == NULL)
        return 0;

    Nodo_Matriz *no = (Nodo_Matriz *)malloc(sizeof(Nodo_Matriz));
    if (no == NULL)
        return 0;
    no->col = col;
    no->lin = lin;
    no->dado = valor;

    no->prox = (*li); //Prox nodo
    *li = no;
    return 1;
}

//Buscar Matriz pelo nome
Matrizes *buscaPorNome(Lista_Matrizes *li, char nome[1])
{

    if (li == NULL)
        return 0;

    Matrizes *no = *li;
    //printf("Este aqui ó %s\n\n",nome);
    while (no != NULL && no->nome[0] != nome[0])
    {

        no = no->prox;
    }

    return no;
}

float buscaNodoPorPosicao(Nodos_Matriz *li, int lin, int col)
{

    if (li == NULL)
    {
        return 0;
    }

    Nodo_Matriz *no = *li;

    while (no != NULL && (no->lin != lin || no->col != col))
    {
        // printf("O dado aqui: %f\n\n\n",no->dado);
        no = no->prox;
    }

    if (no == NULL)
    {
        return 0;
    }
    else
    {

        return no->dado;
    }
}

//Imprimir Linhas e Colunas

Matrizes *imprimirMatriz(Matrizes *no)
{
    int l = 0, c = 0;

    printf("Matriz %s: %d x %d\n", no->nome, no->qtd_l, no->qtd_c);

    printf("Matriz Esparsa %s : %d x %d \n", no->nome, no->qtd_l, no->qtd_c);
    for (l = 0; l < no->qtd_l; l++)
    {

        for (c = 0; c < no->qtd_c; c++)
        {

            printf("%.2f  ", buscaNodoPorPosicao(no->corpo, l + 1, c + 1));
        }
        printf("\n");
    }
}

//Listar matrizes
void listar_matrizes(Lista_Matrizes *li)
{

    if (li == NULL)
    {
        printf("Sua lista de matrizes ainda está vazia!\n");
        return 0;
    }

    Matrizes *no = *li;

    while (no != NULL)
    {
        printf("Matriz %s: %d x %d\n", no->nome, no->qtd_l, no->qtd_c);

        no = no->prox;
    }
}

//Gerar matriz transposta
int gerar_transposta(Lista_Matrizes *li, Nodos_Matriz *corpo, int lin, int col, char nome[1])
{

    if (li == NULL)
    {

        return 0;
    }

    Nodo_Matriz *no_nodo = *corpo;
    struct Nodos_Matriz *li_nodo = cria_lista_nodo();
    while (no_nodo != NULL)
    {
        insere_lista_nodo(li_nodo, no_nodo->col, no_nodo->lin, no_nodo->dado);
        no_nodo = no_nodo->prox;
    }

    insere_dados_matriz(li, li_nodo, lin, col, nome);
    return 1;
};

int somar_matrizes(Lista_Matrizes *li, Nodos_Matriz *corpo1, Nodos_Matriz *corpo2, char nome[1], int linhas, int colunas)
{
    int l, c;

    struct Nodos_Matriz *li_nodo = cria_lista_nodo();
    printf("%d x %d", linhas, colunas);
    for (l = 0; l < linhas; l++)
    {
        for (c = 0; c < colunas; c++)
        {

            float valor1 = buscaNodoPorPosicao(corpo1, l + 1, c + 1);
            float valor2 = buscaNodoPorPosicao(corpo2, l + 1, c + 1);

            if ((valor1 + valor2) != 0)
            {

                insere_lista_nodo(li_nodo, l + 1, c + 1, valor1 + valor2);
            }
        }
    }

    insere_dados_matriz(li, li_nodo, colunas, linhas, nome);
    return 1;
}

int subtrair_matrizes(Lista_Matrizes *li, Nodos_Matriz *corpo1, Nodos_Matriz *corpo2, char nome[1], int linhas, int colunas)
{
    int l, c;

    struct Nodos_Matriz *li_nodo = cria_lista_nodo();
    printf("%d x %d", linhas, colunas);
    for (l = 0; l < linhas; l++)
    {
        for (c = 0; c < colunas; c++)
        {

            float valor1 = buscaNodoPorPosicao(corpo1, l + 1, c + 1);
            float valor2 = buscaNodoPorPosicao(corpo2, l + 1, c + 1);

            if ((valor1 - valor2) != 0)
            {

                insere_lista_nodo(li_nodo, l + 1, c + 1, valor1 - valor2);
            }
        }
    }

    insere_dados_matriz(li, li_nodo, colunas, linhas, nome);
    return 1;
}

int multiplicar_matrizes(Lista_Matrizes *li, Matrizes *primeira, Matrizes *segunda, char nome[1])
{
    int lin, col, x;
    float soma = 0, valor_P, valor_S;
    if (primeira->qtd_c != segunda->qtd_l)
    {

        printf("Não é possivel multiplar uma matriz %dx%d por uma %dx%d", primeira->qtd_l, primeira->qtd_c, segunda->qtd_l, segunda->qtd_c);
        return 0;
    }

    struct Nodos_Matriz *li_nodo = cria_lista_nodo();

    Nodo_Matriz *pri_nodo = primeira->corpo;
    Nodo_Matriz *seg_nodo = segunda->corpo;

    for (lin = 0; lin < primeira->qtd_l; lin++)
    {
        for (col = 0; col < segunda->qtd_c; col++)
        {

            for (x = 0; x < segunda->qtd_c + 1; x++)
            {
                float valor1 = buscaNodoPorPosicao(pri_nodo, lin + 1, x + 1);
                float valor2 = buscaNodoPorPosicao(seg_nodo, x + 1, col + 1);
                soma = valor1 * valor2 + soma;

                // printf("%.2f*%.2f = %.2f + ", valor1, valor2, soma);
            }
            if (soma != 0)
                insere_lista_nodo(li_nodo, lin + 1, col + 1, soma);
            //printf("\n Soma: %f\n", soma);

            soma = 0;
        }
    }

    insere_dados_matriz(li, li_nodo, primeira->qtd_l, segunda->qtd_c, nome);
    return 1;
}
int imprimir_diagonal_principal(Matrizes *matriz)
{
    int lin;
    float valor;
    if (matriz->qtd_c != matriz->qtd_l)
    {

        printf("Não é possivel capturar a dioagonal principal de uma matriz %dx%d!\n\n", matriz->qtd_c, matriz->qtd_l);
        return 0;
    }

    Nodo_Matriz *nodos = matriz->corpo;
    printf("Diagonal Principal:[");
    for (lin = 0; lin < matriz->qtd_l; lin++)
    {
        valor = buscaNodoPorPosicao(nodos, lin + 1, lin + 1);

        printf(" %.2f, ", valor);
    }
    printf("]\n\n");

    return 1;
}

int main()
{

    int entrada, entrada2, linhas, colunas, posicao_li, posicao_col;
    char nome[1];
    float valor;
    struct nodo Nodos_Matriz;
    Lista_Matrizes *li;
    li = cria_lista();
    while (entrada != 12)
    {
        printf("\n1) Criar Matriz Esparsa\n2)Listar Matrizes\n3)Imprimir Matriz\n4)Gerar matriz transposta\n5)Somar Matrizes\n6)Subtrair Matrizes\n7)Multiplicar Matrizes\n8)Buscar diagonal Principal\n9)Liberar matrizes\n10)Finalizar Programa\n\n");
        scanf(" %d", &entrada);

        switch (entrada)
        {

        case 1:
        {
            printf("Qual o tipo da matriz que você deseja criar?\n");
            printf("Numero de linhas:");
            scanf(" %d", &linhas);
            printf("Numero de colunas:");
            scanf(" %d", &colunas);
            printf("Defina o nome de sua Matriz:");
            scanf("%s", &nome[0]);

            struct Nodos_Matriz *li_nodo = cria_lista_nodo();
            Nodo_Matriz *aux = li_nodo;

            while (entrada2 != 2)
            {
                printf("1) Inserir elemento ao nodo:\n2) Finalizar criação da Matriz Esparsa %s:\n", nome);
                scanf(" %d", &entrada2);

                switch (entrada2)
                {
                case 1:
                {

                    printf("Defina a posição de seu nodo: \n");
                    printf("Linha: ");
                    scanf(" %d", &posicao_li);

                    printf("Coluna: ");
                    scanf(" %d", &posicao_col);

                    printf("Defina o valor do nodo: \n");
                    scanf(" %f", &valor);
                    if (posicao_col <= 0 || posicao_col > colunas)
                    {
                        printf("Posição da coluna inválida!\n");
                    }
                    else if (posicao_li <= 0 || posicao_li > linhas)
                    {
                        printf("Posição da linha inválida!\n");
                    }
                    else if (valor == 0)
                    {
                        printf("Nodos de valor zero não precisam ser inseridos!\n");
                    }
                    else
                    {
                        insere_lista_nodo(li_nodo, posicao_li, posicao_col, valor);
                    }

                    break;
                }

                case 2:
                {
                    insere_dados_matriz(li, aux, colunas, linhas, nome);
                    break;
                }
                }
            }
            entrada2 = 0;
            break;
        }

        case 2:
        {

            listar_matrizes(li);
            break;
        }

        case 3:
        {
            printf("Qual matriz deseja visualizar?");
            scanf("%s", &nome[0]);
            Matrizes *teste = buscaPorNome(li, nome);
            imprimirMatriz(teste);

            break;
        }

        case 4:
        {
            printf("Deseja gerar a matriz transposta de qual matriz?");
            scanf("%s", &nome[0]);
            Matrizes *teste = buscaPorNome(li, nome);
            printf("Como deseja chamar esta matriz?");
            scanf("%s", &nome[0]);
            gerar_transposta(li, teste->corpo, teste->qtd_l, teste->qtd_c, nome);
            break;
        }
        case 5:
        {
            printf("Qual matrizes deseja somar?\n");
            printf("Primeira Matriz?");
            scanf("%s", &nome[0]);
            Matrizes *primeira = buscaPorNome(li, nome);

            printf("Segunda Matriz?\n");
            scanf("%s", &nome[0]);
            Matrizes *segunda = buscaPorNome(li, nome);

            if (primeira->qtd_c != segunda->qtd_c || segunda->qtd_l != primeira->qtd_l)
            {

                printf("Infelimente não é possível somar uma matriz %dx%d com uma %dx%d", primeira->qtd_l, primeira->qtd_c, segunda->qtd_l, segunda->qtd_c);
            }
            else
            {

                printf("Qual o nome da matriz que deseja gerar? ");
                scanf("%s", &nome[0]);

                somar_matrizes(li, primeira->corpo, segunda->corpo, nome, primeira->qtd_l, segunda->qtd_c);
            }
            break;
        }

        case 6:
        {
            printf("Qual matrizes deseja subtrair?\n");
            printf("Primeira Matriz?");
            scanf("%s", &nome[0]);
            Matrizes *primeira = buscaPorNome(li, nome);

            printf("Segunda Matriz?\n");
            scanf("%s", &nome[0]);
            Matrizes *segunda = buscaPorNome(li, nome);

            if (primeira->qtd_c != segunda->qtd_c || segunda->qtd_l != primeira->qtd_l)
            {

                printf("Infelimente não é possível somar uma matriz %dx%d com uma %dx%d", primeira->qtd_l, primeira->qtd_c, segunda->qtd_l, segunda->qtd_c);
            }
            else
            {

                printf("Qual o nome da matriz que deseja gerar? ");
                scanf("%s", &nome[0]);

                subtrair_matrizes(li, primeira->corpo, segunda->corpo, nome, primeira->qtd_l, segunda->qtd_c);
            }

            break;
        }

        case 7:
        {
            printf("Qual matrizes deseja multiplicar?\n");
            printf("Primeira Matriz?");
            scanf("%s", &nome[0]);
            Matrizes *primeira = buscaPorNome(li, nome);

            printf("Segunda Matriz?\n");
            scanf("%s", &nome[0]);
            Matrizes *segunda = buscaPorNome(li, nome);

            printf("Qual o nome da matriz que deseja gerar? ");
            scanf("%s", &nome[0]);
            multiplicar_matrizes(li, primeira, segunda, nome);

            break;
        }

        case 8:
        {

            printf("Qual matrizes deseja visualizar a diagonal principal?\n");
            scanf("%s", &nome[0]);
            Matrizes *matriz = buscaPorNome(li, nome);
            imprimir_diagonal_principal(matriz);
            break;
        }

        case 9:
        {

            libera_lista_matrizes(li);
            break;
        }

        case 10:
        {

            libera_lista_matrizes(li);
            entrada = 12;
            break;
        }
        }
    }
}