#include <string>
#include <filesystem>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include "../helpers/utils/id.cpp"
#include "../helpers/utils/removeLine.cpp"

#define YELLOW "\033[33m"
#define RESET "\033[0m"

namespace fs = std::filesystem;
class Task
{
public:
    std::string name;
    std::string stage;
    bool isId;
    struct User
    {
        std::string name;
        std::string mail;
    };
    struct existTask
    {
        int stageNo;
        int lineNO;
        std::string taskName;
    };

    Task(std::string taskName, int type, bool isId0)
    {
        name = taskName;
        isId = isId0;
        stage;

        switch (type)
        {
        case 1:
        {
            stage = "active";
            break;
        }
        case 2:
        {
            stage = "working";
            break;
        }
        case 3:
        {
            stage = "closed";
            break;
        }
        }
    }

private:
    User getUser()
    {
        fs::path configFile;
        if (fs::exists(fs::current_path() / ".pit" / "pitconfig"))
        {
            configFile = fs::current_path() / ".pit" / "pitconfig";
        }
        else
        {
            struct passwd *pw = getpwuid(getuid());
            if ((pw != nullptr))
            {
                fs::path tempConfigFile = pw->pw_dir;
                tempConfigFile = tempConfigFile / ".pitconfig";
                if (fs::exists(tempConfigFile))
                {
                    configFile = tempConfigFile;
                }
                else
                {
                    // TODO :
                }
            }
            else
            {
                // TODO
            }
        }

        std::ifstream infile(configFile);

        if (infile.is_open())
        {
            std::string line;
            std::string username;
            std::string usermail;
            int lineNo = 0;
            while (std::getline(infile, line))
            {
                if (lineNo == 1)
                {
                    username = line.substr(10);
                }
                if (lineNo == 2)
                {
                    usermail = line.substr(7);
                }
                lineNo++;
            }
            infile.close();
            User user = {username, usermail};
            return user;
        }
        else
        {
            std::cerr << "Error: Unable to open file." << std::endl;
            User user = {"unknown", "unknown"};
            return user;
        }
    }

    int hashToOneDigit(std::string taskStr)
    {
        int hashed = 0;
        if (taskStr.length() > 2)
        {
            for (int i = 0; i < 3; i++)
            {
                hashed += int(taskStr[i]);
            }

            return hashed % 10;
        }
        else
        {
            for (int i = 0; i < taskStr.length(); i++)
            {
                hashed += int(taskStr[i]);
            }
            return hashed % 10;
        }
    }

    existTask checkExist(std::string taskName)
    {
        existTask returnExistTask;
        std::string hashed;
        if (isId)
        {
            hashed = taskName.substr(2, 1);
        }
        else
        {
            std::stringstream string;
            string << hashToOneDigit(taskName);
            hashed = string.str();
        }

        std::string stages[3] = {"active", "working", "closed"};
        for (const std::string fileStage : stages)
        {
            fs::path filePath = fs::current_path() / ".pit" / "tasks" / fileStage / hashed;

            std::ifstream infile(filePath);
            int lineNo = 0;
            if (infile.is_open())
            {
                std::string line;
                while (std::getline(infile, line))
                {
                    lineNo++;
                    std::string lineHash = line.substr(0, 3);
                    std::string nameHash = isId ? name.substr(0, 3) : hash(name);
                    if (lineHash == nameHash)
                    {
                        std::vector taskProps = splitString(line, '~');
                        std::string taskMatch = isId ? taskProps[0] : taskProps[1];
                        std::string fileTaskName = taskProps[1];
                        std::cout << taskProps[1] << std::endl;
                        if (name == taskMatch)
                        {
                            infile.close();
                            if (stage == "active")
                            {
                                std::cout << " Task already " << fileStage << " . 'pit task' to see all tasks " << std::endl;
                                exit(0);
                                return returnExistTask;
                            }
                            if (fileStage == "active")
                            {
                                returnExistTask = {1, lineNo, fileTaskName};
                                return returnExistTask;
                            }
                            else if (fileStage == "working")
                            {
                                returnExistTask = {2, lineNo, fileTaskName};
                                return returnExistTask;
                            }
                            else
                            {
                                returnExistTask = {3, lineNo, fileTaskName};
                                return returnExistTask;
                            }
                        }
                    }
                }
                infile.close();
            }
            else
            {
                std::cout << "Unexpected error while opening files" << std::endl;
            }
        }
        returnExistTask = {0, 0, ""};
        return returnExistTask;
    }

    int writeTaskToFile(fs::path pitFolder, std::string hashed,std::string taskName)
    {

        fs::path filePath = pitFolder / "tasks" / stage / hashed;
        std::cout << "file :" << filePath << std::endl;
        std::ofstream outfile(filePath, std::ios::app);
        User user = getUser();
        std::string TUID = generateTUID(taskName);
        if (outfile.is_open())
        {
            long long timeMilliSeconds = std::stoll(TUID.substr(4, 17));
            std::tm *date = getDateFromTime(timeMilliSeconds);
            std::cout << "\t Id   : " << YELLOW << TUID << RESET << "\n"
                      << "\t Task : " << taskName << "\n"
                      << "\t Dev  : " << user.name << "\n"
                      << "\t Date : " << date->tm_year << " " << date->tm_mon << " " << date->tm_mday << " " << date->tm_hour << ":" << date->tm_min << ":" << date->tm_sec << std::endl;
            outfile << TUID << "~" << taskName << "~" << user.name << "~" << user.mail << "\n";
            outfile.close();
            return 0;
        }
        else
        {
            std::cout << "Unexpected error while opening files" << std::endl;
            return 1;
        }
    }

public:
    void setTask()
    {
        fs::path pitFolder = fs::current_path() / ".pit";
        if (fs::exists(pitFolder))
        {
            existTask existCode = checkExist(name);
            std::string hashed;
            if (isId)
            {
                hashed = name.substr(2, 1);
            }
            else
            {
                std::stringstream string;
                string << hashToOneDigit(name);
                hashed = string.str();
            }
            if (existCode.stageNo == 0 && stage == "active")
            {
                writeTaskToFile(pitFolder, hashed ,name);
                return;
            }
            if (existCode.stageNo == 1 && stage == "working")
            {
                std::string removeFilePath = pitFolder / "tasks" / "active" / hashed;
                removeLine(removeFilePath, existCode.lineNO);
                writeTaskToFile(pitFolder, hashed ,existCode.taskName);
                return;
            }
            if (existCode.stageNo == 2 && stage == "closed")
            {
                std::string removeFilePath = pitFolder / "tasks" / "working" / hashed;
                removeLine(removeFilePath, existCode.lineNO);
                writeTaskToFile(pitFolder, hashed ,existCode.taskName);
                return;
            }
            if ((existCode.stageNo == 0 || existCode.stageNo == 1) && stage == "closed")
            {
                std::cout << "task is not in working , only working tasks can close" << std::endl;
                return;
            }
            if (existCode.stageNo == 0 && stage == "working")
            {
                std::cout << "Task not in active , only active tasks can work" << std::endl;
                return;
            }
            if (existCode.stageNo == 3 && stage == "working")
            {
                std::cout << "Task already closed" << std::endl;
                return;
            }
        }
        else
        {
            // TODO : correct error msg ;
        }
    }
};
