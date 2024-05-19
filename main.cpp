/*
 * @file main.cpp
 * @brief โปรแกรมนี้เป็นตัวอย่างการใช้งาน Repository บน GitHub โดยใช้ Git ในการคลายโปรเจค
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <cstdio>
#include <wininet.h>

#include "loadingbar.h"    // ดึงไฟล์ loadingbar.h มาใช้งาน
#include "splash.h"        // ดึงไฟล์ splash.h มาใช้งาน
#include "progressbar.hpp" // ดึงไฟล์ progressbar.hpp มาใช้งาน
#include "sp.h"


/**
 * @brief ฟังก์ชัน isGitInstalled ทำหน้าที่ตรวจสอบว่า Git ได้ถูกติดตั้งหรือไม่
 * @return ค่าความจริงว่า Git ได้ถูกติดตั้งหรือไม่
 * */


bool isGitInstalled()
{
    FILE* pipe = _popen("git --version", "r");
    if (pipe)
    {
        _pclose(pipe);
        return true;
    }
    return false;
}


/**
 * @brief ฟังก์ชัน centerText ทำหน้าที่จัดวางข้อความตรงกลาง
 * @param text เป็นข้อความที่จะแสดง
 * @return ไม่มีค่าที่ส่งกลับ
 * */

void centerText(const std::string &text) 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (columns - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::endl;
}

/**
 * @comment เพื่อให้ผู้ใช้ทราบว่าโปรแกรมนี้จะคลายโปรเจคจาก Repository บน GitHub
 * @note แสดงข้อความต้อนรับและข้อความให้ผู้ใช้ทราบว่าโปรแกรมนี้จะคลายโปรเจคจาก Repository บน GitHub
 * @note แสดงข้อความให้ผู้ใช้ตรวจสอบว่า Git ได้ถูกติดตั้งหรือไม่
 * @note รับชื่อโปรเจคจากผู้ใช้
 * @note แสดงข้อความให้ผู้ใช้ป้อน URL ของ Repository
 * @note กำหนดคำสั่งคลายโปรเจคจาก Repository
 * @note กำหนดคำสั่งเปลี่ยน Directory
 * @note กำหนดคำสั่งลบ Remote Origin
 * @note สร้าง Thread สำหรับแสดง Loading Bar
 * @note คลายโปรเจคจาก Repository
 * @note หยุดการแสดง Loading Bar
 * @note รอให้เสร็จสิ้นการคลายโปรเจค
 * @note หน่วงเวลา 100 มิลลิวินาที
 * @return 0
 * @note สิ้นสุดการทำงานของโปรแกรม
 * */

int main()
{ // ฟังก์ชัน main ทำหน้าที่เรียกใช้งานฟังก์ชันอื่นๆ

    HWND hwnd = GetConsoleWindow();                                         // ดึงหน้าต่าง Console มาใช้งาน
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);  // ตั้งค่าหน้าต่าง Console ให้อยู่ด้านหน้าสุด
    SetConsoleTitle(TEXT("64BIT.BUZZ - Resource Cloner - Untimate (x64)")); // ตั้งชื่อหน้าต่าง Console
    showSplashScreen();                                                     // เรียกใช้งานฟังก์ชัน showSplashScreen จากไฟล์ splash.h

    std::cout << "-> [Waiting] for the console to load..." << std::endl;
    std::cout << "-> [RedNZ] Resource Cloner" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::cout << "-> [Retrun] Resource Cloner" << std::endl;
    Beep(500, 300);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // หน่วงเวลา 1000 มิลลิวินาที

    clearScreen();

    auto center = [](const std::string &text) {                             // ฟังก์ชัน center ทำหน้าที่จัดวางข้อความตรงกลาง
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int padding = (columns - text.length()) / 2;
        std::cout << std::string(padding, ' ') << text << std::endl;
    };

    std::cout << std::endl;
    setColor(3, 0);
    center(" //");
    center("_//");
    center("(')---.");
    center("_/-_( )o");
    std::cout << std::endl;

    std::string title = "Red64BIT - Resource Cloner"; // กำหนดชื่อโปรแกรม
    std::string line(title.length(), '=');            // กำหนดเส้นขั้นระหว่างข้อความ
    setColor(6, 0);
    std::cout << std::endl;
    centerText(line);

    std::string name;
    std::string url = "https://github.com/";
    setColor(6, 0);
    std::cout << std::endl;

    centerText("Welcome to Red64BIT - Resource Cloner!");                   // แสดงข้อความต้อนรับ
    centerText("This tool will clone a project from a GitHub repository."); // แสดงข้อความให้ผู้ใช้ทราบว่าโปรแกรมนี้จะคลายโปรเจคจาก Repository บน GitHub
    centerText("Please make sure you have git installed on your system.");  // แสดงข้อความให้ผู้ใช้ตรวจสอบว่า Git ได้ถูกติดตั้งหรือไม่
    std::cout << std::endl;                                                 // ขึ้นบรรทัดใหม่
    resetColor();                                                           // รีเซ็ตสีข้อความ

    if (!isGitInstalled())
    {                                                                                         // ถ้า Git ไม่ได้ถูกติดตั้ง
        setColor(12, 0);                                                                      // กำหนดสีข้อความเป็นสีแดง
        centerText("Git is not installed on your system. Please install git and try again."); // แสดงข้อความให้ผู้ใช้ติดตั้ง Git
        resetColor();                                                                         // รีเซ็ตสีข้อความ
        return 1;                                                                             // สิ้นสุดการทำงานของโปรแกรม
    }

    setColor(10, 0);                                               // กำหนดสีข้อความเป็นสีเขียว
    std::string prompt = "Please enter the name of the project: "; // กำหนดข้อความให้ผู้ใช้ป้อนชื่อโปรเจค
    centerText(prompt);                                            // จัดวางข้อความตรงกลาง

    resetColor();                 // รีเซ็ตสีข้อความ
    std::getline(std::cin, name); // รับชื่อโปรเจคจากผู้ใช้

    // แสดงข้อความให้ผู้ใช้ป้อน URL ของ Repository
    std::string gitCloneCmd = "git clone "+ url + name; // กำหนดคำสั่งคลายโปรเจคจาก Repository
    std::string changeDirCmd = "cd " + name;                                                   // กำหนดคำสั่งเปลี่ยน Directory
    std::string gitRemoveOriginCmd = "git remote remove origin";                               // กำหนดคำสั่งลบ Remote Origin

    std::atomic<bool> cloning(true);                              // กำหนดตัวแปร atomic สำหรับการคลายโปรเจค
    std::thread loadingThread(showLoadingBar, std::ref(cloning)); // สร้าง Thread สำหรับแสดง Loading Bar
    system(gitCloneCmd.c_str());                                  // คลายโปรเจคจาก Repository

    cloning = false;      // หยุดการแสดง Loading Bar
    loadingThread.join(); // รอให้เสร็จสิ้นการคลายโปรเจค

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // หน่วงเวลา 100 มิลลิวินาที

    return 0; // สิ้นสุดการทำงานของโปรแกรม
}
