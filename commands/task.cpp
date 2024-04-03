#include <iostream>
#include <string>
#include <unordered_map>
#include "../helpers/task/getTasks.cpp"
#include "../helpers/task/addTask.cpp"

void task(int argc, const char **argv)
{
    if (argc > 2)
    {
        std::string subCommand = argv[2];
        if (subCommand == "add")
        {
            if (argc == 5|| argc == 6)
            {
                std::unordered_map<std::string, int> flagsMap = {
                    {"-a", 1},
                    {"--active", 1},
                    {"-w", 2},
                    {"--work", 2},
                    {"-c", 3},
                    {"--close", 3},
                };

                std::string taskName = argv[4];

                switch (flagsMap[argv[3]])
                {
                case 1:
                    addTask(taskName, 1);
                    break;
                case 2:
                    addTask(taskName, 2);
                    break;
                case 3:
                    addTask(taskName, 3);
                    break;
                }
            }
            else if (argc == 4)
            {
                std::string taskName = argv[3];
                addTask(taskName, 1);
            }
        }
    }
    else
    {
        if (argc == 2)
        {
            getTask(false);
        }
        // TODO: Usage
    }
}