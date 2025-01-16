#include <iostream>
#include <windows.h>

void setPosition(int x, int y){
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
std::pair<int, int> ConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return std::pair<int, int>((info.srWindow.Right - info.srWindow.Left + 1), (info.srWindow.Bottom - info.srWindow.Top + 1));
}

int main(){
    std::pair<int, int> consolesize = ConsoleSize();

    int xscreenPixel = GetSystemMetrics(SM_CXSCREEN);
    int ycreenPixel = GetSystemMetrics(SM_CYSCREEN);

    // decreasing factor, approximate scale
    double xfactor = static_cast<double>(xscreenPixel) / consolesize.first;
    double yfactor = static_cast<double>(ycreenPixel) / consolesize.second;

    bool pastClicked = false;
    while(1){
        POINT userCursor;
        GetCursorPos(&userCursor);
        int auxx = (int)(userCursor.x/xfactor);
        int auxy = (int)(userCursor.y/yfactor);
        setPosition((int)(userCursor.x/xfactor), (int)(userCursor.y/yfactor));
        std::cout << ".";
        if ((GetAsyncKeyState(0x01) & 0x8000)){
            // if(!pastClicked){
                GetCursorPos(&userCursor);
                setPosition((int)(userCursor.x/xfactor), (int)(userCursor.y/yfactor));
                std::cout << "x";
            //     pastClicked = true;
            // }
         }
        // else{
        //     pastClicked = false;
        // }
        setPosition(auxx, auxy);
        std::cout << " ";
        Sleep(10);

    }
    

    return 0;
}
