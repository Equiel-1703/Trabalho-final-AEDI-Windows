#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "graphics.h"

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
    SetConsoleTitleW(L"Testes gráficos");
    system("cls");
    system("COLOR 70");

    // Salva o handle da saída do console
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND wConsole = GetConsoleWindow();

    // Impossibilita o usuário de redimensionar a janela do jogo
    SetWindowLongPtr(wConsole, GWL_STYLE, GetWindowLong(wConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    setConsoleFont(hConsoleOut, SPR_FONT);
    setWindowSize(hConsoleOut, SPR_W, SPR_H, true);
    hideCursor(hConsoleOut, true);

    char *SPR1_INIT = loadSPR("./sprs/Opening.txt");
    char *SPR2_INIT = loadSPR("./sprs/Opening2.txt");
    char *FALAS = loadSPR("./sprs/Falas.txt");

    setCmdCursor(0, 0, hConsoleOut);
    showSPR(SPR1_INIT, 0);
    showFala('1', FALAS, POS_FALA_X, POS_FALA_Y, hConsoleOut);
    for (int i = 0; i < 5; i++)
    {
        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR2_INIT, 60);

        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR1_INIT, 60);
    }

    getch();

    showFala('2', FALAS, POS_FALA_X, POS_FALA_Y, hConsoleOut);
    for (int i = 0; i < 5; i++)
    {
        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR2_INIT, 60);

        timer(150);

        setCmdCursor(0, 60, hConsoleOut);
        showSPR(SPR1_INIT, 60);
    }

    getchar();

    return 0;
}
