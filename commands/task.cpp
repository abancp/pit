#include <iostream>
#include <string>
#include "../helpers/task/addTask.cpp"

void task(int argc,const char **argv)
{
    if (argc > 2)
    {
        std::string subCommand = argv[2];
        if (subCommand == "add"){
            if (argc > 3)
            {
                std::string taskName = argv[3];
                addTask(taskName);
            }
        }
    }
}