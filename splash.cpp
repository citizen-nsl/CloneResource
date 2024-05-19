#include "splash.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <cstdio> // for popen and pclose

std::string executeCommand(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

void clearScreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
}

void showSplashScreen() {

    clearScreen();
    std::cout << R"(

   __    _  _    .______    __  .___________.  .______    __    __   ________   ________  
  / /   | || |   |   _  \  |  | |           |  |   _  \  |  |  |  | |       /  |       /  
 / /_   | || |_  |  |_)  | |  | `---|  |----`  |  |_)  | |  |  |  | `---/  /   `---/  /   
| '_ \  |__   _| |   _  <  |  |     |  |       |   _  <  |  |  |  |    /  /       /  /    
| (_) |    | |   |  |_)  | |  |     |  |     __|  |_)  | |  `--'  |   /  /----.  /  /----.
 \___/     |_|   |______/  |__|     |__|    (__)______/   \______/   /________| /________|
                                                                                                                                                  
)";
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string username = executeCommand("git config --global user.name");
    if (!username.empty()) {
        std::cout << "-> [Git] username: " << username;
        if (MessageBoxA(NULL, ("Is this your username? " + username).c_str(), "Notification", MB_YESNO | MB_ICONINFORMATION) == IDNO) {
            exit(0);
        }
    } else {
        std::cout << "Failed to get Git username." << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    clearScreen();
}


