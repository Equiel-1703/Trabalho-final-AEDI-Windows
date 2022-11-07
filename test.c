#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT FontFamily;
    UINT FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);

#define SPR_FONT 8

// Carrega um sprite de texto na memória
char *loadSPR(const char *arquivo)
{
    FILE *fp;

    if ((fp = fopen(arquivo, "r")) == NULL)
    {
        system("COLOR 04");
        printf("\nErro na leitura dos sprites!\n\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    // Ajusta o cursor de leitura para a linha de começo
    fseek(fp, 0, SEEK_END);
    int sizeOfFile = ftell(fp);
    rewind(fp); // Volta pro começo

    char *buffer = (char *)malloc((sizeOfFile * sizeof(char)) + 1);
    char c;
    int i = 0;
    while ((c = getc(fp)) != EOF)
    {
        buffer[i] = c;
        i++;
    }

    fclose(fp);
    return buffer;
}

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
    SetConsoleTitle("Testes gráficos");
    system("cls");
    system("COLOR 70");

    /*

    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Configura a fonte do console
    CONSOLE_FONT_INFOEX conFont;
    conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    conFont.nFont = 0;
    conFont.dwFontSize.X = 0;
    conFont.dwFontSize.Y = SPR_FONT;
    conFont.FontFamily = FF_DONTCARE;
    conFont.FontWeight = FW_NORMAL;
    wcscpy(conFont.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsoleOut, FALSE, &conFont);

    */

    char *SPR1 = loadSPR("./mainMenu_itemsDesc.txt");

    printf("%s", SPR1);
    getchar();

    return 0;
}
