// DS130 - T - TRABALHO PRATICO 1
// PROBLEMA 2 – ROTAS DE ÔNIBUS (50 pontos)
// FELIPE M. BETIOLLO E RICARDO PINTO GIASSON
// 21/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO 10

typedef struct cidadesRota Cidade;

struct cidadesRota
{
    int indice;
    char nome[25];
    char descricao[25];
    Cidade *proxima;
    Cidade *anterior;
};

struct cidadesRota *rotas[TAMANHO_MAXIMO];

Cidade *inicio;
Cidade *fim;
Cidade *aloca(int indice, char nome[], char descricao[]);
Cidade *inserirCidade(int indice, char nome[], char descricao[]);
void inicializarRota();
void inicializarListaDeRotas();
void removerRota();
void imprimeQuebra();
void imprimirLocalizacao();

void inicializarRota()
{
    inicio = NULL;
    fim = NULL;
}

void inicializarListaDeRotas()
{
    for (int i = 0; i < TAMANHO_MAXIMO; i++)
    {
        rotas[i] = 0;
    }
}

int verificarListaDeRotasCheia()
{
    int cheia = 1;
    for (int i = 0; i < TAMANHO_MAXIMO; i++)
    {
        if (rotas[i] == 0)
        {
            cheia = 0;
            break;
        }
    }

    return cheia;
}

Cidade *aloca(int indice, char nome[], char descricao[])
{
    Cidade *novaCidade = (Cidade *)malloc(sizeof(Cidade));

    novaCidade->indice = indice;
    strncpy(novaCidade->nome, nome, sizeof(novaCidade->nome));
    strncpy(novaCidade->descricao, descricao, sizeof(novaCidade->descricao));
    novaCidade->proxima = NULL;
    novaCidade->anterior = NULL;

    return novaCidade;
}

Cidade *inserirCidade(int indice, char nome[], char descricao[])
{
    Cidade *novo = aloca(indice, nome, descricao);
    if (inicio == NULL)
    {
        inicio = novo;
        fim = novo;
    }
    else
    {
        Cidade *atual;
        atual = fim;
        novo->anterior = atual;
        atual->proxima = novo;
        fim = novo;
    }
}

void imprimeQuebra()
{
    printf("\n\n----------------------------------------------------------------------\n\n");
}

void imprimirLocalizacao(Cidade *cidade)
{
    if (cidade->anterior == NULL)
    {
        printf("Cidade anterior: ---\n");
    }
    else
    {
        printf("Cidade anterior: %s, '%s'\n", cidade->anterior->nome, cidade->anterior->descricao);
    }

    printf("Cidade atual: %s, '%s'\n", cidade->nome, cidade->descricao);

    if (cidade->proxima == NULL)
    {
        printf("Cidade seguinte: ---\n");
    }
    else
    {
        printf("Cidade seguinte: %s, '%s'\n\n", cidade->proxima->nome, cidade->proxima->descricao);
    }
}

void removerRota(int codigoRota)
{
    rotas[codigoRota] = 0;
}

