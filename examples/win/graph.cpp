#include <iostream>
#include "graph.h"
#include "glsl-cpp.h"

using namespace glsl;

union U_ARGB {
    unsigned int color;
    unsigned char com[4];
} U_ARGB;

int _bufferStride;
char* _ScreenBuffer = 0;
int* ScreenBuffer = 0;
int WindowWidth = 0, WindowHeight = 0;
int _ww = 0, _wh = 0;
int MousePosX = 0, MousePosY = 0;
int MouseAccX = 0, MouseAccY = 0;
int MouseDragX = 0, MouseDragY = 0;
bool isShow = false;
bool isClose = false;

bool _CreateWindow(void* hInst);
bool _DestroyWindow();
void _Message();
void _AllMessage();
void _CheckWindow();
void _SetWindowClientSize(int w,int h);
void _Redraw();
void _TextOut(int x, int y, const char* text, const Font &f);

void CreateWindow()
{
    _CheckWindow();
}

void DestroyWindow()
{
    _DestroyWindow();
}

bool WindowIsClose()
{
    return isClose;
}

void CheckMessage()
{
    _Message();
}

void CheckAllMessage()
{
    _AllMessage();
}

void SetWindowSize(int w, int h)
{
    WindowWidth = w;
    WindowHeight = h;
    _SetWindowClientSize(WindowWidth, WindowHeight);
}

void DrawScreenBuffer()
{
    _Redraw();
}

unsigned int ARGB(unsigned char a, unsigned char r,unsigned char g,unsigned char b)
{
    union U_ARGB c;
    c.com[3] = a;
    c.com[2] = b;
    c.com[1] = g;
    c.com[0] = r;
    return c.color;
}

void DrawFillRect(int x1,int y1,int x2,int y2,int color)
{
    if (_ScreenBuffer==0)
        return;
    int _x1 = clamp(min(x1,x2),0,WindowWidth);
    int _x2 = clamp(max(x1,x2),0,WindowWidth);
    int _y1 = clamp(min(y1,y2),0,WindowHeight);
    int _y2 = clamp(max(y1,y2),0,WindowHeight);
    int skip = WindowWidth + (_x2 - _x1);
    int* idx = ScreenBuffer + _x1 + (WindowHeight - 1 - _y1) * WindowWidth;
    for (int y = _y1; y<_y2;y++) {
        for (int x = _x1; x<_x2;x++) {
            *idx = color;
            idx ++;
        }
        idx-=skip;
    }
}

void DrawCircle(int xp,int yp,int r, int color)
{
    if (_ScreenBuffer==0)
        return;
    int r2 = r*r;
    int _x1 = clamp(xp-r,0,WindowWidth);
    int _x2 = clamp(xp+r,0,WindowWidth);
    int _y1 = clamp(yp-r,0,WindowHeight);
    int _y2 = clamp(yp+r,0,WindowHeight);
    int skip = WindowWidth + (_x2 - _x1);
    int* idx = ScreenBuffer + _x1 + (WindowHeight - 1 - _y1) * WindowWidth;
    for (int y = _y1-yp; y<_y2-yp; y++) {
        for (int x = _x1-xp; x<_x2-xp; x++) {
            if ( x*x + y*y < r2)
                *idx = color;
            idx ++;
        }
        idx-=skip;
    }
}

void DrawBuff(int x,int y,int w,int h,int *buff)
{
    if (_ScreenBuffer==0)
        return;
    int _x1 = clamp(x,0,WindowWidth);
    int _x2 = clamp(x+w,0,WindowWidth);
    int _y1 = clamp(y,0,WindowHeight);
    int _y2 = clamp(y+h,0,WindowHeight);
    int* bu = buff+_x1-x+w*(_y1-y);
    int bskip = w-(_x2-_x1);
    int skip = WindowWidth + (_x2 - _x1);
    int* idx = ScreenBuffer + _x1 + (WindowHeight - 1 - _y1) * WindowWidth;
    for (int y = _y1; y<_y2;y++) {
        for (int x = _x1; x<_x2;x++) {
            *idx = *bu;
            bu ++;
            idx ++;
        }
        bu += bskip;
        idx -= skip;
    }
}

void DrawBuffAlphaAdd(int x,int y,int w,int h,int *buff)
{
    if (_ScreenBuffer==0)
        return;
    int _x1 = clamp(x,0,WindowWidth);
    int _x2 = clamp(x+w,0,WindowWidth);
    int _y1 = clamp(y,0,WindowHeight);
    int _y2 = clamp(y+h,0,WindowHeight);
    int* bu = buff+_x1-x+w*(_y1-y);
    int bskip = w-(_x2-_x1);
    int skip = WindowWidth + (_x2 - _x1);
    int* idx = ScreenBuffer + _x1 + (WindowHeight - 1 - _y1) * WindowWidth;
    for (int y = _y1; y<_y2;y++) {
        for (int x = _x1; x<_x2;x++) {
            union U_ARGB a;
            union U_ARGB b;
            a.color = *bu;
            b.color = *idx;
            int alp = 256-a.com[3];
            int c1 = ((b.com[0]*alp)>>8) + a.com[0];
            int c2 = ((b.com[1]*alp)>>8) + a.com[1];
            int c3 = ((b.com[2]*alp)>>8) + a.com[2];
            a.com[0] = c1>255 ? 255:c1;
            a.com[1] = c2>255 ? 255:c2;
            a.com[2] = c3>255 ? 255:c3;
            *idx = a.color;
            bu ++;
            idx ++;
        }
        bu += bskip;
        idx -= skip;
    }
}

