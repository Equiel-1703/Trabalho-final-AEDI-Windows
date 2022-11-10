#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------- Funções auxiliares do sistema ----------------------------------------

// Essa função apenas limpa o buffer da stdin
void cleanBuff()
{
    while (getchar() != '\n')
    {
        continue;
    }
}

// Obtém a quantidade de digitos de um numero
int getQtdeDigts(unsigned int num)
{
    int qtde = 1;
    while (num > 9)
    {
        qtde++;
        num /= 10;
    }
    return qtde;
}

// Essa função lê e valida um inteiro positivo
void readUnsInteger(unsigned int *num)
{
    while (1)
    {
        if (scanf("%u", num) == 1 && (int)*num >= 0)
            break;

        cleanBuff();
        printf("Valor invalido!\nInsira outro: ");
    }

    cleanBuff();
}

// Essa função lê e valida um float positivo
void readFloat(float *preco)
{
    while (1)
    {
        if (scanf("%f", preco) == 1 && *preco >= 0)
            break;

        cleanBuff();
        printf("Preco invalido!\nInsira outro: ");
    }

    cleanBuff();
}

// Retorna a resposta do usuário em perguntas de sim e nao
int simNaoPrompt()
{
    char c;
    while (1)
    {
        c = getchar();
        cleanBuff();

        switch (c)
        {
        case 's':
        case 'S':
            return 1;

        case 'n':
        case 'N':
            return 0;

        default:
            printf("\nResposta invalida!\nPor favor, tente de novo: ");
            break;
        }
    }
}

// -------------------- Variáveis globais usadas pelo sistema --------------------
unsigned int usrKey;
float preco;
char nomeProd[TAM_PROD_STR];
int aux;

AVLNodo *el;

// ---------------------------------------- Funções do sistema ----------------------------------------
void insertOption(AVLNodo *tree, char *format, int *maiorQtdeDigs)
{
    while (1)
    {
        printf("Chave: ");
        readUnsInteger(&usrKey);
        if (usrKey == 0)
        {
            printf("Valor invalido!\n");
            getchar();
            break;
        }
        else // Valida elemento repetido
        {
            if (buscarEl(tree, usrKey))
            {
                printf("\nEsta chave ja existe! Insira outra.\n\n");
                continue;
            }
            break;
        }
    }

    printf("Preco do produto: ");
    readFloat(&preco);

    printf("Nome do produto: ");
    scanf(format, nomeProd);
    cleanBuff();

    // Atualiza o valor da maior quantidade de dígitos nas chaves da árvore
    int aux = getQtdeDigts(usrKey);
    *maiorQtdeDigs = (aux > *maiorQtdeDigs) ? aux : *maiorQtdeDigs;

    // printf("\nQtde digitos: %d\n", maiorQtdeDigs);

    if (incluir(&tree, usrKey, preco, nomeProd))
        printf("\nFeito!\n");
}

void searchOption(AVLNodo *tree)
{
    printf("Digite uma chave para buscar: ");
    readUnsInteger(&usrKey);

    el = buscarEl(tree, usrKey);
    printf("\n");

    if (el)
        imprimeEl(el);
    else
        printf("Elemento nao encontrado.\n");
}

void editElementOption(AVLNodo *tree, char *format, int *maiorQtdeDigs)
{
    printf("Informe a chave do elemento que deseja editar: ");
    readUnsInteger(&usrKey);

    // Remove o elemento a ser editado
    el = removeNodo(&tree, usrKey);

    if (el)
    {
        printf("\n");

        // Exibe para o usuário o elemento que ele está editando
        imprimeEl(el);

        // Salva as informações do elemento
        usrKey = getElKey(el);
        preco = getElPrice(el);
        strncpy(nomeProd, getElName(el), TAM_PROD_STR * sizeof(char));

        // Apaga o elemento da memoria
        free(el);

        // Nova chave
        printf("\nDeseja alterar a chave? s/n\n");
        if (simNaoPrompt())
        {
            while (1)
            {
                printf("Chave: ");
                readUnsInteger(&usrKey);
                if (usrKey == 0)
                {
                    printf("Valor invalido! Tente novamente.\n");
                    getchar();
                    continue;
                }
                else // Valida elemento repetido
                {
                    if (buscarEl(tree, usrKey))
                    {
                        printf("\nEsta chave ja existe! Insira outra.\n\n");
                        continue;
                    }
                    break;
                }
            }

            // Atualiza o valor da maior quantidade de dígitos nas chaves da árvore
            aux = getQtdeDigts(usrKey);
            *maiorQtdeDigs = (aux > *maiorQtdeDigs) ? aux : *maiorQtdeDigs;

            // printf("\nQtde digitos: %d\n", maiorQtdeDigs);
        }

        // Novo preco
        printf("Deseja alterar o preco? s/n\n");
        if (simNaoPrompt())
        {
            printf("Preco do produto: ");
            readFloat(&preco);
        }

        // Novo nome
        printf("Deseja alterar o nome do produto? s/n\n");
        if (simNaoPrompt())
        {
            printf("Nome do produto: ");
            scanf(format, nomeProd);
            cleanBuff();
        }

        // Insere o elemento editado
        if (incluir(&tree, usrKey, preco, nomeProd))
            printf("\nFeito!\n");
    }
    else
        printf("\nO elemento nao existe.\n");
}

void deleteOption(AVLNodo *tree)
{
    printf("Digite uma chave para excluir: ");
    readUnsInteger(&usrKey);

    el = removeNodo(&tree, usrKey);

    if (el)
    {
        printf("\nElemento removido: \n");
        imprimeEl(el);
        free(el);
    }
}