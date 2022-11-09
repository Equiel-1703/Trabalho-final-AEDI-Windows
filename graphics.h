#include <windows.h>
#include <stdbool.h>

// Defines de tamanhos de fontes e posições dos gráficos
#define SPR_FONT 8
#define SPR_W 203
#define SPR_H 97

#define POS_FALA_X 151
#define POS_FALA_Y 22

void showSPR(char *SPR, int lineStart, int lineEnd);
char *loadSPR(const char *arquivo);
void showFala(char falaNum, char *falaStr, int posX, int posY, HANDLE hConsoleOut);

void setConsoleFont(HANDLE hConsoleOut, int fontSize);
void setWindowSize(HANDLE hConsole, int BufferX, int BufferY, bool Aumenta);
void setCmdCursor(int x, int y, HANDLE hConsoleOut);
void hideCursor(HANDLE hConsoleOut, bool val);

void timer(int tempoMS);

// --------------------------------------------------- Coisas da API do Windows ---------------------------------------------------

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
