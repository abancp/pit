#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> splitString( std::string str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}