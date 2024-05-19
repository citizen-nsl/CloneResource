
#include <iostream>
#include <string>

void displayProgressBar(int percentage) {
    const int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * percentage / 100;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "#";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << percentage << " %\r";
    std::cout.flush();
}
