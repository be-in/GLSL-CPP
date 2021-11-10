#ifndef BASEGRAPH_H_INCLUDED
#define BASEGRAPH_H_INCLUDED

enum FontStyleType {
    fsNormal = 0,
    fsBold = 1,
    fsItalic = 2,
    fsBoldItalic = 3,
    fsUnderline = 4,
    fsBoldUnderline = 5,
    fsItalicUnderline = 6,
    fsBoldItalicUnderline = 7
};

struct Font {
    // Цвет шрифта
    unsigned int Color;
    // Стиль шрифта
    enum FontStyleType Style;
    // Размер шрифта в пунктах
    unsigned int Size;
    // Наименование шрифта
    char* Name;
};

const Font DefaultFont = {Color:0xFFFFFF, Size:10, Name:(char*)"Arial"};

// Возвращает ширину клиентской части графического окна в пикселах.
extern int WindowWidth;
// Возвращает высоту клиентской части графического окна в пикселах.
extern int WindowHeight;

extern int* ScreenBuffer;

extern int MousePosX;
extern int MousePosY;
extern int MouseAccX;
extern int MouseAccY;
extern int MouseDragX;
extern int MouseDragY;

unsigned int ARGB(unsigned char a, unsigned char r,unsigned char g,unsigned char b);

void CreateWindow();
void SetWindowSize(int w, int h);
bool WindowIsClose();
void CheckMessage();
void CheckAllMessage();
void DrawScreenBuffer();

void DrawFillRect(int x1,int y1,int x2,int y2,int color);
void DrawBuff(int x,int y,int w,int h,int *buff);
void DrawBuffAlphaAdd(int x,int y,int w,int h,int *buff);
void TextOut(int x, int y, const char* text, const Font &f);
void TextOut(int x, int y, int n, const Font &f);
void TextOut(int x, int y, double r, const Font &f);

#endif // BASEGRAPH_H_INCLUDED
