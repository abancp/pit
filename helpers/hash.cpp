#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

std::string hash(std::string taskName)
{
    int hashed = 0;
    if (taskName.length() > 2)
    {
        for (int i = 0; i < 3; i++)
        {
            hashed += int(taskName[i]);
        }
    }
    else
    {
        for (int i = 0; i < taskName.length(); i++)
        {
            hashed += int(taskName[i]);
        }
    }

    std::stringstream string;
    string << hashed;
    std::string hashedString = string.str();
    
    if (hashed > 999)
    {
        return  hashedString.substr(0,3);
    } 
    if(hashed < 100){
        return hashedString + std::string(3 - hashedString.length(),'0');
    }
    return hashedString;
}