#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Carrega um sprite de texto na memória
char *loadSPR(const char *arquivo)
{
    FILE *fp;

    if ((fp = fopen(arquivo, "r")) == NULL)
    {
        system("COLOR 04");
        printf("\nErro na leitura do arquivo!\n\n");
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    // Salva o tamanho do arquivo
    fseek(fp, 0, SEEK_END);
    size_t sizeOfFile = ftell(fp);

    // Volta pro começo
    rewind(fp);

    // Cria um buffer do tamanho do arquivo + 1 (para o \0)
    char *buffer = (char *)malloc((sizeOfFile * sizeof(char)) + 1);

    // Lê o arquivo inteiro e salva no buffer
    char c;
    int i = 0;
    while ((c = getc(fp)) != EOF)
    {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';

    // Fecha o arquivo e retorna o buffer
    fclose(fp);
    return buffer;
}

// Mostra alguma fala na tela em dada posição
void showFala(char falaNum, char *falaStr, int posX, int posY, HANDLE hConsoleOut)
{
    int i = 0, tam = strlen(falaStr), origPosX = posX;

    while (falaStr[i] != falaNum && i < tam)
        i++;

    if (i == tam)
    {
        printf("\nFala não encontrada!\n");
        return;
    }

    i++; // pula o primeiro \n

    while (falaStr[++i] != falaNum + 1 && i < tam)
    {
        setCmdCursor(posX, posY, hConsoleOut);

        if (falaStr[i] != '\n')
        {
            putc(falaStr[i], stdout);
            posX++;
        }
        else
        {
            posY++;
            posX = origPosX;
        }
    }
}

// Mostra um sprite a partir de determinada linha até outra dada linha. AS LINHAS COMEÇAM EM 0!!
void showSPR(char *SPR, int lineStart, int lineEnd)
{
    if (lineStart > lineEnd && lineEnd != -1)
    {
        printf("Linhas de início e fim inválidas!!\n");
        getchar();
        return;
    }

    int tamSPR = strlen(SPR); // Lembrando que strlen ignora o \0
    int startIndex = 0, endIndex = 0;

    // Aqui ele encontra o índice da linha que vai começar a imprimir
    if (lineStart > 0)
    {
        int i = 0;

        for (; startIndex < tamSPR && i != lineStart; startIndex++)
        {
            if (SPR[startIndex] == '\n')
                i++;
        }
    }

    if (lineEnd != -1)
    {
        int numLines = lineEnd - lineStart;
        endIndex = startIndex;

        while (numLines >= 0 && endIndex < tamSPR)
        {
            if (SPR[endIndex] == '\n')
                numLines--;

            endIndex++;
        }

        fwrite(SPR + startIndex, sizeof(char), endIndex - startIndex, stdout);
    }
    else
        fwrite(SPR + startIndex, sizeof(char), tamSPR - startIndex, stdout);
}

// --------------------------------------------------- Manipulação do Console ---------------------------------------------------

// Configura a fonte do console
void setConsoleFont(HANDLE hConsoleOut, int fontSize)
{
    CONSOLE_FONT_INFOEX conFont;
    conFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    conFont.nFont = 0;
    conFont.dwFontSize.X = 0;
    conFont.dwFontSize.Y = fontSize;
    conFont.FontFamily = FF_DONTCARE;
    conFont.FontWeight = FW_NORMAL;
    wcscpy(conFont.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsoleOut, FALSE, &conFont);
}

// Configura fonte e tamanho da janela de forma prática
void setWindowSize(HANDLE hConsole, int BufferX, int BufferY, bool Aumenta)
{
    // Configura o tamanho da janela
    COORD buffer_size;
    SMALL_RECT screen_size;

    buffer_size.X = BufferX;
    buffer_size.Y = BufferY;

    screen_size.Left = 0;
    screen_size.Top = 0;
    screen_size.Right = buffer_size.X - 1;
    screen_size.Bottom = buffer_size.Y - 1;

    if (Aumenta)
    {
        SetConsoleScreenBufferSize(hConsole, buffer_size);
        SetConsoleWindowInfo(hConsole, true, &screen_size);
    }
    else
    {
        SetConsoleWindowInfo(hConsole, true, &screen_size);
        SetConsoleScreenBufferSize(hConsole, buffer_size);
    }

    /*
    NOTA SOBRE REDIMENSIONAR A JANELA:
    É interessante observar que quando se deseja AUMENTAR a janela, é preciso primeiro
    redimensionar o buffer do console e então redimensionar a janela.

    De forma contrária, quando se quer DIMINUIR a janela, precisa-se primeiro redimensionar
    a janela e depois o buffer do console.

    Isso se dá pois quando se aumenta a janela, o buffer precisa ser suficientemente grande
    para o novo tamanho dela. E quando se diminui, a janela precisa se redimensionar primeiro
    para que então "sobre" buffer e seja possível enconlhê-lo para o novo tamanho da janela.

    - Rique
    */
}

// Coloca o cursor do console em uma coordenada específica
void setCmdCursor(int x, int y, HANDLE hConsoleOut)
{
    if ((hConsoleOut != NULL) && (hConsoleOut != INVALID_HANDLE_VALUE))
    {
        COORD coord;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsoleOut, coord);
    }
}

// Esconde o cursor
void hideCursor(HANDLE hConsoleOut, bool val)
{
    // Esconde o cursor
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = !val;

    SetConsoleCursorInfo(hConsoleOut, &info);
}

// --------------------------------------------------- Utilitários ---------------------------------------------------

// Essa função cria um delay de "tempo" milissegundos
void timer(int tempoMS)
{
    // A variável "start" salva o número de clocks até o momento de execução
    clock_t start = clock();
    // A variável "diff" salvará a diferença de clocks
    clock_t diff;
    // "msec" salvará os milissegundos que passaram
    int msec;

    /*
    Aqui foi usado o método do-while para garantir o bom funcionamento
    até em casos em que o tempo de delay é bem pequeno.
    */
    do
    {
        // Esse for é só para ocupar o processador com alguma coisa
        for (int i = 0; i < 99999; i++)
        {
            continue;
        }

        // Calcula a diferença do número de clocks atuais com os iniciais
        diff = clock() - start;
        // Converte essa diferença para milissegundos
        msec = (diff * 1000) / CLOCKS_PER_SEC;

        /*
        Se a diferença em milissegundos for menor que o tempo solicitado para delay,
        o código no "do" continuará a ser executado repetidamente. Quando a diferença
        for igual ou superior que o tempo solicitado, o laço quebra e a função acaba
        */
    } while (msec < tempoMS);
}