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
    struct nodo corpo;
    int qtd_l, qtd_c;
    struct matrizes *prox;
} Matrizes_Esparsas;


typedef struct matrizes Matrizes;
typedef struct nodo *Nodo_Matriz;
typedef struct nodo Nodos_Matriz;

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
Nodo_Matriz *cria_lista_nodo()
{
    Nodo_Matriz *li = (Nodo_Matriz *)malloc(sizeof(Nodo_Matriz)); //reservar memoria para o primeiro no da lista
    if (li != NULL)
    {
        *li = NULL; //Dando ao ultimo elemento da lista o valor de null
        printf("Lista de nodos criada com sucesso!.\n\n");
        return li;
    }
}

//Funcao para liberar a lista de matrizes
void libera_lista(Lista_Matrizes *li)
{ //7
    if (li != NULL)
    {
        Nodos_Matriz *no;
        while ((*li) != NULL)
        {
            no = *li;          //no recebe inicio da lista
            *li = (*li)->prox; //inicio da lista vai apontar para a proxima matriz
            free(no);
        }
        free(li); //libera inicio da lista
    }
    printf("Lista liberada.\n\n");
}

//função checagem nodo vazio
int lista_vazia(Nodo_Matriz *li)
{

    if (li == NULL) //lista nula
        return 1;
    if (*li == NULL) //primeiro elemento apontando pra null
        return 1;
    return 0;
}

//Função para inserir lista de nodo na matriz
int insere_dados_matriz(Lista_Matrizes *li, Nodos_Matriz corpo, int q_col, int q_lin, char *nome)
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
    printf("ESTE É O NOME %s\n\n\n\n\n\n\n",no->nome);
    no->prox = (*li);

    *li = no;
    return 1;
}

//Função para criar nodo da listax
int insere_lista_nodo(Nodo_Matriz *li, int lin, int col, float valor)
{
    if (li == NULL)
        return 0;

    Nodos_Matriz *no = (Nodos_Matriz *)malloc(sizeof(Nodos_Matriz));
    if (no == NULL)
        return 0;
    no->col = col;
    no->lin = lin;
    no->dado = valor;

    no->prox = (*li);
    *li = no;
    return 1;
}

//Buscar Matriz pelo nome

Matrizes* buscaPorNome(Lista_Matrizes *li, char nome[1])
{

    if (li == NULL)
        return 0;

    Matrizes *no = *li;
 printf("Este aqui ó %s\n\n",nome);
    while (no != NULL && no->nome[0] != nome[0])
    {   
        printf("ATENÇÃO!!!");
         printf("%s",no->nome);
        printf("%d  \n", no->qtd_c);
         printf("%d  \n", no->qtd_l);

        
        no = no->prox;
    }

    return no;
}

int main()
{

    int entrada, entrada2, linhas, colunas, posicao_li, posicao_col;
    char nome[1];
    float valor;
    struct nodo nodo_matriz;
    Lista_Matrizes *li;
    li = cria_lista();
    while (entrada != 12)
    {
        printf("1) Criar Matriz Esparsa\n");
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

            struct Nodo_Matriz *li_nodo = cria_lista_nodo();
            Nodos_Matriz *aux = li_nodo;

            while (entrada2 != 2)
            {
                printf("1) Inserir elemento ao nodo:\n2) Finalizar criação da Matriz Esparsa %s:\n", nome);
                scanf(" %d", &entrada2);

                switch (entrada2)
                {
                case 1:
                {

                    printf("Defina a posição de seu dado: \n");
                    printf("Linha: ");
                    scanf(" %d", &posicao_li);

                    printf("Coluna: ");
                    scanf(" %d", &posicao_col);

                    printf("Defina o valor do nodo: \n");
                    scanf(" %f", &valor);
                    if (posicao_col < 0 || posicao_col > colunas)
                    {
                        printf("Posição da coluna inválida!\n");
                    }
                    else if (posicao_li < 0 || posicao_li > linhas)
                    {
                        printf("Posição da linha inválida!\n");
                    }
                    else
                    {
                        insere_lista_nodo(li_nodo, posicao_li, posicao_col, valor);
                    }

                    break;
                }

                case 2:
                {
                    insere_dados_matriz(li, *aux, colunas, linhas, nome);
                    
                }
                }
            }
            entrada2 = 0;
            break;
        }

        case 2:
        {   
            printf("Qual matriz deseja buscal:");
            scanf("%s", &nome[0]);
            Matrizes *teste = buscaPorNome(li, nome);

            printf(" se pa deu certo olhe %s", teste->nome);
        }
        }
    }
}
