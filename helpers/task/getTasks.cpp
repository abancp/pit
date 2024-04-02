#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include "../utils/getDateFromTime.cpp"
#include "../utils/split.cpp"

#define YELLOW "\033[33m"
#define RESET "\033[0m"

namespace fs = std::filesystem;

void getTask(bool order)
{
    if (order == false)
    {
        std::string stages[3] = {"active", "working", "closed"};
        std::string hashes[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        fs::path pitFolder = fs::current_path() / ".pit" / "tasks";
        for (std::string stage : stages)
        {
            std::cout << " ------ " << char(towupper(stage[0])) << stage.substr(1, stage.length() - 1) << "Tasks" << std::endl <<std::endl;
            int taskNo = 0;
            for (std::string hash : hashes)
            {
                std::ifstream inFile(pitFolder / stage / hash);
                std::string line;
                if (inFile.is_open())
                {
                    while (std::getline(inFile, line))
                    {
                        std::vector taskProps = splitString(line, '~');
                        long long timeMilliSeconds = std::stoll(taskProps[0].substr(4, 17));
                        std::tm *date = getDateFromTime(timeMilliSeconds);
                        std::cout << "\t " << ++taskNo << "\n" << "\t Id   : " << YELLOW << taskProps[0] << RESET << "\n"
                                  << "\t Task : " << taskProps[1] << "\n"
                                  << "\t Dev  : " << taskProps[2] << "\n"
                                  << "\t Date : " << date->tm_year << " " << date->tm_mon << " " << date->tm_mday << " " << date->tm_hour << ":" << date->tm_min << ":" << date->tm_sec << std::endl
                                  << std::endl;
                    }
                }
            }
        }
    }
}