#include <windows.h>
#include <stdbool.h>

// Defines de tamanhos de fontes e posições dos gráficos
#define SPR_FONT 8
#define SPR_W 201
#define SPR_H 97

#define MENU_W 300
#define MENU_H 87

#define MSYSTEM_W 75
#define MSYSTEM_H 25
#define MSYSTEM_FONT 24

#define POS_FALA_X 145
#define POS_FALA_Y 22

// Funções de sprites e falas
void showSPR(char *SPR, int lineStart, int lineEnd);
char *loadSPR(const char *arquivo);
void showFala(char falaNum, char *falaSPR, int posX, int posY, HANDLE hConsoleOut);
void showSPRinPos(char *SPR, int posX, int posY, HANDLE hConsoleOut);

// Funções de janela e console
void setConsoleFont(HANDLE hConsoleOut, int fontSize);
void setWindowSize(HANDLE hConsole, int BufferX, int BufferY, bool Aumenta);
void setCmdCursor(int x, int y, HANDLE hConsoleOut);
void hideCursor(HANDLE hConsoleOut, bool val);
void centerWindow(HWND ConsoleWindow);

// Funções auxiliares
void timer(int tempoMS);