int main()
{
    char nome[25], descricao[25];
    char temp, sempre = '-';

    int sair = 0;
    int valorNome, valorDescricao, opcaoGeral, opcaoRota, codigoRota, contadorCidades, visualizarRota, codigoRotaCriada;

    inicializarListaDeRotas(rotas);

    Cidade *cidade;

    while (sair != 1)
    {
        printf("SELECIONE\n1. Cadastrar Rota\n2. Excluir Rota\n3. Visualizar Rota\n4. Sair\n");
        scanf("%d", &opcaoGeral);
        switch (opcaoGeral)
        {
        case 1:
            system("cls");

            if (verificarListaDeRotasCheia() == 1)
            {
                printf("\nLista de rotas cheia, exclua uma rota existente e tente novamente. Pressione ENTER para continuar.\n");
                getch();
                system("cls");
                break;
            }

            do
            {
                printf("Informe o codigo da rota que sera criada (1 a 10) ou -1 para cancelar\n");
                scanf("%d", &codigoRotaCriada);

                if (codigoRotaCriada == -1)
                {
                    break;
                }
                else if (codigoRotaCriada < 1 || codigoRotaCriada > TAMANHO_MAXIMO)
                {
                    printf("\nCodigo invalido, tente outro\n\n");
                }
                else if (rotas[codigoRotaCriada - 1] != 0)
                {
                    printf("\nCodigo ja esta sendo utilizado, tente outro\n\n");
                }
                else
                {
                    break;
                }
            } while (sempre);

            system("cls");

            if (codigoRotaCriada == -1)
            {
                break;
            }

            inicializarRota();

            valorNome = 0;
            valorDescricao = 0;
            contadorCidades = 1;

            inserirCidade(0, "Curitiba", "A capital Paranense");

            while (sempre)
            {
                printf("Digite o nome da %da cidade da rota (%d) (-1 para finalizar)\n", contadorCidades + 1, codigoRotaCriada);
                scanf("%c", &temp);
                scanf("%[^\n]", nome);
                sscanf(nome, "%d", &valorNome);

                if (valorNome == -1)
                {
                    break;
                }

                printf("Digite a descricao da %da cidade da rota (%d) (-1 para finalizar)\n", contadorCidades + 1, codigoRotaCriada);
                scanf("%c", &temp);
                scanf("%[^\n]", descricao);
                sscanf(descricao, "%d", &valorDescricao);

                if (valorDescricao == -1)
                {
                    break;
                }

                inserirCidade(contadorCidades, nome, descricao);

                contadorCidades++;

                printf("\nCidade cadastrada na rota");

                imprimeQuebra();
            }

            if (contadorCidades > 1)
            {
                rotas[codigoRotaCriada - 1] = inicio;
            }

            system("cls");
            break;

        case 2:
            system("cls");

            printf("Informe o codigo da rota que deseja excluir\n");
            scanf("%d", &codigoRota);

            codigoRota = codigoRota - 1;

            if (rotas[codigoRota] == 0)
            {
                printf("\nEssa rota nao existe. Pressione ENTER para continuar.\n");
                getch();
                system("cls");
                break;
            }

            removerRota(codigoRota);

            printf("\n\nRota removida. Pressione ENTER para continuar");
            getch();
            system("cls");

            break;

        case 3:
            system("cls");

            printf("Informe o codigo da rota que deseja visualizar\n");
            scanf("%d", &codigoRota);

            codigoRota = codigoRota - 1;

            cidade = rotas[codigoRota];

            if (cidade == 0)
            {
                printf("\nEssa rota nao existe. Pressione ENTER para continuar.\n\n");
                getch();
                system("cls");
                break;
            }

            visualizarRota = 1;

            printf("\nVoce agora esta visualizando a rota (%d)\n\n", codigoRota + 1);

            while (visualizarRota == 1)
            {
                imprimirLocalizacao(cidade);

                printf("1. Retornar para a cidade anterior\n2. Avancar para a cidade seguinte\n3. Sair da visualizacao de rota\n");
                scanf("%d", &opcaoRota);

                switch (opcaoRota)
                {
                case 1:
                    if (cidade->anterior == NULL)
                    {
                        printf("\nVoce ja esta na primeira cidade da rota\n");
                        sleep(1);
                    }
                    else
                    {
                        printf("\nRetornando...\n");
                        sleep(1);
                        cidade = cidade->anterior;
                    }

                    imprimeQuebra();
                    break;

                case 2:
                    if (cidade->proxima == NULL)
                    {
                        printf("\nVoce ja esta na ultima cidade da rota\n");
                        sleep(1);
                    }
                    else
                    {
                        printf("\nAvancando...\n");
                        sleep(1);
                        cidade = cidade->proxima;
                    }

                    imprimeQuebra();
                    break;

                case 3:
                    visualizarRota = 0;
                    system("cls");
                    break;
                }
            }

            break;

        case 4:
            sair = 1;
            break;
        }
    }
}