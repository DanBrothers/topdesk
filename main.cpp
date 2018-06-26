#include <algorithm>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <memory>
#include <cstdio>            
#include <glut.h>
#include <io.h>

#using <mscorlib.dll>
#using <System.dll>

using namespace System;
using namespace std;

#pragma comment(lib, "wininet.lib")
#pragma comment (lib, "Urlmon.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

HINSTANCE hInstance;
POINT Mouse;
HWND hwnd;
RECT rect;
HDC dc;

float Size = 100;
float angle = 0;
bool Dirty = false;
char TEX;
int posX = 0;
int posY = 0;
int storedDC;

void GetDesktopResolution(int& w, int& h){
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    w = desktop.right;
    h = desktop.bottom;
}

void EX(){
    delete hInstance;
    delete hwnd;
    exit(0);
}

void Keys(){
    if (GetAsyncKeyState(VK_ESCAPE)){
        exit(0);
    }

    if (GetAsyncKeyState(VK_LBUTTON) && GetAsyncKeyState(VK_CONTROL)){

    }
}

void Draw(){
    int h;
    int w;

    //Declair Desktop Size
    GetDesktopResolution(w, h);

    angle += 0.1f;

    if (angle >= 2 * 3.141592f){
        angle -= 2 * 3.141592f;
    }

    GetCursorPos(&Mouse);
    if (Dirty == true){
        rect = { 0, 0, w, h };
        RedrawWindow(hwnd, &rect, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);

        posX = Mouse.x;
        posY = Mouse.y;

        RedrawWindow(hwnd, &rect, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
        Dirty = false;
    }

    dc = GetDC(hwnd);
    storedDC = SaveDC(dc);

    //DEFAULT_CHARSET - ANSI_CHARSET
    HFONT FMain = CreateFont(36, 20, -300, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
    SetTextColor(dc, RGB(255, 255, 255));
    SetBkColor(dc, RGB(0, 255, 0));
    SelectObject(dc, FMain);
    TextOut(dc, 15, 15, L"This is what the program does!", 30);

    RedrawWindow(hwnd, &rect, NULL, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW);

    RestoreDC(dc, storedDC);
    ReleaseDC(hwnd, dc);
}

int main(int argc, char **argv){
    int h;
    int w;

    //Declair Desktop Size
    GetDesktopResolution(w, h);

    // find Program Manager
    hwnd = FindWindowEx(GetDesktopWindow(), 0, L"Progman", L"Program Manager");
    // find SHELLDLL_DefView
    hwnd = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
    // find Desktop Folder
    hwnd = FindWindowEx(hwnd, 0, L"SysListView32", L"FolderView");

    if (hwnd == NULL){
        MessageBox(NULL, L"Could not initiate window!", L"ERROR!", MB_OK);
        EX();
    }

    while (1){
        Keys();
        Draw();
    }

    //Remove the drawing
    rect = { Mouse.x - 50, Mouse.y - 50, Mouse.x + 50, Mouse.y + 50 };
    InvalidateRect(hwnd, &rect, true);

    delete hInstance;
    delete hwnd;

    return 0;
}
