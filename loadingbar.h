#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <cstdio>
#include <wininet.h>

/**
 * @brief ฟังก์ชัน setColor ทำหน้าที่เปลี่ยนสีตัวอักษรและพื้นหลัง
 * @param textColor เป็นสีของตัวอักษร
 * @param bgColor เป็นสีของพื้นหลัง
 * @return ไม่มีค่าที่ส่งกลับ
 * */

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void setColor_(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(7, 0);
}


void showLoadingBar(std::atomic<bool>& cloning) {
    const char* loadChars = "|/-\\";
    int counter = 0;
    while (cloning) {
        setColor(10, 0);
        std::cout << "\r" << loadChars[counter % 4] << std::flush;
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        resetColor();
    }
    setColor(10, 0);
    std::cout << "\rCloning... Done!" << std::endl;
}