void TextOut(int x, int y, const char* text, const Font &f)
{
    _TextOut(x,y,text,f);
}

void TextOut(int x, int y, int n, const Font &f)
{
    char s[12];
    sprintf(s, "%i", n);
    _TextOut(x, y, s, f);
}

void TextOut(int x, int y, double r, const Font &f)
{
    char s[24];
    sprintf(s, "%f", r);
    _TextOut(x, y, s, f);
}

#include <wingdi.h>
#include <windows.h>

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

HWND hMainWnd = NULL;
HDC hDCWnd = NULL;
HBITMAP hDCBuff = NULL;
LPSTR WINCLASSNAME = (LPSTR)"CLASS";
LPSTR WINNAME = (LPSTR)"APPLICATION";

void _SetWindowClientSize(int w,int h)
{
    if (hMainWnd == NULL)
        return;

    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.right = WindowWidth;
    rect.bottom = WindowHeight;
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    _ww = rect.right - rect.left;
    _wh = rect.bottom - rect.top;
    SetWindowPos(hMainWnd, 0, 0, 0, _ww, _ww,SWP_SHOWWINDOW|SWP_NOMOVE);
}

void _ReInitScreenBuffer()
{
    _bufferStride = WindowWidth<<2;
    if (_ScreenBuffer != NULL) {
        DeleteObject(hDCBuff);
        hDCBuff=NULL;
    }
	BITMAPINFO binfo;
	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = WindowWidth;
	binfo.bmiHeader.biHeight = WindowHeight;
	binfo.bmiHeader.biPlanes=1;
	binfo.bmiHeader.biBitCount=32;
	binfo.bmiHeader.biClrImportant=0;
	binfo.bmiHeader.biClrUsed=0;
	binfo.bmiHeader.biSizeImage=WindowWidth*WindowHeight*4;
	binfo.bmiHeader.biCompression=BI_RGB;
    hDCBuff = CreateDIBSection (hDCWnd, (BITMAPINFO*)&binfo, DIB_RGB_COLORS, (void**)&_ScreenBuffer, 0, 0 );
    ScreenBuffer = (int*)_ScreenBuffer;
}

void _Redraw()
{
	BITMAPINFO binfo;
	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = WindowWidth;
	binfo.bmiHeader.biHeight = WindowHeight;
	binfo.bmiHeader.biPlanes=1;
	binfo.bmiHeader.biBitCount=32;
	binfo.bmiHeader.biClrImportant=0;
	binfo.bmiHeader.biClrUsed=0;
	binfo.bmiHeader.biSizeImage=WindowWidth*WindowHeight*4;
	binfo.bmiHeader.biCompression=BI_RGB;
	SetDIBitsToDevice(hDCWnd,0,0,WindowWidth, WindowHeight,0,0,0,WindowHeight,ScreenBuffer,(BITMAPINFO*)&binfo,DIB_RGB_COLORS);
}

void _MouseCheck(int x,int y,unsigned int w)
{
    MouseAccX += x-MousePosX;
    MouseAccY += y-MousePosY;
    if (w==MK_LBUTTON) {
        MouseDragX += x-MousePosX;
        MouseDragY += y-MousePosY;
    }
    MousePosX = x;
    MousePosY = y;
}

LRESULT CALLBACK WinProc(HWND hw,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            break;
        case WM_SIZE:
            WindowWidth = LOWORD(lParam);
            WindowHeight = HIWORD(lParam);
            RECT rect;
            rect.top = 0;
            rect.left = 0;
            rect.right = WindowWidth;
            rect.bottom = WindowHeight;
            AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
            _ww = rect.right - rect.left;
            _wh = rect.bottom - rect.top;
            _ReInitScreenBuffer();
            break;
        case WM_PAINT:
            //_Redraw();
            return DefWindowProc(hw,msg,wParam,lParam);
        case WM_DESTROY:
            _DestroyWindow();
            PostQuitMessage(0);
            ExitProcess(0);
            break;
        case WM_MOUSEMOVE:
            _MouseCheck(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),wParam);
            break;
        //case WM_QUIT:
            //ExitProcess(wParam);
            //break;
        default:
            return DefWindowProc(hw,msg,wParam,lParam);
    }
    return 0;
}

