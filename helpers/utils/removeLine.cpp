#include <fstream>
#include <string>
#include <iostream>

int removeLine(const std::string filename, int lineToRemove) {
    std::cout << filename <<"--"<< lineToRemove << std::endl;
    std::ifstream fin(filename);
    std::ofstream temp("temp.txt");

    std::string line;
    int lineNumber = 0;

    while (std::getline(fin, line)) {
        lineNumber++;
        if (lineNumber != lineToRemove) {
            temp << line << std::endl;
        }
    }

    fin.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    return 0;
}
