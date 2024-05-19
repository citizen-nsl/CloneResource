#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <cstdio>
#include <wininet.h>
#include <iostream>
#include <cstdio> // for popen and pclose
#include <string>



std::string executeCommand(const char* command) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(command, "r"); // Use _popen instead of popen
    if (!pipe) {
        std::cerr << "Error: _popen failed." << std::endl;
        return "";
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    _pclose(pipe); // Use _pclose instead of pclose
    return result;
}
