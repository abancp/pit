#include <iostream>
#include <string>
#include <chrono>
#include <random>

std::string generateUniqueId() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

    std::string timeString = std::to_string(value.count());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');
    std::string randomString;
    for (int i = 0; i < 10; ++i) { 
        randomString += dis(gen);
    }

    std::string uniqueId = timeString + randomString;

    if (uniqueId.length() < 20) {
        uniqueId += std::string(20 - uniqueId.length(), 'a');
    } else if (uniqueId.length() > 20) {
        uniqueId = uniqueId.substr(0, 20);
    }

    return uniqueId;
}

