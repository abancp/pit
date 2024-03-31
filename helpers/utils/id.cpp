#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include "./hash.cpp"

std::string generateTUID(std::string taskName)
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');
    std::string randomString;
    for (int i = 0; i < 10; ++i) { 
        randomString += dis(gen);
    }

    std::string timeString = std::to_string(value.count());
    std::string UID = hash(taskName) + "/" + timeString + randomString;

    if (UID.length() < 20)
    {
        UID += std::string(20 - UID.length(), 'a');
    }
    else if (UID.length() > 20)
    {
        UID = UID.substr(0, 20);
    }

    return UID;
}