bool _CreateWindow(void* hInst)
{
    WNDCLASS wc; /*объявляем наш класс*/
    wc.style=0; /* стиль (поведение) класса окон,*/
    wc.lpfnWndProc=WinProc; /*процедура обработки событий окна - передаём указатель на функцуию*/
    wc.cbClsExtra=0; /*размер дополнительной памяти в системной структуре класса для данных пользователя */
    wc.cbWndExtra=0; /*  размер дополнительной памяти в системной структуре окна для данных пользователя*/
    wc.hInstance=(HINSTANCE)hInst;/*дескриптор модуля (экземпляра программы), в котором реализована процедура обработки - передаём указатель на нашу программу ,полученный из WinMain() */
    wc.hIcon=NULL; /* дескриптор иконки окна*/
    wc.hCursor=LoadCursor(0, IDC_ARROW); /*дескриптор курсора мыши для окна */
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);/* дескриптор "кисточки" для закрашивания фона окна - определяем стиль закрашивания*/
    wc.lpszMenuName=NULL;/* имя ресурса, содержащего меню окна*/
    wc.lpszClassName = WINCLASSNAME;/* имя класса*/
    if (!RegisterClass(&wc)) return FALSE; /*  регистрируем класс программы с заполненной структорой  -в случае деуспешности последнего действа -
                                                  возвращаем "наружу" всеми признанный идентификатор неуспешности - false*/

    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.right = WindowWidth;
    rect.bottom = WindowHeight;
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    _ww = rect.right - rect.left;
    _wh = rect.bottom - rect.top;
            /* создаем главное окно и отображаем его  - передаём 11 параметров*/
    hMainWnd=CreateWindow(WINCLASSNAME, /*имя класса  */
        WINNAME,/*имя окна (заголовок) */
        WS_OVERLAPPEDWINDOW, /*стиль (поведение) окна =  стиль WS_OVERLAPPEDWINDOW дарует окну стандартные в числе прочего
                                стандартные кнопки свёртывания - развёртывания и заголовок */
            /*CW_USEDEFAULT - этот параметр предлагает операционной системе виндоус самой определиться со значением ниже
             перечисленных характеристик окна.*/
        WindowWidth > 0 ? (GetSystemMetrics (SM_CXSCREEN) >> 1) - (_ww  >> 1) : CW_USEDEFAULT, /*горизонтальная позиция окна на экране -  точка левого верхнего угла окна - х-координата  */
        WindowHeight > 0 ? (GetSystemMetrics (SM_CYSCREEN) >> 1) - (_wh >> 1) : CW_USEDEFAULT, /*вертикальная позиция окна на экране -  точка левого верхнего угла окна - у-координата  - от нее откладываются длина и высота*/
        WindowWidth > 0 ? _ww : CW_USEDEFAULT, /*ширина окна */
        WindowHeight > 0 ? _wh : CW_USEDEFAULT, /*высота окна */
        NULL, /*дескриптор родительского окна */
        NULL, /*дескриптор меню */
        (HINSTANCE)hInst, /* дескриптор экземпляра программы */
        NULL /*указатель на какую-нибудь ерунду (по другой версии - "указатель на данные создания окна")*/
    );

    if (!hMainWnd) return FALSE;

    hDCWnd = GetDC(hMainWnd);
    _ReInitScreenBuffer();
    isClose = false;
    return true;
}

bool _DestroyWindow()
{
    bool ret = true;
    if (_ScreenBuffer != NULL)
        DeleteObject(hDCBuff);
    if (ReleaseDC(hMainWnd,hDCWnd)==0)
		ret = false;
    isClose = true;
    return ret;
}

void _CheckWindow()
{
    if (hMainWnd == NULL && _CreateWindow(NULL) && !isShow) {
        ShowWindow(hMainWnd, SW_SHOWNORMAL);
        isShow = true;
    }
}

void _Message()
{
    _CheckWindow();

    MSG messages;
    if (PeekMessage(&messages, hMainWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}

void _AllMessage()
{
    _CheckWindow();

    MSG messages;
    while (PeekMessage(&messages, hMainWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}

void _TextOut(int x, int y, const char* text, const Font &f)
{
    if (_ScreenBuffer==0)
        return;

    HDC hdcCompat = CreateCompatibleDC(hDCWnd);
    HGDIOBJ hLast = SelectObject(hdcCompat, hDCBuff);

    HFONT hf = CreateFont(-MulDiv(f.Size, GetDeviceCaps(hDCWnd, LOGPIXELSY), 72), 0, 0, 0, ((f.Style & 1)!=0) ? 700 : 400,
                          ((f.Style & 2)!=0),
                          ((f.Style & 4)!=0),
                          false, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, f.Name);
    SelectObject(hdcCompat, hf);
    SetBkMode(hdcCompat, TRANSPARENT);
    SetTextColor(hdcCompat, f.Color);
    TextOut(hdcCompat, x, y, text, strlen(text));

    SelectObject(hdcCompat, hLast);
    DeleteObject(hf);
    DeleteDC(hdcCompat);
}

void __attribute__((constructor)) _CoreStart()
{
    //_Message();
}

void __attribute__((destructor)) _CoreExit()
{
    //_Message();

    _CheckWindow();

    MSG messages;            /* Here messages to the application are saved */
    while (GetMessage(&messages, hMainWnd, 0, 0))
    {
        //if (messages.message == WM_QUIT)
            //ExitProcess(0);
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}
