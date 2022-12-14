#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "graphics.h"
#include "marketSystemTools.h"
#include "AVL.h"

int main(int argc, char const *argv[])
{
    // Configura a página de código de saída do console para UTF-8
    if (!SetConsoleOutputCP(65001))
    {
        system("COLOR 04");
        printf("Erro na configuracao da pagina de saida!\n\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    // Limpa a tela e coloca as cores
    SetConsoleTitleW(L"Mercado da Ju");
    system("cls");
    system("COLOR 70");

    // Salva o handle da saída e entrada do console
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    // Salva o handle da janela do console
    HWND wConsole = GetConsoleWindow();

    // Impossibilita o usuário de redimensionar a janela do jogo
    SetWindowLongPtr(wConsole, GWL_STYLE, GetWindowLong(wConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    // Configura tamanho e fonte do console
    setConsoleFont(hConsoleOut, SPR_FONT);
    setWindowSize(hConsoleOut, SPR_W, SPR_H, true);
    // Esconde o cursor
    hideCursor(hConsoleOut, true);

    // Carrega os sprites na memória
    char *SPR1_OPENING = loadSPR("./sprs/Opening.txt");
    char *SPR2_OPENING = loadSPR("./sprs/Opening2.txt");
    char *SPR3_OPENING = loadSPR("./sprs/Opening3.txt");

    char *SPR_MENU_BG = loadSPR("./sprs/backgd_menu.txt");
    char *SPR_MENU_OPTNS = loadSPR("./sprs/menuOptions.txt");

    char *SPR_FALAS = loadSPR("./sprs/Falas.txt");

    setCmdCursor(0, 0, hConsoleOut);
    showSPR(SPR1_OPENING, 0, -1);
    showFala('1', SPR_FALAS, POS_FALA_X, POS_FALA_Y, hConsoleOut);
    // Animação de mexer a boca
    for (int i = 0; i < 5; i++)
    {
        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR2_OPENING, 60, 64);

        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR1_OPENING, 60, 64);
    }

    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    setCmdCursor(0, 41, hConsoleOut);
    showSPR(SPR3_OPENING, 41, 55);
    showFala('2', SPR_FALAS, POS_FALA_X, POS_FALA_Y, hConsoleOut);
    // Animação de mexer a boca
    for (int i = 0; i < 5; i++)
    {
        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR2_OPENING, 60, 64);

        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR1_OPENING, 60, 64);
    }

    FlushConsoleInputBuffer(hConsoleIn);
    getch();

    // ------------------------------------- Sistema do Mercado -------------------------------------

    // Declaração da árvore
    AVLNodo *mainTree = NULL;

    // Outras variáveis usadas pelo programa
    int maiorQtdeDigs = 0, aux;
    char format[10], usrSelection;

    // Cria a string que será passada para o scanf de leitura do nome do produto
    snprintf(format, sizeof(format), "%%%d[^\n]s", TAM_PROD_STR - 1);

    // Configura a janela para exibir o menu na primeira vez
    system("cls");
    setWindowSize(hConsoleOut, MENU_W, SPR_H, true);
    setWindowSize(hConsoleOut, MENU_W, MENU_H, false);

    // Loop principal
    while (1)
    {
        // Exibe o o background do menu
        setCmdCursor(0, 0, hConsoleOut);
        showSPR(SPR_MENU_BG, 0, -1);
        // Exibe o menu de opções
        showSPRinPos(SPR_MENU_OPTNS, 57, 16, hConsoleOut);

        do
        {
            FlushConsoleInputBuffer(hConsoleIn);
        } while ((usrSelection = getch()) > '9' || usrSelection < '0');

        // Fecha o programa
        if (usrSelection == '0')
        {
            system("cls");

            setWindowSize(hConsoleOut, MENU_W, SPR_H, true);
            setWindowSize(hConsoleOut, SPR_W, SPR_H, false);

            setCmdCursor(0, 0, hConsoleOut);
            showSPR(SPR1_OPENING, 0, -1);

            // Olhinhos fechados
            setCmdCursor(0, 41, hConsoleOut);
            showSPR(SPR3_OPENING, 41, 55);

            // Mostra última fala
            showFala('3', SPR_FALAS, POS_FALA_X, POS_FALA_Y, hConsoleOut);
            // Animação de mexer a boca
            for (int i = 0; i < 5; i++)
            {
                timer(150);

                setCmdCursor(0, 60, hConsoleOut);
                showSPR(SPR2_OPENING, 60, 64);

                timer(150);

                setCmdCursor(0, 60, hConsoleOut);
                showSPR(SPR1_OPENING, 60, 64);
            }

            // Desaloca os sprites
            free(SPR1_OPENING);
            free(SPR2_OPENING);
            free(SPR3_OPENING);
            free(SPR_FALAS);
            free(SPR_MENU_BG);
            free(SPR_MENU_OPTNS);

            // Libera a árvore
            freeTree(mainTree);

            FlushConsoleInputBuffer(hConsoleIn);
            getch();

            exit(EXIT_SUCCESS);
        }

        // Configura o console para a parte do sistema do mercado
        system("cls");
        setConsoleFont(hConsoleOut, MSYSTEM_FONT);
        setWindowSize(hConsoleOut, MSYSTEM_W, MSYSTEM_H, false);
        setCmdCursor(0, 0, hConsoleOut);
        hideCursor(hConsoleOut, false);

        switch (usrSelection)
        {
        // Inserir
        case '1':
            insertOption(&mainTree, format, &maiorQtdeDigs);
            getch();
            break;

        // Listagem vertical
        case '2':
            imprimeArvVertical(mainTree);
            getch();
            break;

        // Listagem de arvore
        case '3':
            imprimePorNivel(mainTree, maiorQtdeDigs);
            getch();
            break;

        // Procurar chave
        case '4':
            searchOption(mainTree);
            getch();
            break;

        // Editar valor de um elemento
        case '5':
            editElementOption(&mainTree, format, &maiorQtdeDigs);
            getch();
            break;

        // Excluir
        case '6':
            deleteOption(&mainTree);
            getch();
            break;

        // Imprime ordenado
        case '7':
            imprimeOrdenado(mainTree);
            printf("\n");
            getch();
            break;

        // Num. elementos na árvore
        case '8':
            printf("Quantidade de elementos na arvore: %d\n", qtdeElementos(mainTree));
            getch();
            break;

        // Altura da árvore
        case '9':
            printf("Altura da arvore: %d\n", alturaArv(mainTree));
            getch();
            break;

        default:
            break;
        }

        // Configura a janela para exibir o menu de novo
        system("cls");
        setConsoleFont(hConsoleOut, SPR_FONT);
        setWindowSize(hConsoleOut, MENU_W, MENU_H, true);
        hideCursor(hConsoleOut, true);
    }

    return 0;
}
